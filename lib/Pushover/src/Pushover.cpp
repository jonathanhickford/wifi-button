#include "Pushover.h"

Pushover::Pushover (const char* token, const char* user, const char* endpoint, const char* fingerprint) {
  pushover_user = user;
  pushover_token = token;
  pushover_endpoint = endpoint;
  pushover_fingerprint = fingerprint;
}


void Pushover::send_message(const char* title, const char* message) {
  Serial.println("[Pushover] message:");
  Serial.println(title);
  Serial.println(message);
  Serial.println(pushover_user);
  Serial.println(pushover_token);
  String content = create_body(title, message);
  Serial.println("[Pushover] content:");
  Serial.println(content);
  HTTPClient http;

  Serial.println("[HTTP] begin...");
  http.begin(pushover_endpoint, pushover_fingerprint);
  http.addHeader("Content-Type", "application/x-www-form-urlencoded");
  Serial.println("[HTTP] POST...");
  int httpResponseCode = http.POST(content);

  if(httpResponseCode > 0) {
    Serial.printf("[HTTP] POST response code: %d\n", httpResponseCode);
    if(httpResponseCode >= 200 && httpResponseCode < 300) {
        Serial.println("[HTTP] success...");
    } else {
        Serial.println("[HTTP] fail...");
    }
    String payload = http.getString();
    Serial.println(payload);
  }
}

/* Private methods */

String Pushover::create_body(const char* title, const char* message) {
  return "token=" + String(pushover_token) +
   "&user=" + String(pushover_user) +
   "&title=" + Pushover::URLEncode(title) +
   "&message=" + Pushover::URLEncode(message);
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
