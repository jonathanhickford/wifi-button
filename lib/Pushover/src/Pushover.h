#ifndef PUSHOVER_H
#define PUSHOVER_H

#include <ESP8266HTTPClient.h>

class Pushover {
private:
  const char* pushover_token;
  const char* pushover_user;

  String URLEncode(const char* msg);
  String create_body(const char* title, const char* message);

public:
  Pushover(const char* token, const char* user);

  void send_message(const char* title, const char* message);
};

#endif
