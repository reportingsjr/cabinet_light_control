#include <ESP8266WiFi.h>
#include <WiFiUdp.h>

#include <Time.h> // https://github.com/PaulStoffregen/Time
#include <Timezone.h> // https://github.com/JChristensen/Timezone

#include "updateTime.h"

unsigned int localPort = 2390;

/* Don't hardwire the IP address or we won't get the benefits of the pool.
 *  Lookup the IP address for the host name instead */
IPAddress timeServerIP; // time.nist.gov NTP server address
const char* ntpServerName = "time.nist.gov";

const int NTP_PACKET_SIZE = 48; // NTP time stamp is in the first 48 bytes of the message


byte packetBuffer[ NTP_PACKET_SIZE]; //buffer to hold incoming and outgoing packets

// A UDP instance to let us send and receive packets over UDP
WiFiUDP udp;

time_t eastern, utc;
TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -240};  //UTC - 4 hours
TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -300};   //UTC - 5 hours
Timezone usEastern(usEDT, usEST);

void startNTP() {
  udp.begin(localPort);

  // This sets up a timer to update our time from NTP every 10 minutes
  setSyncProvider(ntpUpdateTime);
  setSyncInterval(600);
}

// send an NTP request to the time server at the given address
unsigned long sendNTPpacket(IPAddress& address)
{
  Serial.println("sending NTP packet...");
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;

  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}

time_t ntpUpdateTime()
{
  time_t ntpTime = 0;
  int maxRetries = 5;

  // Attempt up to maxRetries to get a time from NTP
  int i = 0;
  while( i < maxRetries ) {
    //get a random server from the pool
    WiFi.hostByName(ntpServerName, timeServerIP); 

    sendNTPpacket(timeServerIP);

    // wait to see if a reply is available
    delay(1000);
  
    int cb = udp.parsePacket();
    if (!cb) {
      // If we hit our limit return out of the function,
      // else increment and try again
      if(i == (maxRetries - 1)) {
        Serial.println("Giving up trying to get time from NTP server.");
        return ntpTime;
      } else {
        i++;
      }
    } else {
      // If we got a response break out of the loop
      break;
    }
  }
  
  // We've received a packet, read the data from it
  udp.read(packetBuffer, NTP_PACKET_SIZE);

  //the timestamp starts at byte 40 of the received packet and is four bytes,
  // or two words, long. First, extract the two words:

  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;


  // now convert NTP time into unix epoch:
  // Unix time starts on Jan 1 1970. In seconds since Jan 1 1900 that's 2208988800:
  const unsigned long seventyYears = 2208988800UL;
  // subtract seventy years:
  ntpTime = secsSince1900 - seventyYears;
  
  // return Unix time:
  return ntpTime;
}
