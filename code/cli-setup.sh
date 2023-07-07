#!/bin/bash
now=$(date)
echo "$now" > arduino_cli_setup.log

echo "Install / Upgrade ESP32 core" |tee -a arduino_cli_setup.log
echo "##########" >>arduino_cli_setup.log

echo "arduino-cli --config-file arduino-cli.yml core search esp32" |tee -a arduino_cli_setup.log
arduino-cli --config-file arduino-cli.yml core search esp32 >>arduino_cli_setup.log 2>&1
echo "##########" >>arduino_cli_setup.log

echo "arduino-cli --config-file arduino-cli.yml core install esp32:esp32" |tee -a arduino_cli_setup.log
arduino-cli --config-file arduino-cli.yml core install esp32:esp32 >>arduino_cli_setup.log 2>&1
echo "##########" >>arduino_cli_setup.log

echo "arduino-cli --config-file arduino-cli.yml core update-index" |tee -a arduino_cli_setup.log
arduino-cli --config-file arduino-cli.yml core update-index >>arduino_cli_setup.log 2>&1
echo "##########" >>arduino_cli_setup.log

echo "arduino-cli --config-file arduino-cli.yml core upgrade" |tee -a arduino_cli_setup.log
arduino-cli --config-file arduino-cli.yml core upgrade >>arduino_cli_setup.log 2>&1
echo "##########" >>arduino_cli_setup.log

echo "Install / Upgrade Adafruit NeoPixel Library" |tee -a arduino_cli_setup.log
echo "##########" >>arduino_cli_setup.log

echo "arduino-cli --config-file arduino-cli.yml lib search 'Adafruit NeoPixel'" |tee -a arduino_cli_setup.log
arduino-cli --config-file arduino-cli.yml lib search 'Adafruit NeoPixel' >>arduino_cli_setup.log 2>&1
echo "##########" >>arduino_cli_setup.log

echo "arduino-cli --config-file arduino-cli.yml lib install 'Adafruit NeoPixel'" |tee -a arduino_cli_setup.log
arduino-cli --config-file arduino-cli.yml lib install 'Adafruit NeoPixel' >>arduino_cli_setup.log 2>&1
echo "##########" >>arduino_cli_setup.log

echo "arduino-cli --config-file arduino-cli.yml lib upgrade 'Adafruit NeoPixel'" |tee -a arduino_cli_setup.log
arduino-cli --config-file arduino-cli.yml lib upgrade 'Adafruit NeoPixel' >>arduino_cli_setup.log 2>&1
echo "##########" >>arduino_cli_setup.log
