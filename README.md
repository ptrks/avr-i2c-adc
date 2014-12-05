avr-i2c-adc
===========

This repo will help you get started with using the PCF8591 A/D & D/A I2C capable converter. 


###Prerequisites
To be able to run these examples you will need an ATmega328/128 microcontroller and a PCF8591 module. I picked up a really awesome module on Amazon that has a built in trim pot, photoresistor and thermistor. This allowed for very fast verification of communication and A/D sampling. This module also has an LED attached to the D/A converter for quick visual verification of values being written to it.

* [Amazon link to the exact module I am using](http://www.amazon.com/gp/product/B00BXX4UWC/ref=oh_aui_detailpage_o01_s00?ie=UTF8&psc=1)

###Getting Started
Hooking up the PCF8591 module to your micocontroller is super easy. The only connections required are SDA,SCL,GND and VCC. Here is a table showing the I2C (TWI) pins on bare bones microcontrollers and the popular Arduino Uno.

| Pin Function  | ATmega328p    | ATmega128   | Arduino UNO |
|:---------------:|:---------------:|:------------:|:-----------------------------------:|
| SDA    | PC4   | PC4  | Analog Input 4     |
| SCL  | PC5   | PC5  | Analog Input 5    |



###Compiling and Flashing

My project is using an ATmega328p with a 16Mhz clock. Update CMakeLists.txt as needed:

  * Microcontroller : `set(MCU   atmega328p)`
  * Clockspeed : `set(F_CPU 16000000)`
  * Programmer: `set(PROG_TYPE usbasp)`


```
git clone https://github.com/patrick--/avr-i2c-adc
cd avr-i2c-adc
mkdir build
cd build
cmake ..
make flash
