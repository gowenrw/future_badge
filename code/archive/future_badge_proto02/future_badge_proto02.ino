#include <Adafruit_NeoPixel.h>
#include <WiFi.h>
#include <Arduino.h>

// NeoPixel PIN VALUES
#define NEO01Pin 18   // 18 corresponds to GPIO18
#define NEO02Pin 19   // 18 corresponds to GPIO19

// Two color RY LED PIN VALUES
// The A pin is Yellow and the B pin is Red
#define LED31A 12  // 12 corresponds to GPIO12
#define LED31B 13  // 13 corresponds to GPIO13
#define LED32A 27
#define LED32B 14
#define LED33A 25
#define LED33B 26
#define LED34A 32
#define LED34B 33

// One color B/W LED PIN VALUES
#define LEDB01 23
#define LEDB02 22
#define LEDB03 21
#define LEDB04 5
#define LEDW05 17
#define LEDW06 16

// Touch PIN VALUE
#define TouchPin 4  // 4 corresponds to GPIO4 - Touch0

// PWM Properties
const int freq = 1000;
const int resolution = 8;
const int LED31Apwm = 0;
const int LED31Bpwm = 1;
const int LED32Apwm = 2;
const int LED32Bpwm = 3;
const int LED33Apwm = 4;
const int LED33Bpwm = 5;
const int LED34Apwm = 6;
const int LED34Bpwm = 7;

// Define NeoPixel Strips - (Num pixels, pin to send signals, pixel type, signal rate)
Adafruit_NeoPixel NEO01 = Adafruit_NeoPixel(2, NEO01Pin, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel NEO02 = Adafruit_NeoPixel(2, NEO02Pin, NEO_RGB + NEO_KHZ800);

// Touch Properties
int TouchThreshold = 12;
int TouchValue = 14;

// Debug Serial - If set greater than 0 it send lots of things to serial for debugging
int DebugSerial = 1;

// WIFI status codes
const char* wl_status_to_string(wl_status_t status) {
  switch (status) {
    case WL_NO_SHIELD: return "WL_NO_SHIELD";
    case WL_IDLE_STATUS: return "WL_IDLE_STATUS";
    case WL_NO_SSID_AVAIL: return "WL_NO_SSID_AVAIL";
    case WL_SCAN_COMPLETED: return "WL_SCAN_COMPLETED";
    case WL_CONNECTED: return "WL_CONNECTED";
    case WL_CONNECT_FAILED: return "WL_CONNECT_FAILED";
    case WL_CONNECTION_LOST: return "WL_CONNECTION_LOST";
    case WL_DISCONNECTED: return "WL_DISCONNECTED";
  }
}

// WiFi & BT Functions
void disableWiFi(){
    //adc_power_off();
    WiFi.disconnect(true);  // Disconnect from the network
    WiFi.mode(WIFI_OFF);    // Switch WiFi off
    Serial.println("WiFi disabled!");
}
void disableBluetooth(){
    btStop();
    Serial.println("Bluetooth stopped!");
}
void setModemSleep() {
    disableWiFi();
    disableBluetooth();
    setCpuFrequencyMhz(80);
}
void enableWiFi(){
    //adc_power_on();
    delay(200);
    WiFi.disconnect(false);  // Reconnect the network
    WiFi.mode(WIFI_STA);    // Switch WiFi on
    delay(200);
    Serial.println("WiFi Started!");
    //WiFi.begin(STA_SSID, STA_PASS);
    //while (WiFi.status() != WL_CONNECTED) {
    //    delay(500);
    //    Serial.print(".");
    //}
    //Serial.println("WiFi connected");
    //Serial.println("IP address: ");
    //Serial2\.println(WiFi.localIP());
}
void wakeModemSleep() {
    setCpuFrequencyMhz(240);
    enableWiFi();
}

// SETUP - RUN ONCE
void setup(){
  // Add a delay to allow opening serial monitor
  delay(300);

  // Turn Off WiFi/BT
  setModemSleep();

  // Playing with other sleep methods
  //WiFi.mode(WIFI_OFF);
  //esp_sleep_enable_timer_wakeup(9000000);
  //esp_light_sleep_start();

  // configure LED PWM functionalitites per channel
  ledcSetup(LED31Apwm, freq, resolution);
  ledcSetup(LED31Bpwm, freq, resolution);
  ledcSetup(LED32Apwm, freq, resolution);
  ledcSetup(LED32Bpwm, freq, resolution);
  ledcSetup(LED33Apwm, freq, resolution);
  ledcSetup(LED33Bpwm, freq, resolution);
  ledcSetup(LED34Apwm, freq, resolution);
  ledcSetup(LED34Bpwm, freq, resolution);

  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED31A, LED31Apwm);
  ledcAttachPin(LED31B, LED31Bpwm);
  ledcAttachPin(LED32A, LED32Apwm);
  ledcAttachPin(LED32B, LED32Bpwm);
  ledcAttachPin(LED33A, LED33Apwm);
  ledcAttachPin(LED33B, LED33Bpwm);
  ledcAttachPin(LED34A, LED34Apwm);
  ledcAttachPin(LED34B, LED34Bpwm);

  //Normal LED output
  pinMode(LEDB01, OUTPUT);
  pinMode(LEDB02, OUTPUT);
  pinMode(LEDB03, OUTPUT);
  pinMode(LEDB04, OUTPUT);
  pinMode(LEDW05, OUTPUT);
  pinMode(LEDW06, OUTPUT);

  // Initializes the NeoPixels
  NEO01.begin();
  NEO02.begin(); 

  // Set Neopixel Brightness (0-255 scale)
  NEO01.setBrightness(200);
  NEO02.setBrightness(200);
  
  // setup the serial output baud rate
  Serial.begin(115200);
}

// LOOP - MAIN 
void loop(){
  // Set Delay Time [in ms]
  int DelayTime = 20;

  // Dynamically adjust touch threshold UP to account for
  // Assembly conditions and battery vs usb
  TouchValue = touchRead(TouchPin);
  if ( (TouchValue / TouchThreshold) > 2 ) { TouchThreshold = int(TouchThreshold * 1.8); }

  // Display WIFI status
  if (DebugSerial > 0) {
    Serial.print("WiFi Status: ");
    Serial.println(wl_status_to_string(WiFi.status()));
  }

  // Iterate 0 to 255
  for(int i=0; i<256; i++){

    // Set position value to iteration
    int pos = i;
    //
    // First of three position groups 0-84
    if (pos < 85) {
      //
      // BLUE LEDS
      if (pos % 2) {
        digitalWrite(LEDB01, HIGH);
        digitalWrite(LEDB03, LOW);
      } else {
        digitalWrite(LEDB01, LOW);
        digitalWrite(LEDB03, HIGH);
      }
      digitalWrite(LEDB02, HIGH);
      digitalWrite(LEDB04, HIGH);
      // WHITE LEDS
      digitalWrite(LEDW05, LOW);
      digitalWrite(LEDW06, LOW);
      //
      // RY PWM LEDS
      //
      // Start off and slowly get brighter to full on
      ledcWrite(LED31Apwm, int(pos*3));
      ledcWrite(LED32Bpwm, int(pos*3));
      ledcWrite(LED33Apwm, int(pos*3));
      ledcWrite(LED34Bpwm, int(pos*3));
      // Start on and slowly get dimmer to full off
      ledcWrite(LED31Bpwm, int(255 - (pos*3)));
      ledcWrite(LED32Apwm, int(255 - (pos*3)));
      ledcWrite(LED33Bpwm, int(255 - (pos*3)));
      ledcWrite(LED34Apwm, int(255 - (pos*3)));
      //
      // Flame NeoPixel Red=ON Green=Cycle Blue=OFF (R+G=Y)
      //
      // Red 255 Green ++ Blue 0
      NEO01.setPixelColor(0, 255, int(pos), 0);
      // Red 255 Green -- Blue 0
      NEO01.setPixelColor(1, 255, int(84 - (pos)), 0);
      //
      // Title NeoPixel Color Cycle
      //
      // Red 255-0 Green 0-255
      NEO02.setPixelColor(0, int(255 - (pos*3)), int(pos*3), 0);
      // Blue 255-0 Red 0-255
      NEO02.setPixelColor(1, int(pos*3), 0, int(255 - pos*3));
    //
    // Second of three position groups 0-84
    } else if (pos < 170) {
      pos = pos - 85;
      //
      // BLUE LEDS
      if (pos % 2) {
        digitalWrite(LEDB02, HIGH);
        digitalWrite(LEDB04, LOW);
      } else {
        digitalWrite(LEDB02, LOW);
        digitalWrite(LEDB04, HIGH);
      }
      digitalWrite(LEDB01, HIGH);
      digitalWrite(LEDB03, HIGH);
      // WHITE LEDS
      digitalWrite(LEDW05, LOW);
      digitalWrite(LEDW06, LOW);
      //
      // RY PWM LEDS
      //
      // Start off and slowly get brighter to full on
      ledcWrite(LED31Bpwm, int(pos*3));
      ledcWrite(LED32Apwm, int(pos*3));
      ledcWrite(LED33Bpwm, int(pos*3));
      ledcWrite(LED34Apwm, int(pos*3));
      // Start on and slowly get dimmer to full off
      ledcWrite(LED31Apwm, int(255 - (pos*3)));
      ledcWrite(LED32Bpwm, int(255 - (pos*3)));
      ledcWrite(LED33Apwm, int(255 - (pos*3)));
      ledcWrite(LED34Bpwm, int(255 - (pos*3)));
      //
      // Flame NeoPixel Red=ON Green=Cycle Blue=OFF (R+G=Y)
      //
      // Red 255 Green ++ Blue 0
      NEO01.setPixelColor(1, 255, int(pos), 0);
      // Red 255 Green -- Blue 0
      NEO01.setPixelColor(0, 255, int(84 - (pos)), 0);
      //
      // Title NeoPixel Color Cycle
      //
      // Green 255-0 Blue 0-255
      NEO02.setPixelColor(0, 0, int(255 - (pos*3)), int(pos*3));
      // Red 255-0 Green 0-255
      NEO02.setPixelColor(1, int(255 - (pos*3)), int(pos*3), 0);
    //
    // Third of three position groups 0-84
    } else {
      pos = pos -170;
      //
      // BLUE LEDS
      digitalWrite(LEDB01, HIGH);
      digitalWrite(LEDB02, HIGH);
      digitalWrite(LEDB03, HIGH);
      digitalWrite(LEDB04, HIGH);
      //
      // Split third group for things that need even number of transitions
      if (pos <43) {
        // WHITE LEDS
        int wr05 = random(0,15);
        if (wr05 >9) { digitalWrite(LEDW05, HIGH); } else { digitalWrite(LEDW05, LOW); }
        int wr06 = random(0,15);
        if (wr06 >9) { digitalWrite(LEDW06, HIGH); } else { digitalWrite(LEDW06, LOW); }
        //
        // RY PWM LEDS
        //
        // Start off and slowly get brighter to full on
        ledcWrite(LED31Apwm, int(pos*6));
        ledcWrite(LED32Bpwm, int(pos*6));
        ledcWrite(LED33Apwm, int(pos*6));
        ledcWrite(LED34Bpwm, int(pos*6));
        // Start on and slowly get dimmer to full off
        ledcWrite(LED31Bpwm, int(255 - (pos*6)));
        ledcWrite(LED32Apwm, int(255 - (pos*6)));
        ledcWrite(LED33Bpwm, int(255 - (pos*6)));
        ledcWrite(LED34Apwm, int(255 - (pos*6)));
        //
        // Flame NeoPixel Red=ON Green=ON/OFF Blue=OFF (R+G=Y)
        //
        // Red 255 Green 25 Blue 0
        NEO01.setPixelColor(0, 255, 25, 0);
        // Red 255 Green 0 Blue 0
        NEO01.setPixelColor(1, 255, 0, 0);
      //
      // Split third group for things that need even number of transitions
      } else {
        // WHITE LEDS
        digitalWrite(LEDW05, LOW);
        digitalWrite(LEDW06, LOW);
        //
        // RY PWM LEDS
        //
        // Start off and slowly get brighter to full on
        ledcWrite(LED31Bpwm, int((pos-43)*6));
        ledcWrite(LED32Apwm, int((pos-43)*6));
        ledcWrite(LED33Bpwm, int((pos-43)*6));
        ledcWrite(LED34Apwm, int((pos-43)*6));
        // Start on and slowly get dimmer to full off
        ledcWrite(LED31Apwm, int(255 - ((pos-43)*6)));
        ledcWrite(LED32Bpwm, int(255 - ((pos-43)*6)));
        ledcWrite(LED33Apwm, int(255 - ((pos-43)*6)));
        ledcWrite(LED34Bpwm, int(255 - ((pos-43)*6)));
        //
        // Flame NeoPixel Red=ON Green=ON/OFF Blue=OFF (R+G=Y)
        //
        // Red 255 Green 25 Blue 0
        NEO01.setPixelColor(1, 255, 25, 0);
        // Red 255 Green 0 Blue 0
        NEO01.setPixelColor(0, 255, 0, 0);
      }
      //
      // Title NeoPixel Color Cycle
      //
      // Blue 255-0 Red 0-255
      NEO02.setPixelColor(0, int(pos*3), 0, int(255 - pos*3));
      // Green 255-0 Blue 0-255
      NEO02.setPixelColor(1, 0, int(255 - (pos*3)), int(pos*3));
    }    
    NEO01.show();
    NEO02.show();
    // Print current Iteration value to serial console for troubleshooting
    if (DebugSerial > 0) {
      Serial.print(" Iteration=");
      Serial.print(i);
      Serial.print(" Position=");
      Serial.print(pos);
    }
    //
    // TOUCH
    //
    //Read Touch Value
    TouchValue = touchRead(TouchPin);
    // Do Stuff If We Detect a Touch
    if (TouchValue < TouchThreshold) {
      setModemSleep();
      // Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial > 0) {
        Serial.print(" TOUCHED=");
        Serial.print(TouchValue);
        Serial.print("/");
        Serial.print(TouchThreshold);
      }
      //
      // LED BOOP EFFECT - OVERRIDES PRIOR LED SETTINGS BEFORE DELAY
      //
      // BLUE LEDS
      digitalWrite(LEDB01, HIGH);
      digitalWrite(LEDB02, HIGH);
      digitalWrite(LEDB03, HIGH);
      digitalWrite(LEDB04, HIGH);
      // WHITE LEDS
      digitalWrite(LEDW05, HIGH);
      digitalWrite(LEDW06, HIGH);
      // RY PWM LEDS
      ledcWrite(LED31Apwm, 255);
      ledcWrite(LED32Apwm, 255);
      ledcWrite(LED33Apwm, 255);
      ledcWrite(LED34Apwm, 255);
      ledcWrite(LED31Bpwm, 0);
      ledcWrite(LED32Bpwm, 0);
      ledcWrite(LED33Bpwm, 0);
      ledcWrite(LED34Bpwm, 0);
      // Flame NeoPixel
      NEO01.setPixelColor(0, 255, 84, 0);
      NEO01.setPixelColor(1, 255, 84, 0);
      NEO01.show();
      // Title NeoPixel
      NEO02.setPixelColor(0, 255, 255, 255);
      NEO02.setPixelColor(1, 255, 255, 255);
      NEO02.show();
    // Do Stuff If We DONT Detect a Touch
    } else {
      // Print current Touch value/threshold to serial console for troubleshooting
      if (DebugSerial > 0) {
        Serial.print(" Touch=");
        Serial.print(TouchValue);
        Serial.print("/");
        Serial.print(TouchThreshold);
      }
    }
    // Print Carriage Return for debug output
    if (DebugSerial > 0) {    
      Serial.println();
    }
    // Pause the loop to display LEDS
    delay(DelayTime);
  }
}