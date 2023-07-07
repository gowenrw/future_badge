#!/bin/bash

###########
# HELP TXT
###########
Help()
{
   # Display Help
   echo "This script requires ONE argument."
   echo
   echo "Syntax: cli-compile.sh <Sketch_Name>"
   echo
}

#################
# Check For Args
#################
if [ $# -eq 0 ] || ! [ -z "$2" ]
  then
    Help
    exit;
fi

###################
# Check For Sketch
###################
if ! [ -d "$1" ]
  then
    echo "Sketch $1 Not Found"
    exit;
fi

echo "arduino-cli --config-file arduino-cli.yml compile --fqbn esp32:esp32:esp32 --build-path _build --export-binaries $1"
arduino-cli --config-file arduino-cli.yml compile --fqbn esp32:esp32:esp32 --build-path _build --export-binaries $1
