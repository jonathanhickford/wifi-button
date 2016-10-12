#include "Pushover.h"

Pushover::Pushover (const char* pushover_token, const char* pushover_user) {
  pushover_user = pushover_user;
  pushover_token = pushover_token;
}


void Pushover::send_message(const char* title, const char* message) {
  const char* url = "https://api.pushover.net/1/messages.json";
  const char* fingerprint = "27 41 80 CE F4 46 C9 02 F6 8C C0 D1 CC 72 3F D2 43 FA 35 0D";

  String content = create_body(title, message);

  HTTPClient http;

  Serial.println("[HTTP] begin...");
  http.begin(url, fingerprint);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  Serial.println("[HTTP] POST...");
  int httpResponseCode = http.POST(content);

  if(httpResponseCode > 0) {
    Serial.printf("[HTTP] POST response code: %d\n", httpResponseCode);
    if(httpResponseCode >= 200 && httpResponseCode < 300) {
      String payload = http.getString();
      Serial.println(payload);
    }
  }
}

/* Private methods */

String Pushover::create_body(const char* title, const char* message) {
  return "token=" + String(pushover_token) +
   "&user=" + String(pushover_user) +
   "&title=" + Pushover::URLEncode(title) +
   "&message" + Pushover::URLEncode(message);
}

String Pushover::URLEncode(const char* msg) {
    const char *hex = "0123456789abcdef";
    String encodedMsg = "";

    while (*msg!='\0'){
        if( ('a' <= *msg && *msg <= 'z')
                || ('A' <= *msg && *msg <= 'Z')
                || ('0' <= *msg && *msg <= '9') ) {
            encodedMsg += *msg;
        } else {
            encodedMsg += '%';
            encodedMsg += hex[*msg >> 4];
            encodedMsg += hex[*msg & 15];
        }
        msg++;
    }
    return encodedMsg;
}



/*
void send_pushover_message(const char* title, const char* message) {

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

  String content = create_pushover_body(title, message);

  client.print(String("POST ") + url +
               "Host: " + host + "\r\n" +
               "Content-Type: application/x-www-form-urlencoded\r\n" +
               "Content-Length: " + content.length() + "\r\n\r\n" +
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
*/
