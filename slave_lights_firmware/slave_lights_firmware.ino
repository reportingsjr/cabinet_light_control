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

extern "C" {
#include "pwm.h"
}

#include <ESP8266WiFi.h>
// For MQTT
#include <PubSubClient.h>

// For OTA updates
#include <ESP8266mDNS.h>
#include <WiFiUdp.h>
#include <ArduinoOTA.h>

#include "wifiPassword.h"

const PROGMEM char*     MQTT_CLIENT_ID    = "microwave_cabinet_lights";
const PROGMEM char*     MQTT_SERVER_IP    = "192.168.0.22";
const PROGMEM uint16_t  MQTT_SERVER_PORT  = 1883;

// MQTT: topics
// state
const PROGMEM char*     MQTT_LIGHT_STATE_TOPIC                = "kitchen/microwavecabinetlight";
const PROGMEM char*     MQTT_LIGHT_COMMAND_TOPIC              = "kitchen/microwavecabinetlight/switch";

// brightness
const PROGMEM char*     MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC     = "kitchen/microwavecabinetlight/brightness";
const PROGMEM char*     MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC   = "kitchen/microwavecabinetlight/brightness/set";

// payloads by default (on/off)
const PROGMEM char*     LIGHT_ON          = "ON";
const PROGMEM char*     LIGHT_OFF         = "OFF";

// state of the sun
const PROGMEM char*    MQTT_SUN_TOPIC = "sun";

// sun payloads
const PROGMEM char*    SUNSET = "sunset";
const PROGMEM char*    SUNRISE = "sunrise";

boolean m_light_state = false;
int m_light_brightness = 0;
boolean m_sun_up = false;

// pin used for the led (PWM)
const PROGMEM uint8_t LIGHT_PIN = D1;

const uint8_t MSG_BUFFER_SIZE = 20;
char m_msg_buffer[MSG_BUFFER_SIZE]; 

WiFiClient wifiClient;
PubSubClient client(wifiClient);

time_t PIR_time_passed = 0;
boolean on_from_PIR = false;

// number of milliseconds to wait to turn off LEDs once PIR no longer detects someone
const unsigned long turn_off_countdown = 120000;

// state machine:
// on_pir = PIR sensor detects presence
// counting_down_pir = PIR sensor doesn't detect anyone, but on
// off_pir = PIR sensor hasn't detected anyone in X seconds
// off_ha = turned off in home assistant
// on_ha = turned off in home assistant
enum current_state_enum {
  on_pir,
  counting_down_pir,
  off_pir,
  off_ha,
  on_ha,
  button
};

current_state_enum current_state = off_pir;

// function called to adapt the brightness and the state of the led
void setLightState() {
  if (m_light_state) {
    pwm_set_duty(m_light_brightness, 0);
    pwm_start();
    Serial.print("INFO: Brightness: ");
    Serial.println(m_light_brightness);
  } else {
    pwm_set_duty(0, 0);
    pwm_start();
    Serial.println("INFO: Turn light off");
  }
}

// function called to publish the state of the led (on/off)
void publishLightState() {
  if (m_light_state) {
    client.publish(MQTT_LIGHT_STATE_TOPIC, LIGHT_ON, true);
  } else {
    client.publish(MQTT_LIGHT_STATE_TOPIC, LIGHT_OFF, true);
  }
}

// function called to publish the brightness of the led
void publishLightBrightness() {
  snprintf(m_msg_buffer, MSG_BUFFER_SIZE, "%d", map(m_light_brightness, 0, 5000, 0, 255));
  client.publish(MQTT_LIGHT_BRIGHTNESS_STATE_TOPIC, m_msg_buffer, true);
}


// function called to publish the command to change the state of the led (on/off)
void publishLightStateCommand() {
  //if (m_light_state) {
  //  client.publish(MQTT_LIGHT_COMMAND_TOPIC, LIGHT_ON, true);
  //} else {
  //  client.publish(MQTT_LIGHT_COMMAND_TOPIC, LIGHT_OFF, true);
  //}
}

// function called to publish the command to change brightness of the led
void publishLightBrightnessCommand() {
  //snprintf(m_msg_buffer, MSG_BUFFER_SIZE, "%d", map(m_light_brightness, 0, 5000, 0, 255));
  //client.publish(MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC, m_msg_buffer, true);
}

// function called when a MQTT message arrived
void callback(char* p_topic, byte* p_payload, unsigned int p_length) {
  // concat the payload into a string
  String payload;
  for (uint8_t i = 0; i < p_length; i++) {
    payload.concat((char)p_payload[i]);
  }
  // handle message topic
  if (String(MQTT_LIGHT_COMMAND_TOPIC).equals(p_topic)) {
    ////////////////////////////////on_from_PIR = false;
    // test if the payload is equal to "ON" or "OFF"
    if (payload.equals(String(LIGHT_ON))) {
      current_state = on_ha;
      if (m_light_state != true) {
        m_light_state = true;
        setLightState();
        publishLightState();
      }
    } else if (payload.equals(String(LIGHT_OFF))) {
      current_state = off_ha;
      if (m_light_state != false) {
        m_light_state = false;
        m_light_brightness = 0;
        setLightState();
      }
        publishLightState();
    }
  } else if (String(MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC).equals(p_topic)) {
    current_state = on_ha;
    uint8_t brightness = payload.toInt();
    if (brightness < 0 || brightness > 255) {
      // do nothing...
      return;
    } else {
      m_light_brightness = map(brightness, 0, 255, 0, 5000);
      setLightState();
      publishLightBrightness();
    }
  } else if (String(MQTT_SUN_TOPIC).equals(p_topic)) {
    if(payload.equals(String(SUNRISE))) {
      m_sun_up = true;
    } else if(payload.equals(String(SUNSET))) {
      m_sun_up = false;
    }
  }

}

void reconnect() {
  Serial.print("INFO: Attempting MQTT connection...");
  // Attempt to connect
  if (client.connect(MQTT_CLIENT_ID)) {
    Serial.println("\nINFO: connected");

    // Once connected, publish an announcement...
    // publish the initial values
    publishLightState();
    publishLightBrightness();

    // ... and resubscribe
    client.subscribe(MQTT_LIGHT_COMMAND_TOPIC);
    client.subscribe(MQTT_LIGHT_BRIGHTNESS_COMMAND_TOPIC);
    client.subscribe(MQTT_SUN_TOPIC);
  } else {
    Serial.print("ERROR: failed, rc=");
    Serial.print(client.state());
  }
}

void setup ( void ) {
  Serial.begin(115200);
  // LED PWM pin
  pinMode(5, OUTPUT);
  // PIR sensor input pin
  pinMode(D2, INPUT);
  // pushbutton input pin
  pinMode(D5, INPUT);

  #define PWM_CHANNELS 1
  const uint32 period = 5000; // * 200ns ^= 1kHz

  uint32 io_info[PWM_CHANNELS][3] = {
    // MUX, FUNC, PIN
    {PERIPHS_IO_MUX_GPIO5_U, FUNC_GPIO5, 5}
  };

  uint32 pwm_duty_init[PWM_CHANNELS] = {0};

  pwm_init(period, pwm_duty_init, PWM_CHANNELS, io_info);
  pwm_start();

  setLightState();


  // init the WiFi connection
  Serial.println();
  Serial.println();
  Serial.print("INFO: Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("INFO: WiFi connected");
  Serial.print("INFO: IP address: ");
  Serial.println(WiFi.localIP());

  //ArduinoOTA.setPassword((const char *)"123");
  ArduinoOTA.setHostname((const char *)"slaveCabinetLights");

  ArduinoOTA.onStart([]() {
    Serial.println("Start");
  });
  ArduinoOTA.onEnd([]() {
    Serial.println("\nEnd");
  });
  ArduinoOTA.onProgress([](unsigned int progress, unsigned int total) {
    Serial.printf("Progress: %u%%\r", (progress / (total / 100)));
  });
  ArduinoOTA.onError([](ota_error_t error) {
    Serial.printf("Error[%u]: ", error);
    if (error == OTA_AUTH_ERROR) Serial.println("Auth Failed");
    else if (error == OTA_BEGIN_ERROR) Serial.println("Begin Failed");
    else if (error == OTA_CONNECT_ERROR) Serial.println("Connect Failed");
    else if (error == OTA_RECEIVE_ERROR) Serial.println("Receive Failed");
    else if (error == OTA_END_ERROR) Serial.println("End Failed");
  });
  ArduinoOTA.begin();

  // init the MQTT connection
  client.setServer(MQTT_SERVER_IP, MQTT_SERVER_PORT);
  client.setCallback(callback);
}


// time from millis() when the PIR sensor no longer detected someone
unsigned long time_turned_off = 0;

// How the pushbutton should work:
//   If pressed briefly (<1s) it will turn the lights on if they are off, and off if they are on
//   If the pushbutton is held down (>1s) it will fade brightness up and down until the button
//   is released. Whatever the brightness is at that time is what the lights will be set to.

// time from millis() when the pushbutton was pushed
unsigned long pushbutton_time_pressed = 0;

// how many times we have looped in the button state
int button_counter = 0;

void state_machine() {
  if(current_state == off_pir) {
    if(!digitalRead(D5)) {
      //client.publish("kitchen/cabinetlights/pushbutton", "button pressed", true);
    //   current_state = button;
    //   pushbutton_time_pressed = millis();
    //   return;
    }
    /*if(digitalRead(D2)) {
      current_state = on_pir;
      m_light_state = true;
      m_light_brightness = 0;
      if(m_sun_up) {
        int end_brightness = 2000;
        for(int i = 0; i < 10; i++) {
          m_light_brightness += end_brightness/10;
          setLightState();
          ////////////////publishLightStateCommand();
          /////////////////publishLightBrightnessCommand();
          // we want a 250ms delay total
          delay(250/10);
        }
          publishLightStateCommand();
          publishLightBrightnessCommand();
      } else {
        for(int i = 0; i < 5; i++) {
          m_light_brightness += 1;
          setLightState();
          //////////////publishLightStateCommand();
          /////////////publishLightBrightnessCommand();
          // we want a 250ms delay total
          delay(250/5);
        }
      }
      //publishLightStateCommand();
      //publishLightBrightnessCommand();
    }*/
  } else if(current_state == on_pir) {
    if(!digitalRead(D5)) {
      //client.publish("kitchen/cabinetlights/pushbutton", "button pressed", true);
    //   //current_state = button;
    //   pushbutton_time_pressed = millis();
    //   return;
    }
    if(!digitalRead(D2)) {
      current_state = counting_down_pir;
      time_turned_off = millis();
    }
  } else if(current_state == counting_down_pir) {
    //if(digitalRead(D5)) {
    //   current_state = button;
    //   pushbutton_time_pressed = millis();
    //   return;
    //}
    if(digitalRead(D2)) {
      current_state = on_pir;
    } else if(millis() - time_turned_off > turn_off_countdown) {
      current_state = off_pir;
      m_light_state = false;
      setLightState();
      publishLightBrightnessCommand();
      publishLightStateCommand();
    }
  } else if(current_state == on_ha) {
    // this state overrides the PIR via MQTT so don't do anything here except check the pushbutton
    //if(digitalRead(D5)) {
    //   current_state = button;
    //   pushbutton_time_pressed = millis();
    //   return;
    //}
  } else if(current_state == off_ha) {
    // this state is currently no different from off_pir, so switch straight to that
    current_state = off_pir;
  } else if(current_state == button) {
    // if we are in this state the button has either been pressed, or is being held down
    if(digitalRead(D5)) {
      // the button is still being pressed
    } else {
      // the button is not being pressed
      if((millis() - pushbutton_time_pressed) < 1000) {
        // it was let go before 1s was up
      } else {
        // it was held down,
      }
    }
    if(button_counter > 10) {
      current_state = off_pir;
      button_counter = 0;
    }
    button_counter++;
    m_light_state = !m_light_state;
    setLightState();
    publishLightBrightness();
    publishLightState();
    delay(10);
  }
}

void loop ( void ) {
  ArduinoOTA.handle();

  if (!client.connected()) {
    reconnect();
  }
  state_machine();
  client.loop();
}

