#include <Adafruit_NeoPixel.h>

// NeoPixel PIN VALUES
#define NEO01Pin 18   // 18 corresponds to GPIO18
#define NEO02Pin 19   // 18 corresponds to GPIO19

// LED PIN VALUES
#define LED01Pin 12  // 12 corresponds to GPIO12
#define LED02Pin 13  // 13 corresponds to GPIO13

// Touch PIN VALUE
#define TouchPin 32  // 32 corresponds to GPIO32 - Touch9

// PWM Properties
const int freq = 1000;
const int PWMChannel0 = 0;
const int PWMChannel1 = 1;
const int resolution = 8;

// Define NeoPixel Strips - (Num pixels, pin to send signals, pixel type, signal rate)
Adafruit_NeoPixel NEO01 = Adafruit_NeoPixel(2, NEO01Pin, NEO_RGB + NEO_KHZ800);
Adafruit_NeoPixel NEO02 = Adafruit_NeoPixel(2, NEO02Pin, NEO_RGB + NEO_KHZ800);

// Touch Properties
const int TouchThreshold = 20;
int TouchValue = 21;

// SETUP - RUN ONCE
void setup(){
  // configure LED PWM functionalitites per channel
  ledcSetup(PWMChannel0, freq, resolution);
  ledcSetup(PWMChannel1, freq, resolution);
  
  // attach the channel to the GPIO to be controlled
  ledcAttachPin(LED01Pin, PWMChannel0);
  ledcAttachPin(LED02Pin, PWMChannel1);

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