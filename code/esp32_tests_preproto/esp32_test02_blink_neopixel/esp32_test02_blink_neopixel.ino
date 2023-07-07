#include <Adafruit_NeoPixel.h>
#define PIN 18

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(1, PIN, NEO_RGB + NEO_KHZ800);

void setup() {
  pixels.begin(); // This initializes the NeoPixel library.
}

void loop() {
  pixels.setPixelColor(0, pixels.Color(0,0,0));
  pixels.show();
  delay(1500);
  pixels.setPixelColor(0, pixels.Color(255,0,0));
  pixels.show();
  delay(500);
  pixels.setPixelColor(0, pixels.Color(0,255,0));
  pixels.show();
  delay(500);
  pixels.setPixelColor(0, pixels.Color(0,0,255));
  pixels.show();
  delay(500);
}
