#ifndef WEBSERVER1985_H
#define WEBSERVER1985_H

#include "webserverUtils.h"

#include <Arduino.h>
#include <WiFi.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>
//#include <LittleFS.h>

#include "webpages1985.h"
#include "webcommon.h"

const String usr1985 = "mcfly";
const String pwd1985 = "N0tAchicken";

// configure web server
void configureWebServer1985() {

  // if url isn't found
  server1985->onNotFound(notFound);

  // run handleUpload function when any file is uploaded
  //server1985->onFileUpload(handleUpload);

  // visiting this page will cause you to be logged out
  server1985->on("/logout", HTTP_GET, [](AsyncWebServerRequest * request) {
    request->requestAuthentication();
    request->send(401);
  });

  // presents a "you are now logged out" webpage
  server1985->on("/logged-out", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + " " + request->url();
    Serial.println(logmessage);
    request->send_P(401, "text/html", logout_html1985, processor);
  });

  server1985->on("/", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();

    if (checkUserWebAuth(request, usr1985, pwd1985)) {
      logmessage += " Auth: Success";
      Serial.println(logmessage);
      request->send_P(200, "text/html", index_html1985, processor);
    } else {
      logmessage += " Auth: Failed";
      Serial.println(logmessage);
      return request->requestAuthentication();
    }
  });

  server1985->on("/index.html", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();

    if (checkUserWebAuth(request, usr1985, pwd1985)) {
      logmessage += " Auth: Success";
      Serial.println(logmessage);
      request->send_P(200, "text/html", index_html1985, processor);
    } else {
      logmessage += " Auth: Failed";
      Serial.println(logmessage);
      return request->requestAuthentication();
    }
  });

  server1985->on("/css/future-style.css", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();

    Serial.println(logmessage);
    request->send_P(200, "text/html", future_style_css, processor);
  });

  server1985->on("/js/jquery-1.11.3.min.js", HTTP_GET, [](AsyncWebServerRequest * request) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + + " " + request->url();

    Serial.println(logmessage);
    request->send_P(200, "text/html", jquery_1_11_3_min_js, processor);
  });

}

#endif