---
layout: default
---

![future badge assembly hero](images/future_badge_assembly_hero.jpg)

# Future Badge Assembly Instructions

Here are the assembly instructions I put together for the future badge.

There is also a [Future Badge Soldering Walk-Through Video](https://youtu.be/ozqXjqQztUM) that you may find helpful.

## Badge Distribution Packages

The badges have been distributed in three different packages

* KIT - This is the standard kit that requires DIY soldering/assembly of all components (including 4 SMT)
* WMP - This is the "With Mounted Parts" kit that requires DIY soldering/assembly of all components EXCEPT the SMT components which have been pre-mounted on the PCB
* ASS - This is a Fully Assembled ready to wear badge

## Component List

This is the list of components that you should have available for the assembly

* Main Kit Bag (7x9in) Containing:
  * 1x PCB panel (which breaks apart for top/front and bottom/rear PCBs)
  * 1x Lanyand
  * 1x 9V Battery
  * 1x Sticker (Not Required for badge Assembly)
  * Small Component Bag (3x4in) Containing:
    * 1x ESP32 WROOM Development board
  * Large Component Bag (6x8in) Containing:
    * 1x Header Male Breakaway Strip with 1x40 Pins
    * 3x Header Female 1x4 Pins
    * 1x Header Female Keyed 2x3 Pins (Badge SAO connector)
    * 1x 9V Battery connector
    * 2x Rubber Band #8 size (1 req. 1 spare)
    * Medium Component Bag (4x6in) Containing:
      * 1x THT SS12D00 3-Pin SPDT Switch
      * 4x THT 100nF Ceramic Disc Capacitors
      * 1x THT 10uF 50V X5R 106 5.08mm Multi-Layer Ceramic Capacitor
      * 4x THT WS2812D RPIN 5mm 4-Pin Addressable LEDs
      * 4x THT Two Color (Red-Yellow) 3mm 3-Pin LEDs
      * 4x THT One Color (Blue) 3mm 2-pin Flat Top LEDs
      * 2x THT One Color (White) 3mm 2-pin Round Top LEDs
      * 14x THT 47 Ohm 6.2mm Metal Film Resistors
    * Small Component Bag (3x4in) Containing:
      * NOTE: The WMP kit has SMD components pre-assembled so this bag will not be present
      * 1x SMT CJ3139k 20V 0.66A PNP SOT-23 MOSFET Transistor
      * 1x SMT LMTOE78_03-0.5 12x12mm Step Down Power Regulator
      * 2x SMT 22uF 25V X7R 1210 Multi-Layer Ceramic Capacitor

![future badge kit](images/future_badge_kit.jpg)

## Soldering Steps

These are the assembly steps that require soldering.
I have presented them in the order I recommend they be implemented for best results.

### Surface Mount

If you are working with the standard KIT then you will need to solder the surface mount components.
If you got the WMP kit (with mounted parts) then skip these steps.

* Solder the four SMDs (surface mount devices) first
  * These parts have extra large pads allowing for hand soldering with traditional iron and solder but solder paste with hotair/hotplate also works well
  * I start with the largest and progress to the smallest of these
    * VR1 - This voltage regulator is a large (12mmx12mm!) square component with pads on the 4 corners
      * Align VR1 using the silk drawing of it on the PCB and solder the 4 corners
    * C2 and C3 - These 22uF capacitors are in a chunky 1210 package and are non-polar (she goes both ways)
      * Place C2 and C3 onto the pads and solder the 2 ends of each
    * Q1 - This MOSFET transistor is a small SOT-23 package with 3 pins (2 on one side, 1 on other)
      * Align Q1 pins with pads and solder its 3 pins

### Through Hole

If you are working with the standard KIT or the WMP kit (with mounted parts) then you will need to solder the through hole components.

* Almost all components are on the bottom/rear PCB so we start with that one
  * The top/front PCB has only headers which will be done last
* Placement of the THT (through hole technology) components on the 
  * These components are placed on the front of the PCB where the component labels are and soldered on the back side of that PCB
* I start with the resistors since there are a lot of them and they are easy to do all at once
  * There are 14 47-Ohm resistors labeled R1-R6, R10-11, R20-21. and R31-34
  * Resistors are non-polar so they can be placed in either direction.
  * Place all the resistors into the PCB bending thier legs outward to hold them in place
  * Solder all 28 resistor connections (both ends of the 14 resistors)
  * When cooled cut the component legs off at the top of the solder joints (do not cut into the solder joint)
* Capacitors are next
  * C1 - This is a blue colored 5mm wide 2 pin 10uF MLCC non-polar capacitor
  * C10, C11, C20, C21 - These are tan colored 2.5mm wide 2 pin 100nF ceramic disc non-polar capacitors
  * Place all the capacitors in thier designated places on the PCB bending legs out to hold in place
  * Solder all the capacitor connections
  * When cooled cut the component legs off at the top of the solder joints (do not cut into the solder joint)
* The traditional one color 2 pin LEDs are easy but there are two types so be careful with placement
  * D1-D4 - These are 3mm 2-pin Clear FLAT TOP LEDs that emit BLUE light
  * D5-D6 - These are 3mm 2-pin Clear ROUND TOP LEDs that emit WHITE light
  * Place the LEDs in thier designated places on the PCB bending legs out to hold in place
  * Make sure to align the LEDs properly using the silk guide to place short leg in square hole
  * DO NOT force the LED down flush with the board, stop when you feel resistance
  * Solder all the LED connections
  * When cooled cut the component legs off at the top of the solder joints (do not cut into the solder joint)
* Two color 3 pin LEDs are easy to solder but need proper alignment for colors
  * D31-34 - These are 3mm 3-pin Clear LEDs that emit RED and/or Yellow light
  * Place the LEDs in thier designated places on the PCB bending legs out to hold in place
  * Make sure to align the LEDs properly using the silk guide to place short leg in square hole
  * DO NOT force the LED down flush with the board, stop when you feel resistance
  * Solder all the LED connections
  * When cooled cut the component legs off at the top of the solder joints (do not cut into the solder joint)
* Addressable neopixel LEDs are a bit more difficult to solder given the pins are close
  * D10-D11, D20-D21 - These are 5mm 4-pin frosted short hat LEDs that are addressable RGB neopixels
  * Place the LEDs in thier designated places on the PCB bending legs out to hold in place
  * Align the LEDs properly using the silk guide to place longest leg in VDD (middle hole next to square hole)
  * DO NOT force the LED down flush with the board, stop when you feel resistance
  * Solder all the LED connections
  * When cooled cut the component legs off at the top of the solder joints (do not cut into the solder joint)
* The ESP32 development board should be easy to solder
  * ESP32 DEVKIT - This is the 30 pin ESP32 WROOM development board
  * Place the ESP32 in its designated place on the PCB using the silk guide to align with usb toward top of PCB
  * Optionally you can keep the dev board raised off the PCB inserting only enough of the legs to allow soldering
    * This avoids the need to cut excess leg length off the back of the pcb later
  * Solder all the ESP32 connections
  * When cooled, if needed, cut excess leg length off at the top of solder joints (do not cut into the solder joint)
* Switch for battery power is next
  * The battery power switch is a 3-pin SPDT switch with a 3mm lever
  * This was designed to be placed on the front of the PCB like all the other components
    * This places the switch in between the two PCBs when the badge is assembled
    * Optionally the switch can be mounted on the other side to keep it on the back
    * Mounting on the back provides easier access but also has it rub against the wearer
  * Place the switch in its designated place on the PCB in either direction
  * Solder all the switch connections
  * When cooled, if needed, cut excess leg length off at the top of solder joints (do not cut into the solder joint)
* Female headers must maintain 90 degree angle to the PCB
  * JB1-3 - These are 4-pin 2.54mm Female headers
  * We will solder these headers one at a time to allow us to adjust angle
  * Place a header into the PCB and while holding it in place solder ONE pin
  * Check the alignment to make sure it is at a 90 degree angle from the PCB
  * If angle adjustment is needed heat up that one soldered pin and move angle as needed
  * Once the header is at the proper angle solder the remaining connections
  * Repeat this for the other two headers
* Battery connector is the last component on the bottom/rear PCB
  * The 9V battery connector comes with long lead wires that will need to be cut to size
  * Do not cut the wires too short, some excess wire is ok as it can be tucked under the ESP
  * Strip about 1/8th inch (3mm) of plastic off the ends of the lead wires
  * Twist the wire strands to allow them to easily insert into the holes, optionally Tin the lead wires
  * Place the lead wires into thier designated places on the PCB
    * Red wire is placed in square hole marked +
    * Black wire is placed in round hole marked GND
  * Solder the lead wires in place
* With the bottom/rear PCB complete we can proceed to the top/front PCB
* Male headers on the top/front PCB must align with the female headers on the bottom/rear PCB
  * Prepare three 4-pin Male headers by breaking them off the provided 40-pin breakaway strip
  * These 4-pin 2.54mm Male headers will be soldered on the front side of the top/front PCB
  * With the bottom/rear PCB component side up, place the male headers into the female headers on that PCB
  * Place the top/front PCB art side up onto the male headers in the appropriate holes on three sides
  * Solder the male headers to the top/front PCB
  * When cooled remove the top/front PCB with its male headers now attached from the bottom/rear PCB
* SAO connector is keyed and needs proper alignment
  * The SAO connector is a 2x3 pin Female Keyed header that must have the key aligned
  * This will be placed on the front of the PCB, soldered on the back where the silk labels are
  * The silk guide shows that the header key should be aligned toward the top edge of PCB
  * Solder all the SAO header connections

## Additional Assembly Steps

These are the additional assembly steps that do not require soldering.

### Separating the PCBs

Breaking apart the PCBs can be done at any point.
But, since you will only be working on one PCB at a time it may make sense to do this before soldering.

* Break apart the PCBs on the mouse bites
  * To provide an even break line placing one PCB on a hard surface (like a desk) and pushing down on the other PCB works well
  * Break off the mouse bites from the PCB(s) that they are still attached to
  * Mini pliers are helpful but not required
  * The rough edges can be filed or sanded down if a smooth edge is preferred

### Final Assembly

* Take one #8 rubber band and attach either end of it to the hooks in the center of bottom/back PCB
* Connect the top/front and bottom/back PCBs via the 4 pin headers on three sides

## Wear and Enjoy!

* With switch in off position attach 9V battery to battery connector
* Slide 9V battery between the rubber band and the top/front PCB
* Attach lanyard to provided holes on bottom/rear pcb
* Wear the badge and adjust lanyard length by pushing the button on the lanyard plastic ball
* Move the switch to the on position
* Enjoy!

## Home

[Return to Home Page](/)

---

[@alt_bier](https://twitter.com/alt_bier)  - [My Contact Info](https://gowen.net/about)
