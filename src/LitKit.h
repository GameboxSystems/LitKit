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

/**
 * @author: Oleksandr Kiyenko
 * @version: 1.0
 * Write data to a single WS2812B 
 * 
 * @param pin - Pin number from PORTB 
 * @param r   - Red intensity 0-255
 * @param g   - Green intensity 0-255
 * @param b   - Blue intensity 0-255
 * @return none
 */
void ws2812b_write(uint8_t pin, uint8_t r, uint8_t g, uint8_t b);

/**
 * @author: Oleksandr Kiyenko
 * @version: 1.0
 * Write stream to a WS2812B 
 * 
 * @param pin - Pin number from PORTB 
 * @param grb - Array of colors in GRB format
 * @param b   - Bytes to send 0-255
 * @return none
 */
void ws2812b_stream(uint8_t pin, uint8_t* grb, uint8_t n);

/**
 * @author: Oleksandr Kiyenko
 * @version: 1.0
 * Write data to a single SK6812
 * 
 * @param pin - Pin number from PORTB 
 * @param r   - Red intensity 0-255
 * @param g   - Green intensity 0-255
 * @param b   - Blue intensity 0-255
 * @return none
 */
void sk6812_write(uint8_t pin, uint8_t r, uint8_t g, uint8_t b);

/**
 * @author: Oleksandr Kiyenko
 * @version: 1.0
 * Write stream to a SK6812
 * 
 * @param pin - Pin number from PORTB 
 * @param grb - Array of colors in GRB format
 * @param b   - Bytes to send 0-255
 * @return none
 */
void sk6812_stream(uint8_t pin, uint8_t* grb, uint8_t n);


#endif  // LITKIT_H_
