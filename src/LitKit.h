#ifndef LITKIT_H_
#define LITKIT_H_
/*H***************************************************************************
 * FILENAME :        LitKit.h
 *
 * DESCRIPTION :
 *       Basic ATtiny functions to work WS2812B LED
 *
 * PUBLIC FUNCTIONS :
 *       void ws2812b_write(uint8_t pin, uint8_t r, uint8_t g, uint8_t b)
 *
 * NOTES :
 *       Functions assume that you work with PORTB (The only possible 
 *       for ATtiny85)
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
#include "avr/io.h"

void ws2812b_write(uint8_t pin, uint8_t r, uint8_t g, uint8_t b, uint8_t n);

#endif  // LITKIT_H_
