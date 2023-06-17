# Code

This is where all the project related Code / Firmware is located

## File Structure

This is the file structure of this repository

* [/](/README.md) - Home
* [/code/](/code/) - YOU ARE HERE

## Arduino IDE

The code presented here is mostly Arduino code.

In order to use this code and push new code to the ESP32 on the badge we recommend using the Arduino IDE software.
This can be downloaded for various platforms at [arduino.cc](https://www.arduino.cc/en/software).

The Arduino IDE version we are using for testing is 2.1.0 and this is the version we recommend.

Some additional setup is required to use the Arduino IDE with the ESP32 on the badge:
* Add the ESP32 boards manager URL in preferences
  * Under File->Preferences find the "Additional boards manager URLs" section and add the following
  * https://espressif.github.io/arduino-esp32/package_esp32_index.json
  * Then click OK and close the IDE.  When it is reopened it wil download the ESP32 board definitions.
* Select the board "ESP32 Dev Module"
  * You need to select a board to associate with the code even if that board is not connected
  * In the "Select Board" dropdown, choose "ESP32 Dev Module" from the list
  * The first time you do this it may download some addiotional software.
* Connect the ESP32 via USB cable and select the COM port if it is not autodetected
  * In most cases it should autodetect the port
  * Sometimes on first connect you need to help it by going to Tools->Port and choosing the port
* This code uses the AdaFruit NeoPixel library which needs to be installed
  * The library can be installed via the Arduino IDE library manager or manually
  * Installation instructions can be found at [the adafruit neopixel github page](https://github.com/adafruit/Adafruit_NeoPixel)

