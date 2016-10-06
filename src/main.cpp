/**
 * Blink
 * Turns on an LED on for one second,
 * then off for one second, repeatedly.
 */
#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClientSecure.h>
#include "config.h"

void setup()
{
  // initialize LED digital pin as an output.
  pinMode(LED_BUILTIN, OUTPUT);

  Serial.begin(115200);
  Serial.println();
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

void loop()
{
  // turn the LED on (HIGH is the voltage level)
  digitalWrite(LED_BUILTIN, HIGH);
  // wait for a second
  delay(1000);
  // turn the LED off by making the voltage LOW
  digitalWrite(LED_BUILTIN, LOW);
   // wait for a second
  delay(1000);
}



void pushover() {
  const char* host = "api.pushover.net";
  const char* fingerprint = "27 41 80 CE F4 46 C9 02 F6 8C C0 D1 CC 72 3F D2 43 FA 35 0D";
  const int httpsPort = 443;

  WiFiClientSecure client;
  Serial.print("Connecting to ");
  Serial.println(host);

  if(!client.connect(host, httpsPort)) {
    Serial.println("connection failed");
    return;
  }

  if (client.verify(fingerprint, host)) {
    Serial.println("certificate matches");
  } else {
    Serial.println("certificate doesn't match");
  }

  String url = "/1/messages.json";
  Serial.print("requesting URL: ");
  Serial.println(url);

  String content =  "token=" + String(Config::pushover_token) +
   "&user=" + String(Config::pushover_user) +
   "&title=" + "Study" +
   "&message" + "Come+to+the+study";

  client.print(String("POST ") + url +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n\r\n" +
               "Content-Length: " + content.length() + "\r\n" +
               content + "\r\n"
              );
               Serial.println("request sent");

  while (client.connected()) {
    String line = client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
  }
  String line = client.readStringUntil('\n');
   if (line.startsWith("{\"status\":1")) {
     Serial.println("Message sent successfull!");
   } else {
     Serial.println("Message failure");
   }
   Serial.println("reply was:");
   Serial.println("==========");
   Serial.println(line);
   Serial.println("==========");
   Serial.println("closing connection");



}
