# Teensy LC capactive touch button demo board
Capactive touch button demo board for Teensy LC with Adafruit 128x64 OLED (SPI)

## Shared Project
* This is what was ordered and tested
* URL: https://oshpark.com/shared_projects/J02KZSsn
* Project Name: Teensy LC with OLED & Touch [f37453f]
* File: teensybig-oled.kicad_pcb
* Repo: https://github.com/pdp7/teensy-big-oled
* Commit: f37453f   
* ISSUE: 
  * OLED GND not connected to GND plane.
  *  Temporary fix: solder wire from OLED GND to TEENSY GND

## License
This project released under the CERN Open Hardware v1.2 License

**Note:** `teensy-touch.ino` contains code based on:
* "Capacitive sensors with the Teensy 3.0"
  * http://njhurst.com/blog/01356576041
* SSD1306 display code based on example by Paul Stoffregen:
  * https://www.pjrc.com/teensy/td_libs_SSD1306.html
