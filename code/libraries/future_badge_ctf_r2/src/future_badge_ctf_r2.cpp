#include "future_badge_ctf_r2.h"

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClient.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>
//#include <LittleFS.h>

//#include "LittleFS_Util.h"

#include "webserverUtils.h"

// DEBUG SET HERE AND IN webserverUtils.h
//#define DEBUGLEVEL DEBUGLEVEL_ERRORS //For production
//#define DEBUGLEVEL DEBUGLEVEL_DEBUGGING 
#define DEBUGLEVEL DEBUGLEVEL_ERRORS
#include "debug.h"

// LittleFS Configurations
//
//#define FORMAT_LITTLEFS_IF_FAILED true
//LittleFS_Util lfsu;

// DNS Configuration
//
DNSServer dnsServer;

// WIFI Configurations
//
#define WIFI_AP_MODE true  // AP Mode required for CTF but setting false allows use of client mode
//
// Define AP ssid var
String ap_ssid;  // This gets set below to FUTURE-BADGE-<wifi_mac>
//
// Set AP password
const char* ap_password = "THEFUTUREWILLPREVAIL";
//
// Set Wifi Client mode ssid/password (to connect to)
const char* wifi_ssid     = "guest_network";     // change this for your own network
const char* wifi_password = "XXXXXXXXXXX";       // change this for your own network
//
// Set AP Static IP Addresses
IPAddress ap_Local_IP(192, 168, 1, 31);
IPAddress ap_Gateway_IP(192, 168, 1, 1);
IPAddress ap_Subnet(255, 255, 255, 0);

void ctfMain() {
  // CTF Mainline

  // Print Serial Welcome Once
  Serial.println("****************************************");
  Serial.println("******* WELCOME TO THE CTF MODE ********");
  Serial.println("****************************************");
  Serial.println("*** ACTIVATED BY LONG TOUCH ON BADGE ***");
  Serial.println("****************************************");
  Serial.println("****************************************");
  Serial.println("***** POWER CYCLE TO EXIT CTF MODE *****");
  Serial.println("****************************************");

  // Set ctfActive - use this to allow for ctf exit conditions
  bool ctfActive = true;

  /////////////////////////////////////
  // Initialize LittleFS
/*
  lfsu.init();
  if(!LittleFS.begin(FORMAT_LITTLEFS_IF_FAILED)){
      Serial.println("LittleFS Mount Failed");
      return;  
  }
  debugD("LittleFS Free: "); debuglnD(lfsu.humanReadableSize((LittleFS.totalBytes() - LittleFS.usedBytes())));
  debugD("LittleFS Used: "); debuglnD(lfsu.humanReadableSize(LittleFS.usedBytes()));
  debugD("LittleFS Total: "); debuglnD(lfsu.humanReadableSize(LittleFS.totalBytes()));
  debuglnV(lfsu.listFiles());
  lfsu.readFile(LittleFS, "/foo.txt");
  debuglnD(">>>>>>>>>>>>>>><<<<<<<<<<<<<<<<<");
*/
/*
  Serial.println( "SPIFFS-like write file to new path and delete it w/folders" );
  lfsu.writeFile2(LittleFS, "/new1/new2/new3/hello3.txt", "Hello3");
  lfsu.listDir(LittleFS, "/", 3);
  lfsu.deleteFile2(LittleFS, "/new1/new2/new3/hello3.txt");

  lfsu.listDir(LittleFS, "/", 3);
  lfsu.createDir(LittleFS, "/mydir");
  lfsu.writeFile(LittleFS, "/mydir/hello2.txt", "Hello2");
  lfsu.listDir(LittleFS, "/", 1);
  lfsu.deleteFile(LittleFS, "/mydir/hello2.txt");
  lfsu.removeDir(LittleFS, "/mydir");
  lfsu.listDir(LittleFS, "/", 1);
  lfsu.writeFile(LittleFS, "/hello.txt", "Hello ");
  lfsu.appendFile(LittleFS, "/hello.txt", "World!\r\n");
  lfsu.readFile(LittleFS, "/hello.txt");
  lfsu.renameFile(LittleFS, "/hello.txt", "/foo.txt");
  lfsu.readFile(LittleFS, "/foo.txt");
  debuglnD( "Test complete" ); 
*/

  /////////////////////////////////////
  // Configure Wifi
  //
  // Get MAC Address for AP ssid uniqueness
  byte wifi_mac[6]; 
  WiFi.macAddress(wifi_mac);
  //
  // Set AP ssid name using mac
  String ap_ssid = "FUTURE-BADGE-" + String(wifi_mac[3], HEX) + String(wifi_mac[4], HEX) + String(wifi_mac[5], HEX);
  //
  if (WIFI_AP_MODE) {
    // AP Mode
    Serial.println("Setting up AP Mode");
    Serial.println("*** AP MODE ***");
    //WiFi.mode(WIFI_AP);     // This is set by default in the main badge code
    WiFi.softAP(ap_ssid, ap_password);
    WiFi.softAPConfig(ap_Local_IP, ap_Gateway_IP, ap_Subnet);
    Serial.println();
    WiFi.softAPIP();
    IPAddress IP = WiFi.softAPIP();
    debuglnD("AP - ESP32 device IP address: " + IP.toString());
    debuglnD("Successfully Turned ON the device ESP32's Wifi-hotpspot...");
  } else {
    // Client Mode
    Serial.println("Setting up Client Mode");
    Serial.println("*** Client MODE ***");
    WiFi.mode(WIFI_STA);
    delay(500);
    Serial.print("Connecting to ");
    Serial.println(wifi_ssid);
    Serial.println("*** WIFI CLIENT BEGIN ***");
    WiFi.begin(wifi_ssid, wifi_password);
    while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
    }
    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());
  }
  debuglnD("\n\nNetwork Configuration:");
  debuglnD("----------------------");
  debugD("         SSID: "); debuglnD(WiFi.SSID());
  debugD("  Wifi Status: "); debuglnD(WiFi.status());
  debugD("Wifi Strength: "); debugD(WiFi.RSSI()); debuglnD(" dBm");
  debugD("          MAC: "); debuglnD(WiFi.macAddress());
  debugD("           IP: "); debuglnD(WiFi.localIP().toString());
  debugD("       Subnet: "); debuglnD(WiFi.subnetMask().toString());
  debugD("      Gateway: "); debuglnD(WiFi.gatewayIP().toString());
  debugD("        DNS 1: "); debuglnD(WiFi.dnsIP(0).toString());
  debugD("        DNS 2: "); debuglnD(WiFi.dnsIP(1).toString());
  debugD("        DNS 3: "); debuglnD(WiFi.dnsIP(2).toString());
  debuglnD();

  /////////////////////////////////////
  // Configure DNS
  debuglnD("Starting DNS Server");
  dnsServer.start(53, "*", WiFi.softAPIP());

  /////////////////////////////////////
  // Configure Web Servers
  debuglnD("Configuring Webservers ...");
  server80 = new AsyncWebServer(80);
  server1985 = new AsyncWebServer(1985);
  server3000 = new AsyncWebServer(3000);
  server15001 = new AsyncWebServer(15001);
  configureWebServer80();
  configureWebServer1985();
  configureWebServer3000();
  configureWebServer15001();

  /////////////////////////////////////
  // Start Web Servers
  debuglnD("Starting Webservers ...");
  server80->begin();
  server1985->begin();
  server3000->begin();
  server15001->begin();

  // Captive Portal Config
  // maybe later

  // Setup Complete
  Serial.println(".....: Setup complete :.....");

  // LOOP
  while (ctfActive) {
    // Simple LED toggle for now
    // replace with CTF code here
    digitalWrite(LEDB01, HIGH);
    digitalWrite(LEDB02, LOW);
    delay(1000);
    digitalWrite(LEDB01, LOW);
    digitalWrite(LEDB02, HIGH);
    delay(1000);
    Serial.println("****************************************");
    Serial.println("*********** CTF MODE ACTIVE ************");
    Serial.println("***** POWER CYCLE TO EXIT CTF MODE *****");
    Serial.println("****************************************");
  }
}
