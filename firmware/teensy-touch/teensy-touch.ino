/*
 * Test of Capactive Touch buttons with Teensy LC
 * 
 * file: teensy-touch.ino
 * 
 * gist: https://gist.github.com/pdp7/6503aae568da2d0df85f56d2f1e47c5e
 * 
 * based on: "Capacitive sensors with the Teensy 3.0"
 * http://njhurst.com/blog/01356576041
 * 
 * SSD1306 display code based on example by Paul Stoffregen:
 * https://www.pjrc.com/teensy/td_libs_SSD1306.html
 */

/* 
 * Adafruit_SSD1306 library changes for upside down Adafruit i2c 128x64 OLED:
 * 
 * gist: https://gist.github.com/pdp7/687d0db32b30148779b3ff5346c3955e
 * 
 * path: hardware/teensy/avr/libraries/Adafruit_SSD1306/Adafruit_SSD1306.h
 *    #define SSD1306_128_64
 *    //   #define SSD1306_128_32
 *    //   #define SSD1306_96_16

 * forum post: "Re: SSD1306 flip lcd"
 *    https://forums.adafruit.com/viewtopic.php?f=47&t=25438&sid=c8bd3b6d598bd14259abb4e25cdd43a9
 * 
 * path: hardware/teensy/avr/libraries/Adafruit_SSD1306/Adafruit_SSD1306.cpp   
 *    //ssd1306_command(SSD1306_SEGREMAP | 0x1);
 *    ssd1306_command(SSD1306_SEGREMAP);
 *    //ssd1306_command(SSD1306_COMSCANDEC);
 *    ssd1306_command(SSD1306_COMSCANINC);
 *    
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

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);  // initialize with the I2C addr 0x3C (for the 128x32)
  display.clearDisplay();
  display.setCursor(0,0);
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
  int cap = 0;
  cap = touchRead(A1);
  Serial.print(  "[15/A1] ");
  Serial.print(cap);
  if(cap > 2000) {
    display.setCursor(0,0);
    display.println("CAP15 [A1]");
    display.println(cap);
    display.display();  
    delay(200);
  }
  
  cap = touchRead(A2);
  Serial.print("\t[16/A2] ");
  Serial.print(cap);
    if(cap > 2000) {
    display.setCursor(0,0);
    display.println("CAP16 [A2]");
    display.println(cap);
    display.display();  
    delay(200);
  }
  
  Serial.print("\t[17/A3] ");
  Serial.print(touchRead(A3));

  Serial.print("\t[18/A4] ");
  Serial.print(touchRead(A4));

  Serial.print("\t[19/A5] ");
  Serial.print(touchRead(A5));

  Serial.print("\t[22/A8] ");
  Serial.print(touchRead(A8));

  Serial.print("\t[23/A9] ");
  Serial.print(touchRead(A9));

  Serial.print("\t[0] ");
  Serial.print(touchRead(0));

  Serial.print("\t[1] ");
  Serial.print(touchRead(1));

  Serial.print("\t[3] ");
  Serial.print(touchRead(3));

  Serial.print("\t[4] ");
  Serial.print(touchRead(4));

  Serial.println();
  display.clearDisplay();
  display.display();
}