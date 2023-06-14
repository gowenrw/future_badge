#include <Adafruit_NeoPixel.h>

// NeoPixel PIN VALUES
#define NEO01Pin 18   // 18 corresponds to GPIO18
#define NEO02Pin 19   // 18 corresponds to GPIO19

// Two color LED PIN VALUES
#define LED31A 12  // 12 corresponds to GPIO12
#define LED31B 13  // 13 corresponds to GPIO13
#define LED32A 27
#define LED32B 14
#define LED33A 25
#define LED33B 26
#define LED34A 32
#define LED34B 33

// One color LED PIN VALUES
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
const int TouchThreshold = 20;
int TouchValue = 21;

// SETUP - RUN ONCE
void setup(){
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
  int DelayTime = 10;
  digitalWrite(LEDB01, HIGH);
  digitalWrite(LEDB02, HIGH);
  digitalWrite(LEDB03, HIGH);
  digitalWrite(LEDB04, HIGH);
  digitalWrite(LEDW05, HIGH);
  digitalWrite(LEDW06, HIGH);

  // Iterate 0 to 255
  for(int i=0; i<256; i++){

    // Set position value to iteration
    int pos = i;
    if (pos < 85) {
      // Start off and slowly get brighter to full on
      ledcWrite(PWMChannel0, int(pos*3));
      // Start on and slowly get dimmer to full off
      ledcWrite(PWMChannel1, int(255 - (pos*3)));
      //
      // NeoPixel Color Cycle
      //
      // Red 255-0 Green 0-255
      NEO01.setPixelColor(0, int(255 - (pos*3)), int(pos*3), 0);
      NEO02.setPixelColor(1, int(255 - (pos*3)), int(pos*3), 0);
      // Green 255-0 Blue 0-255
      NEO01.setPixelColor(1, 0, int(255 - (pos*3)), int(pos*3));
      // Blue 255-0 Red 0-255
      NEO02.setPixelColor(0, int(pos*3), 0, int(255 - pos*3));
    } else if (pos < 170) {
      pos = pos - 85;
      // Start off and slowly get brighter to full on
      ledcWrite(PWMChannel1, int(pos*3));
      // Start on and slowly get dimmer to full off
      ledcWrite(PWMChannel0, int(255 - (pos*3)));
      //
      // NeoPixel Color Cycle
      //
      // Red 255-0 Green 0-255
      NEO02.setPixelColor(0, int(255 - (pos*3)), int(pos*3), 0);
      // Green 255-0 Blue 0-255
      NEO01.setPixelColor(0, 0, int(255 - (pos*3)), int(pos*3));
      NEO02.setPixelColor(1, 0, int(255 - (pos*3)), int(pos*3));
      // Blue 255-0 Red 0-255
      NEO01.setPixelColor(1, int(pos*3), 0, int(255 - pos*3));
    } else {
      pos = pos -170;
      if (pos <43) {
        // Start off and slowly get brighter to full on
        ledcWrite(PWMChannel0, int(pos*6));
        // Start on and slowly get dimmer to full off
        ledcWrite(PWMChannel1, int(255 - (pos*6)));        
      } else {
        // Start off and slowly get brighter to full on
        ledcWrite(PWMChannel1, int((pos-43)*6));
        // Start on and slowly get dimmer to full off
        ledcWrite(PWMChannel0, int(255 - ((pos-43)*6)));
      }
      //
      // NeoPixel Color Cycle
      //
      // Red 255-0 Green 0-255
      NEO01.setPixelColor(1, int(255 - (pos*3)), int(pos*3), 0);
      // Green 255-0 Blue 0-255
      NEO02.setPixelColor(0, 0, int(255 - (pos*3)), int(pos*3));
      // Blue 255-0 Red 0-255
      NEO01.setPixelColor(0, int(pos*3), 0, int(255 - pos*3));
      NEO02.setPixelColor(1, int(pos*3), 0, int(255 - pos*3));
    }    
    NEO01.show();
    NEO02.show();
    // Print current Iteration value to serial console for troubleshooting
    Serial.print(" Iteration=");
    Serial.print(i);
    Serial.print(" Position=");
    Serial.print(pos);
    // TOUCH
    TouchValue = touchRead(TouchPin);
    // Print current Touch value to serial console for troubleshooting
    if (TouchValue < TouchThreshold) { Serial.print(" TOUCHED="); } else { Serial.print(" Touch="); }
    Serial.print(TouchValue);
    // Print Carriage Return
    Serial.println();
    // Pause the loop to display LEDS
    delay(DelayTime);
  }
}