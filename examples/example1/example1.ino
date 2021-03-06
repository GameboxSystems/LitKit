/*H***************************************************************************
 * FILENAME :        example1.c
 *
 * DESCRIPTION :
 *       Shows a simple usecase for LitKit library
 *       Simple control loop for 1 WS2812B LED
 *
 * NOTES :
 *       Example for a LitKit board and Arduino IDE
 *
 * @author: Oleksandr Kiyenko
 * If you find this code useful you know what to do
 * bc1q8pflngx8qhaxtjvyhevdft4r6jvztrcm70fxz9
 *
 * @version: 1.0
 *
 * CHANGES :
 *
 * VERSION DATE        WHO     DETAIL
 * 1.0     2021.03.26  OK      Initial relase
 * 1.1     2021.04.02  OK      Updated with new functions
***************************************************************************H*/
#include "LitKit.h"

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
  	ws2812b_write(PB4, red, green, blue);
  	red += 10;
  	green += 30;
  	blue += 50;
  	delay(500);
  }
}
