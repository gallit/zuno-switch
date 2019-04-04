# Z Wave Zuno
This repo is used to store a zuno module projet used to manage some devices.

## Configure the host computer
Read the documentation from the Zuno website and download the Quick Start Guide.
Take care about these settings from the Arduino IDE :
- File / Preference / Additional boards manager...
- Tools / Board / Zuno board
- Tools / Frequency / ...
- Tools / Programmer / Zuno
- Tools / Burn bootloader

## zuno-switch1.ino
This sketch manages 4 pins, the 19 to 22 by doing a single switch on them.
They are exposed to the controller as binary / bool values.
A custom battery metter is exposed but the value is a constant.
The **FLIRS powersave mode** is enabled but the sleep mode is never called so it's like the **always on** profile.

## Jeedom
Jeedom is a Z Wave Controller software.
Configuration is quite simple once the device is correctly associated.

### Commands
Comming next

