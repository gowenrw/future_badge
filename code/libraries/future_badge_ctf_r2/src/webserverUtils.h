#ifndef WEBSERVERUTILS_H
#define WEBSERVERUTILS_H

// DEBUG SET HERE AND IN future_badge_ctf_r2.cpp
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS //For production
//#define DEBUGLEVEL DEBUGLEVEL_DEBUGGING 
#define DEBUGLEVEL DEBUGLEVEL_ERRORS
#include "debug.h"

#include <Arduino.h>
#include <WiFi.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>
//#include <LittleFS.h>

#define FIRMWARE_VERSION "v0.0.2"
bool shouldReboot = false;            // schedule a reboot

AsyncWebServer *server80;               // initialise webserver
AsyncWebServer *server1985;               // initialise webserver
AsyncWebServer *server3000;               // initialise webserver
AsyncWebServer *server15001;               // initialise webserver

//web config values
const String httpadminuser = "admin";
const String httpadminpassword = "admin";

void notFound(AsyncWebServerRequest *request) {
  String logmessage = "Client:" + request->client()->remoteIP().toString() + ":" + request->client()->remotePort() + " " + request->url();
  Serial.println(logmessage);
  request->send(404, "text/plain", "Not found");
}

// used by server.on functions to discern whether a user has the correct httpapitoken OR is authenticated by username and password
bool checkUserWebAuth(AsyncWebServerRequest * request, String usr, String pwd) {
  bool isAuthenticated = false;

  if (request->authenticate(usr.c_str(), pwd.c_str())) {
    Serial.println("is authenticated via username and password");
    isAuthenticated = true;
  }
  return isAuthenticated;
}

/*
// handleUpload requires LittleFS which we are no longer using
// handles uploads to the fileserver
void handleUpload(AsyncWebServerRequest *request, String filename, size_t index, uint8_t *data, size_t len, bool final) {
  // make sure authenticated before allowing upload
  //if (checkUserWebAuth(request, usr.c_str(), pwd.c_str())) {
    String logmessage = "Client:" + request->client()->remoteIP().toString() + ":" + request->client()->remotePort() + " " + request->url();
    Serial.println(logmessage);

    if (!index) {
      logmessage = "Upload Start: " + String(filename);
      // open the file on first call and store the file handle in the request object
      request->_tempFile = LittleFS.open("/" + filename, "w");
      Serial.println(logmessage);
    }

    if (len) {
      // stream the incoming chunk to the opened file
      request->_tempFile.write(data, len);
      logmessage = "Writing file: " + String(filename) + " index=" + String(index) + " len=" + String(len);
      Serial.println(logmessage);
    }

    if (final) {
      logmessage = "Upload Complete: " + String(filename) + ",size: " + String(index + len);
      // close the file handle as the upload is now done
      request->_tempFile.close();
      Serial.println(logmessage);
      request->redirect("/");
    }
  //} else {
  //  Serial.println("Auth: Failed");
  //  return request->requestAuthentication();
  //}
}
*/

// Make size of files human readable
// source: https://github.com/CelliesProjects/minimalUploadAuthESP32
String humanReadableSize(const size_t bytes) {
  if (bytes < 1024) return String(bytes) + " B";
  else if (bytes < (1024 * 1024)) return String(bytes / 1024.0) + " KB";
  else if (bytes < (1024 * 1024 * 1024)) return String(bytes / 1024.0 / 1024.0) + " MB";
  else return String(bytes / 1024.0 / 1024.0 / 1024.0) + " GB";
}

/*
// weblistFiles requires LittleFS which we are no longer using
String weblistFiles(bool ishtml = false);

// list all of the files, if ishtml=true, return html rather than simple text
// source: https://github.com/smford/esp32-asyncwebserver-fileupload-example/tree/master
String weblistFiles(bool ishtml) {
  String returnText = "";
  Serial.println("Listing files stored on SPIFFS");
  File root = LittleFS.open("/");
  File foundfile = root.openNextFile();
  if (ishtml) {
    returnText += "<table><tr><th align='left'>Name</th><th align='left'>Size</th><th></th><th></th></tr>";
  }
  while (foundfile) {
    if (ishtml) {
      returnText += "<tr align='left'><td>" + String(foundfile.name()) + "</td><td>" + humanReadableSize(foundfile.size()) + "</td>";
      returnText += "<td><button onclick=\"downloadDeleteButton(\'" + String(foundfile.name()) + "\', \'download\')\">Download</button>";
      returnText += "<td><button onclick=\"downloadDeleteButton(\'" + String(foundfile.name()) + "\', \'delete\')\">Delete</button></tr>";
    } else {
      returnText += "File: " + String(foundfile.name()) + " Size: " + humanReadableSize(foundfile.size()) + "\n";
    }
    foundfile = root.openNextFile();
  }
  if (ishtml) {
    returnText += "</table>";
  }
  root.close();
  foundfile.close();
  return returnText;
}
*/

// parses and processes webpages
// if the webpage has %SOMETHING% or %SOMETHINGELSE% it will replace those strings with the ones defined
String processor(const String& var) {
  if (var == "FIRMWARE") {
    return FIRMWARE_VERSION;
  }
/*
  if (var == "FREELittleFS") {
    return humanReadableSize((LittleFS.totalBytes() - LittleFS.usedBytes()));
  }

  if (var == "USEDLittleFS") {
    return humanReadableSize(LittleFS.usedBytes());
  }

  if (var == "TOTALLittleFS") {
    return humanReadableSize(LittleFS.totalBytes());
  }
*/
}

#include "webserver80.h"
#include "webserver1985.h"
#include "webserver3000.h"
#include "webserver15001.h"

#endif