#include <Adafruit_NeoPixel.h>

// NeoPixel PIN VALUES
#define NEO01Pin 18   // 18 corresponds to GPIO18

// LED PIN VALUES
#define LED01Pin 12  // 12 corresponds to GPIO12
#define LED02Pin 13  // 13 corresponds to GPIO13

// Touch PIN VALUE
#define TouchPin 32  // 32 corresponds to GPIO32 - Touch9

// PWM Properties
const int freq = 5000;
const int PWMChannel0 = 0;
const int PWMChannel1 = 1;
const int resolution = 8;

// Define NeoPixel Strip - (Num pixels, pin to send signals, pixel type, signal rate)
Adafruit_NeoPixel NEO01 = Adafruit_NeoPixel(1, NEO01Pin, NEO_RGB + NEO_KHZ800);

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

  // setup the serial output baud rate
  Serial.begin(115200);
}

// LOOP - MAIN 
void loop(){
  // Set Delay Time [in ms]
  int DelayTime = 20;

  // Iterate 0 to 254
  for(int i=0; i<255; i++){
    // Set the LED01 value to iteration value using esp pwm channel write
    // Start off and slowly get brighter to full on
    ledcWrite(PWMChannel0, i);
    // Set the LED02 value to 255-iteration value using esp pwm channel write
    // Start on and slowly get dimmer to full off
    ledcWrite(PWMChannel1, (255 - i));
    // NeoPixel Color Cycle
    int pos = i;
    if (pos < 85) {
      // Cycle Red & Green based on itiration number
      NEO01.setPixelColor(0, int(pos * 3), int(255 - (pos*3)), 0);
    } else if (pos < 170) {
      pos = pos - 85;
      // Cycle Red & Blue based on itiration number
      NEO01.setPixelColor(0, int(255 - pos*3), 0, int(pos*3));
    } else {
      pos = pos -170;
      // Cycle Green & Blue based on itiration number
      NEO01.setPixelColor(0, 0, int(pos*3), int(255 - pos*3));
    }    
    NEO01.show();
    // Print current Iteration value to serial console for troubleshooting
    Serial.print(" Iteration=");
    Serial.print(i);
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
  
  // Iterate 255 to 1
  for(int i=255; i>0; i--){
    // Set the LED01 value to iteration value using esp pwm channel write
    // Start on and slowly get dimmer to full off
    ledcWrite(PWMChannel0, i);
    // Set the LED02 value to 255-iteration value using esp pwm channel write
    // Start off and slowly get brighter to full on
    ledcWrite(PWMChannel1, (255 - i));
    // NeoPixel Color Cycle
    int pos = i;
    if (pos < 85) {
      // Cycle Red & Green based on itiration number
      NEO01.setPixelColor(0, int(pos * 3), int(255 - (pos*3)), 0);
    } else if (pos < 170) {
      pos = pos - 85;
      // Cycle Red & Blue based on itiration number
      NEO01.setPixelColor(0, int(255 - pos*3), 0, int(pos*3));
    } else {
      pos = pos -170;
      // Cycle Green & Blue based on itiration number
      NEO01.setPixelColor(0, 0, int(pos*3), int(255 - pos*3));
    }    
    NEO01.show();    
    // Print current Iteration value to serial console for troubleshooting
    Serial.print(" Iteration=");
    Serial.print(i);
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