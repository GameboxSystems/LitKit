/*H***************************************************************************
 * FILENAME :        example1.c
 *
 * DESCRIPTION :
 *       Shows a simple usecase for LitKit library
 *
 * NOTES :
 *       Example for a LitKit board and Arduino IDE
 *
 * @author: Oleksandr Kiyenko
 * @version: 1.0
 *
 * CHANGES :
 *
 * VERSION DATE        WHO     DETAIL
 * 1.0     2021.03.26  OK      Initial relase
 *
***************************************************************************H*/
#include "LitKit.h"

#define NUM_LEDS    4

void setup() {
  // put your setup code here, to run once:
  // Configure PB4 as output
  DDRB |= (1 << PB4);        //replaces pinMode(PB4, OUTPUT);
}

void loop() {
  uint8_t red = 0;
  uint8_t green = 0;
  uint8_t blue = 0;
  while(1){
  	ws2812b_write(PB4, red, green, blue, NUM_LEDS);
  	red += 10;
  	green += 30;
  	blue += 50;
  	delay(500);
  }
}
