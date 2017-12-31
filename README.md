# neoplay
A game console based on Arduino &amp; neopixel LEDs

Neoplay is a custom game console based on the Arduino board and neopixel LED strips. The project is currently in its early stage and will be documented and released as Open Source later.
The repository contains the console's "firmware" (makes me chuckle to call it that) and the individual games.

## Release version
The release version is supposed to

* work based on an Arduino Uno or Due
* have a 11x11 neopixel RGB LED matrix (yes, a total resolution of 121 pixels!)
* beep & buzz
* use 9 pin sub D joysticks (Atari & Commodore) as input device
* have an on/off switch, a reset and a number of players button
* support multiple games!

The idea is that the Neoplay can be updated with additional games easily by just compiling it with new game code. The "firmware" and IO related code is kept separately.

## Current version

What it does already

* basic separation of system and game code
* 1 & 2 player switch buttons and LED indicators
* reset button
* 1 player support
* early version of the first game
* sound support

What it does not yet

* 2 player mode (I'm missing some parts and need to upgrade to Arduino Due as I'm running out of IO pins)
* console bootup intro
* main menu with game selection
* reset to main menu
* ...more games!

Feel free to join the project, but don't expect too much, it's only for fun and I don't have too much time right now ;)
