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

### Serial
- 9600 baud
- Start the serial monitor and then do a reset from the button switch, console will then show activity

## zuno-switch.ino
Latest version, v5.
BinarySwitch updated to have now getters and setters functions. No variable anymore.
That will help in debug on serial port.
Noticed some mismatch between pin values and zwave values sent.
Switch|Pin|ZWave
-|-|-
OFF|0 (LOW)|0
ON|1 (HIGH)|255

Switch mapping
Switch|Pin
-|-
1 | 03
2 | 04
3 | 05
4 | 06
5 | 19
6 | 20
7 | 21
8 | 22


Maybe issue is due on reporting the ON value 1 instead of 255. Let's patch and check.


## zuno-switch1.ino
This sketch manages 4 pins, the 19 to 22 by doing a single switch on them.
They are exposed to the controller as binary / bool values.
A custom battery metter is exposed but the value is a constant.
The **FLIRS powersave mode** is enabled but the sleep mode is never called so it's like the **always on** profile.

## zuno-switch2.ino
Same as the 1 and adding pins 3 to 6.

## zuno-switch3.ino
This release is trying to get less lag on requests.
- Big code cleanup
- Removed the FLIRS powersave mode so the battery monitor is disabled (Zuno SDK)
- Removed the sleep inside the loop code
- Adding 2 "virtual pins" managing respectively the channels 1-4 and 5-8.

## zuno-switch4.ino
New version of zwave make the module to hang during get/set pin values.
ZWave connection gets lost because the set value is continously sent to device.
This version has many patches but does not succeed.




## Home assistant
Press service button 3 times to integrate into ha. S0 security seems to be not working.

## Jeedom
Jeedom is a Z Wave Controller software.
Configuration is quite simple once the device is correctly associated.

### Commands
Switch 1 status information
- Add a binary information request
- Set the class to 37 (binary switch), instance to 1 and index to 0

Switch 1 - Power ON
- Add an action (default mode) associated to the button status previously created 
- Set the same class, instance and index
- Set the command arguments to this : type=setvalue&value=0

Switch 1 - Power OFF
- Same as Power ON except the command argument value that needs to be 255 : type=setvalue&value=255



