#ifndef FUTURE_BADGE_CTF_R2_H
#define FUTURE_BADGE_CTF_R2_H

#include <Arduino.h>
#include <WiFi.h>

#include <AsyncTCP.h>
#include <DNSServer.h>
#include <ESPAsyncWebSrv.h>
//#include <LittleFS.h>

// One color B/W LED PIN VALUES
#define LEDB01 23
#define LEDB02 22
#define LEDB03 21
#define LEDB04 5
#define LEDW05 17
#define LEDW06 16

void ctfMain();

#endif
