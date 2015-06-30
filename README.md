# pinger
Code and design documents for a USB-based notification bell

The pinger was made using a Minimus board programmed with the FLIP programmer. The Arduino sketch must be compiled with Arduino 1.0.3 (this is the only version that's compatibile with the Minimus). 

-- Pinger.ino -- 

This file is the Arduino sketch for the minimus board. It sets the board up to act as a USB serial port, and respond to two commands. 

ping: Sets output pin 4 (PD4) high for a few milliseconds to drive the solenoid to hit the bell.

help: Sends a helpful message to the serial port. 


PD4 is connected to a MOSFET transistor which drives the soleniod, taking power from the USB bus. 