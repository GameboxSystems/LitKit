/*H***************************************************************************
 * FILENAME :        example2.c
 *
 * DESCRIPTION :
 *       Shows a simple usecase for LitKit library
 *       Example of LEDs array function
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
 * 1.0     2021.04.02  OK      Initial relase
 *
***************************************************************************H*/
#include "LitKit.h"

void setup() {
  // put your setup code here, to run once:
  // Configure PB4 as output
  DDRB |= (1 << PB4);        //replaces pinMode(PB4, OUTPUT);
}

void loop() {
  // Array for 17 LEDs (GRB format)
  uint8_t grb[51] = {100,0,0, 
     0,0,0, 20,20,20, 0,0,0, 0,50,50, 
     0,0,0, 0,0,0, 0,0,0, 20,20,20,
     20,20,20, 0,0,0, 0,0,0, 0,0,0, 
     0,0,100, 0,0,0, 20,20,20, 0,0,0};

  	ws2812b_stream(PB4, grb, 51);
  	delay(500);
}
