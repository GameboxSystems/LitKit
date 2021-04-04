/*H***************************************************************************
 * FILENAME :        LitKit.c
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
 * If you find this code useful you know what to do
 * bc1q8pflngx8qhaxtjvyhevdft4r6jvztrcm70fxz9
 *
 * @version: 1.2
 *
 * CHANGES :
 *
 * VERSION DATE        WHO     DETAIL
 * 1.0     2021.03.26  OK      Initial relase
 * 1.1     2021.03.27  OK      Multiple LEDs control
 * 1.2     2021.04.04  OK      SK6812 support
***************************************************************************H*/
#include "LitKit.h"

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
void ws2812b_write(uint8_t pin, uint8_t r, uint8_t g, uint8_t b){
	uint8_t grb[3];
	grb[0] = g;
	grb[1] = r;
	grb[2] = b;
	ws2812b_stream(pin, grb, 3);
}

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
void ws2812b_stream(uint8_t pin, uint8_t* grb, uint8_t n){
  uint8_t l, h;
  uint16_t j;

  l = PORTB;                  // Port B value for "Low"
  h = l | (1 << pin);         // Port B value for "High"

  asm volatile(
    // Assembler instructions
    // 0 /400ns\850ns /6 \14
    // 1 /800ns\450ns /13\7
    // 62.5ns/cycle
	"ld r16,X+\n"			  // Load byte & inc pointer (2 ?)
    "bst r16,7\n"        	  // Load T-bit from B[7]
    "cli\n"                   // Disable interrupts
  "B7%=:\n"                   // Start of B[7]
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B7_0%=\n"           // Jump if T=0
	"ld r17,X+\n"			  // Load next byte & inc pointer (2 ?)
    "dec %[cnt]\n"            // Decrement counter (1 cycle)
	"nop\n"       			  // Wait
    "bst r16,6\n"             // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B6%=\n"             // Jump to next bit
  "B7_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
	"ld r17,X+\n"			  // Load next byte & inc pointer (2 ?)
    "dec %[cnt]\n"            // Decrement counter (1 cycle)
	"nop\n nop\n"             // Wait
    "bst r16,6\n"             // Load T-bit from next bit
  "B6%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B6_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst r16,5\n"             // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B5%=\n"             // Jump to next bit
  "B6_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst r16,5\n"             // Load T-bit from next bit
  "B5%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B5_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst r16,4\n"             // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B4%=\n"             // Jump to next bit
  "B5_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst r16,4\n"             // Load T-bit from next bit
  "B4%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B4_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst r16,3\n"             // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B3%=\n"             // Jump to next bit
  "B4_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst r16,3\n"             // Load T-bit from next bit
  "B3%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B3_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst r16,2\n"             // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B2%=\n"             // Jump to next bit
  "B3_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst r16,2\n"             // Load T-bit from next bit
  "B2%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B2_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst r16,1\n"             // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B1%=\n"             // Jump to next bit
  "B2_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst r16,1\n"             // Load T-bit from next bit
  "B1%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B1_0%=\n"           // Jump if T=0
	"nop\n nop\n nop\n"       // Wait
    "bst r16,0\n"             // Load T-bit from next bit
	"mov r16,r17\n"           // Reload data for next cycle
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B0%=\n"             // Jump to next bit
  "B1_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
	"nop\n nop\n nop\n nop\n" // Wait
    "bst r16,0\n"             // Load T-bit from next bit
	"mov r16,r17\n"           // Reload data for next cycle
  "B0%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B0_0%=\n"           // Jump if T=0
  "B0_1%=:\n"                 // T=1
    "bst r17,7\n"             // Load T-bit fot next cycle (1 cycle)
    "cpi %[cnt],0\n"          // Last transfer ?
    "brne NotLast1%=\n"       // Jump to start (1/2 cycle)
    "nop\n nop\n"             // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp END%=\n"            // Jump to next bit
  "NotLast1%=:\n"             // Not Last cycle
    "nop\n"                   // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B7%=\n"             // Jump to start
  "B0_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "bst r17,7\n"             // Load T-bit fot next cycle (1 cycle)
    "cpi %[cnt],0\n"          // Last transfer ?
    "brne NotLast0%=\n"       // Jump to start (1/2 cycle)
    "nop\n"                   // Wait
    "rjmp END%=\n"            // Jump to end
  "NotLast0%=:\n"             // Not Last cycle
    "rjmp B7%=\n"             // Jump to start
  "END%=:\n"
    "sei\n"                   // Enable interrupt
    :                         // Output operators
    :                         // Input operators
    [cnt]"a" (n),             // Butes to send
	[arr]"x" (grb),           // Colors array GRB format
    [port]"I" (_SFR_IO_ADDR(PORTB)), // Port
    [high]"r" (h),            // High value
    [low]"r" (l)              // Low value
    :                         // Clobbed registers
	"r16",                    // Current data
	"r17"		              // Next data
  );
  for(j=0;j<400;j++){
    asm volatile("nop");
  }
}

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
void sk6812_write(uint8_t pin, uint8_t r, uint8_t g, uint8_t b){
	uint8_t grb[3];
	grb[0] = g;
	grb[1] = r;
	grb[2] = b;
	sk6812_stream(pin, grb, 3);
}

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
void sk6812_stream(uint8_t pin, uint8_t* grb, uint8_t n){
  uint8_t l, h;
  uint16_t j;

  l = PORTB;                  // Port B value for "Low"
  h = l | (1 << pin);         // Port B value for "High"

  asm volatile(
    // Assembler instructions
    // 0 /300ns\900ns /4.8 \14.4
    // 1 /600ns\600ns /9.6 \ 9.6
    // 62.5ns/cycle
	"ld r16,X+\n"			  // Load byte & inc pointer (2 ?)
    "bst r16,7\n"        	  // Load T-bit from B[7]
    "cli\n"                   // Disable interrupts
  "B7%=:\n"                   // Start of B[7]
    "out %[port], %[high]\n"  // Drive pin high
    "brts B7_1%=\n"           // Jump if T=1
	"out %[port], %[low]\n"   // Drive pin low
	"ld r17,X+\n"			  // Load next byte & inc pointer
    "dec %[cnt]\n"            // Decrement counter (1 cycle)
    "bst r16,6\n"             // Load T-bit from next bit
    "rjmp B6%=\n"             // Jump to next bit
  "B7_1%=:\n"                 // T=1
    "nop\n nop\n"		      // Wait
    "out %[port], %[low]\n"   // Drive pin low
	"ld r17,X+\n"			  // Load next byte & inc pointer (2 ?)
    "dec %[cnt]\n"            // Decrement counter (1 cycle)
    "bst r16,6\n"             // Load T-bit from next bit
	
  "B6%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brts B6_1%=\n"           // Jump if T=1
	"out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,5\n"             // Load T-bit from next bit
    "rjmp B5%=\n"             // Jump to next bit
  "B6_1%=:\n"                 // T=1
    "nop\n nop\n"		      // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,5\n"             // Load T-bit from next bit
	
  "B5%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brts B5_1%=\n"           // Jump if T=0
	"out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"      // Wait
    "bst r16,4\n"             // Load T-bit from next bit
    "rjmp B4%=\n"             // Jump to next bit
  "B5_1%=:\n"                 // T=0
    "nop\n nop\n"		      // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,4\n"             // Load T-bit from next bit
	
  "B4%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brts B4_1%=\n"           // Jump if T=0
	"out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,3\n"             // Load T-bit from next bit
    "rjmp B3%=\n"             // Jump to next bit
  "B4_1%=:\n"                 // T=0
    "nop\n nop\n"		      // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,3\n"             // Load T-bit from next bit
	
  "B3%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brts B3_1%=\n"           // Jump if T=0
	"out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,2\n"             // Load T-bit from next bit
    "rjmp B2%=\n"             // Jump to next bit
  "B3_1%=:\n"                 // T=0
    "nop\n nop\n"		      // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,2\n"             // Load T-bit from next bit
	
  "B2%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brts B2_1%=\n"           // Jump if T=0
	"out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,1\n"             // Load T-bit from next bit
    "rjmp B1%=\n"             // Jump to next bit
  "B2_1%=:\n"                 // T=0
    "nop\n nop\n"		      // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n"       // Wait
    "bst r16,1\n"             // Load T-bit from next bit
	
  "B1%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brts B1_1%=\n"           // Jump if T=0
	"out %[port], %[low]\n"   // Drive pin low
	"nop\n nop\n"             // Wait
    "bst r16,0\n"             // Load T-bit from next bit
	"mov r16,r17\n"           // Reload data for next cycle
    "rjmp B0%=\n"             // Jump to next bit
  "B1_1%=:\n"                 // T=0
    "nop\n nop\n"		      // Wait
    "out %[port], %[low]\n"   // Drive pin low
	"nop\n nop\n"             // Wait
    "bst r16,0\n"             // Load T-bit from next bit
	"mov r16,r17\n"           // Reload data for next cycle

  "B0%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brts B0_1%=\n"           // Jump if T=0
	"out %[port], %[low]\n"   // Drive pin low
  "B0_0%=:\n"                 // T=1
    "bst r17,7\n"             // Load T-bit fot next cycle (1 cycle)
    "cpi %[cnt],0\n"          // Last transfer ?
    "brne NotLast1%=\n"       // Jump to start (1/2 cycle)
    "nop\n nop\n"             // Wait
    "rjmp END%=\n"            // Jump to next bit
  "NotLast1%=:\n"             // Not Last cycle
    "nop\n"                   // Wait
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B7%=\n"             // Jump to start
  "B0_1%=:\n"                 // T=0
    "bst r17,7\n"             // Load T-bit fot next cycle (1 cycle)
    "cpi %[cnt],0\n"          // Last transfer ?
    "out %[port], %[low]\n"   // Drive pin low
    "brne NotLast0%=\n"       // Jump to start (1/2 cycle)
    "rjmp END%=\n"            // Jump to end
  "NotLast0%=:\n"             // Not Last cycle
    "rjmp B7%=\n"             // Jump to start
  "END%=:\n"
    "sei\n"                   // Enable interrupt
    :                         // Output operators
    :                         // Input operators
    [cnt]"a" (n),             // Butes to send
	[arr]"x" (grb),           // Colors array GRB format
    [port]"I" (_SFR_IO_ADDR(PORTB)), // Port
    [high]"r" (h),            // High value
    [low]"r" (l)              // Low value
    :                         // Clobbed registers
	"r16",                    // Current data
	"r17"		              // Next data
  );
  for(j=0;j<400;j++){
    asm volatile("nop");
  }
}
