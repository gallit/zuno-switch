# Z Wave Zuno
This repo is used to store a zuno module projet used to manipulate 4 relays switches.
The module is managed by a Jeedom Z Wave Controller.

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
Comming next

