/*
 * Copyright (c) 2015, Majenko Technologies
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * * Redistributions of source code must retain the above copyright notice, this
 *   list of conditions and the following disclaimer.
 *
 * * Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * * Neither the name of Majenko Technologies nor the names of its
 *   contributors may be used to endorse or promote products derived from
 *   this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>

#include "Time.h"
#include "Timezone.h"

#include "updateTime.h"
#include "localWebServer.h"

TimeChangeRule usEDT = {"EDT", Second, Sun, Mar, 2, -240};  //UTC - 4 hours
TimeChangeRule usEST = {"EST", First, Sun, Nov, 2, -300};   //UTC - 5 hours
Timezone usEastern(usEDT, usEST);

int brightness = 0;
bool brighter = true;

int pwmIntervals = 180; // three hour fade on and off
float R = (pwmIntervals * log10(2))/(log10(1023));

// variable here temporarily to simulate faster days
int timeWarp = 0;

void setup ( void ) {
  startWiFi();
  startNTP();
  analogWriteFreq(500);
  analogWrite(D1, brightness);
}

void loop ( void ) {
  server.handleClient();
  
  // artificially increase the time by 15 mins ever loop to simulate faster days.
  time_t utc = now();// + timeWarp*900;
  time_t eastern = usEastern.toLocal(utc);

  if(hour(eastern) >= 7 && hour(eastern) < 10) {
    Serial.println("Getting brighter!");
    float minutesSince7 = (hour(eastern) - 7)*60 + minute(eastern);
    brightness = pow(2, (minutesSince7 /  R)) - 1;
  }
  if(hour(eastern) >= 10 && hour(eastern) < 17) {
    Serial.println("Peak brightness!");
    brightness = 1023;
  }
  if(hour(eastern) >= 17 && hour(eastern) < 20) {
    // dim LEDs
    Serial.println("Getting dimmer!");
    float minutesUntil8 = (20 - hour(eastern))*60 - minute(eastern);
    brightness = pow(2, (minutesUntil8 / R)) - 1;
  }
  if(hour(eastern) >= 20 || hour(eastern) < 7) {
    Serial.println("Peak darkness!");
    brightness = 0;
  }


  if(lightToggleOverride == 1) {
    brightness = 1023;
  }
  if(lightToggleOverride == 2) {
    brightness = 0;
  }
  Serial.print("Current time:");
  Serial.println(hour(eastern));
  Serial.print("Current brightness:");
  Serial.println(brightness);
  analogWrite(D1, brightness);

  delay(500);
  // Let's do the time warp again!
  //timeWarp++;
}

