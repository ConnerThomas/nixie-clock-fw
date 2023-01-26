# nixie-clock-fw
Firmware for NCS314 HW2.3 with PlatformIO support

Forked from h3xcat's rewrite of the original gra-afch code. 

# Required Libraries

* https://github.com/bhagman/Tone
* https://github.com/PaulStoffregen/Time


# Disclaimer

This repo has been further modified to be compadible with HW v2.3, with an Arduino Mega 2560. It may work with other boards but there is no guarantee.

# Current Features

* **Timezones with DST:** DST can be set to None, EU, or US modes.
* **GPS synchronization:** Firmware is able to detect the baud rate by itself, should be compatible with most GPS modules using NMEA protocol over serial.
* **Anti cathode poisoning (ACD):** The ACD include various modes with customizable intervals)
* **Display Interface:** Provides easy control over the nixie tubes.
* **RTTL player:** The RTTL player itself is completed, but needs Alarm implementation before its usable.

# TODO

* Menu(Buttons + IR Remote)
* LED Control
* Temperature
* Alarm
* Smooth fading between digits
* Add more anti-poisoning routines