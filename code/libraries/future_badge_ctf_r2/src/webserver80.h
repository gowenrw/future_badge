#ifndef WEBSERVER80_H
#define WEBSERVER80_H

#include "webserverUtils.h"

#include <Arduino.h>
#include <WiFi.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>
//#include <LittleFS.h>

#include "webpages80.h"
#include "webcommon.h"

const String usr80 = "admin";
const String pwd80 = "adminsrule";

// configure web server
void configureWebServer80() {


  // if url isn't found
  server80->onNotFound(notFound);

  // run handleUpload function when any file is uploaded
  //server80->onFileUpload(handleUpload);

  // visiting this page will cause you to be logged out
  server80->on("/logout", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->requestAuthentication();
    request->send(401);
  });

  server80->on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();

    Serial.println(logmessage);
    request->send_P(200, "text/html", index_html80, processor);
  });

  server80->on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();

    Serial.println(logmessage);
    request->send_P(200, "text/html", index_html80, processor);
  });

  server80->on("/notes.txt", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();

    Serial.println(logmessage);
    request->send_P(200, "text/html", notes_txt80, processor);
  });

  server80->on("/listfiles", HTTP_GET, [](AsyncWebServerRequest * request)
  {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + " " + request->url();
    if (checkUserWebAuth(request, usr80, pwd80)) {
      logmessage += " Auth: Success";
      Serial.println(logmessage);
      request->send(200, "text/plain", "LittleFS Not Enabled, Sorry.");
      //request->send(200, "text/plain", weblistFiles(true)); //requires littlefs
    } else {
      logmessage += " Auth: Failed";
      Serial.println(logmessage);
      return request->requestAuthentication();
    }
  });

  server80->on("/reboot", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + " " + request->url();

    Serial.println(logmessage);
    request->send(200, "text/html", reboot_html80);
    shouldReboot = true;
  });
}

#endif