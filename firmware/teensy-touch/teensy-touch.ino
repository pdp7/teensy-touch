/*
   Test of Cap Touch buttons with Teensy LC

   file: teensy-touch.ino

   gist: https://gist.github.com/pdp7/6503aae568da2d0df85f56d2f1e47c5e

   based on: "Capacitive sensors with the Teensy 3.0"
   http://njhurst.com/blog/01356576041

   SSD1306 display code based on example by Paul Stoffregen:
   https://www.pjrc.com/teensy/td_libs_SSD1306.html
*/

/*
   Adafruit_SSD1306 library changes for upside down Adafruit i2c 128x64 OLED:

   gist: https://gist.github.com/pdp7/687d0db32b30148779b3ff5346c3955e

   path: hardware/teensy/avr/libraries/Adafruit_SSD1306/Adafruit_SSD1306.h
      #define SSD1306_128_64
      //   #define SSD1306_128_32
      //   #define SSD1306_96_16

   forum post: "Re: SSD1306 flip lcd"
      https://forums.adafruit.com/viewtopic.php?f=47&t=25438&sid=c8bd3b6d598bd14259abb4e25cdd43a9

   path: hardware/teensy/avr/libraries/Adafruit_SSD1306/Adafruit_SSD1306.cpp
      //ssd1306_command(SSD1306_SEGREMAP | 0x1);
      ssd1306_command(SSD1306_SEGREMAP);
      //ssd1306_command(SSD1306_COMSCANDEC);
      ssd1306_command(SSD1306_COMSCANINC);

*/

#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// based on SSD1306 example by Paul Stoffregen
// using software SPI (the default case):
// https://www.pjrc.com/teensy/td_libs_SSD1306.html
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

#define THRESHOLD 1800
#define NBUTTON 11
#define NULL_VALUE -1

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.println("Teensy LC cap touch test");
  display.display();
  delay(1000);
  display.clearDisplay();
  display.display();
}

// the loop() methor runs over and over again,
// as long as the board has power

void loop() {
  /*
    int a = touchRead(A9);
    int b = touchRead(A8);
    Serial.println((a - b) * 1000 / (a + b));
    delay(100);
  */
  int reading = 0;
  int val = 0;
  int disp_sample = NULL_VALUE;
  String label;

  int sample[NBUTTON];
  String desc[NBUTTON] = { "CAP15", "CAP16", "CAP17", "CAP18",
                           "CAP19", "CAP22", "CAP23", "CAP0",
                           "CAP1",  "CAP3",  "CAP4"
                         };
  int pin[NBUTTON] =     {  A1,      A2,      A3,      A4,
                            A5,      A8,      A9,       0,
                            1,       3,       4
                         };

  // TODO: support simultaneous button presses
  for (int i = 0; i < NBUTTON; i++) {

    sample[i] = touchRead(pin[i]);

    /*
        NOTE: only one pressed button
        will "win" for each iteration
        of loop(). Thus "multi-touch"
        is not supported.
    */
    if (sample[i] > THRESHOLD) {
      disp_sample = i;
    }

    Serial.print(i);
    Serial.print("\t");
    Serial.print(sample[i]);
    Serial.print("\t");
    Serial.print(pin[i] );
    Serial.print("\t");
    Serial.print(desc[i] );
    Serial.print("\t");
    Serial.print( disp_sample );
    Serial.println();
  }

  display.clearDisplay();
  display.setCursor(0, 0);
  display.setTextColor(WHITE);
  display.setTextSize(2);

  if (disp_sample > -1) {
    display.println("touched:");

    display.setTextSize(3);
    display.print("<");
    display.print(desc[disp_sample]);
    display.println(">");

    display.setTextSize(2);
    display.print("value:");
    display.println(sample[disp_sample]);
  } else {
    display.println("Touch any button");
  }
  display.display();
  delay(100);

}
