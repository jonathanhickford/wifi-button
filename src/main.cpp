/**
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "Pushover.h"
#include "config.h"


void connect_to_wifi();

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();

  connect_to_wifi();

  Pushover pushover(Config::pushover_token, Config::pushover_user);
  pushover.send_message("Study", "I need you in the study");
}

void loop() {
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  delay(1000);
}


void connect_to_wifi() {
  Serial.println("Begin connection");
  WiFi.begin(Config::network, Config::password);

  Serial.print("Connecting to wifi");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println();

  Serial.print("Connected to wifi, IP address: ");
  Serial.println(WiFi.localIP());
}
