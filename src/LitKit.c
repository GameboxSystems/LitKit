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
 * @version: 1.0
 *
 * CHANGES :
 *
 * VERSION DATE        WHO     DETAIL
 * 1.0     2021.03.26  OK      Initial relase
 * 1.1     2021.03.27  OK      Multiple LEDs control
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
 * @param n   - LEDs in chain 0-255
 * @return none
 */
void ws2812b_write(uint8_t pin, uint8_t r, uint8_t g, uint8_t b, uint8_t n){
  uint8_t l, h, c;
  uint16_t j;

  l = PORTB;                  // Port B value for "Low"
  h = l | (1 << pin);         // Port B value for "High"
  c = n;                      // Initial counter value

  asm volatile(
    // Assembler instructions
    // 0 /400\850 /6\14
    // 1 /800\450 /13\7
    // 62.5ns/cycle
    "bst %[green],7\n"        // Load T-bit from G[7]
    "mov r16, %[cnt]\n"       // Load Counter
    "cli\n"                   // Disable interrupts
  "G7%=:\n"                   // Start of G[7]
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G7_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n"       // Wait
    "dec r16\n"               // Decrement counter (1 cycle)
    "bst %[green],6\n"        // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G6%=\n"             // Jump to next bit
  "G7_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n" // Wait
    "dec r16\n"               // Decrement counter (1 cycle)
    "bst %[green],6\n"        // Load T-bit from next bit

  "G6%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G6_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[green],5\n"        // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G5%=\n"             // Jump to next bit
  "G6_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[green],5\n"        // Load T-bit from next bit

  "G5%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G5_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[green],4\n"        // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G4%=\n"             // Jump to next bit
  "G5_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[green],4\n"        // Load T-bit from next bit

  "G4%=:\n"                   // Start of bit
  
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G4_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[green],3\n"        // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G3%=\n"             // Jump to next bit
  "G4_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[green],3\n"        // Load T-bit from next bit

  "G3%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G3_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[green],2\n"        // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G2%=\n"             // Jump to next bit
  "G3_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[green],2\n"        // Load T-bit from next bit

  "G2%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G2_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[green],1\n"        // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G1%=\n"             // Jump to next bit
  "G2_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[green],1\n"        // Load T-bit from next bit

  "G1%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G1_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[green],0\n"        // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G0%=\n"             // Jump to next bit
  "G1_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[green],0\n"        // Load T-bit from next bit

  "G0%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc G0_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],7\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R7%=\n"             // Jump to next bit
  "G0_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],7\n"          // Load T-bit from next bit

  "R7%=:\n"                   // Start of R[7]
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R7_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],6\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R6%=\n"             // Jump to next bit
  "R7_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],6\n"          // Load T-bit from next bit

  "R6%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R6_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],5\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R5%=\n"             // Jump to next bit
  "R6_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],5\n"          // Load T-bit from next bit

  "R5%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R5_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],4\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R4%=\n"             // Jump to next bit
  "R5_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],4\n"          // Load T-bit from next bit

  "R4%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R4_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],3\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R3%=\n"             // Jump to next bit
  "R4_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],3\n"          // Load T-bit from next bit

  "R3%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R3_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],2\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R2%=\n"             // Jump to next bit
  "R3_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],2\n"          // Load T-bit from next bit

  "R2%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R2_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],1\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R1%=\n"             // Jump to next bit
  "R2_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],1\n"          // Load T-bit from next bit

  "R1%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R1_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[red],0\n"          // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp R0%=\n"             // Jump to next bit
  "R1_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[red],0\n"          // Load T-bit from next bit

  "R0%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc R0_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],7\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B7%=\n"             // Jump to next bit
  "R0_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],7\n"         // Load T-bit from next bit

  "B7%=:\n"                   // Start of G[7]
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B7_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],6\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B6%=\n"             // Jump to next bit
  "B7_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],6\n"         // Load T-bit from next bit

  "B6%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B6_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],5\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B5%=\n"             // Jump to next bit
  "B6_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],5\n"         // Load T-bit from next bit

  "B5%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B5_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],4\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B4%=\n"             // Jump to next bit
  "B5_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],4\n"         // Load T-bit from next bit

  "B4%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B4_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],3\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B3%=\n"             // Jump to next bit
  "B4_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],3\n"         // Load T-bit from next bit

  "B3%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B3_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],2\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B2%=\n"             // Jump to next bit
  "B3_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],2\n"         // Load T-bit from next bit

  "B2%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B2_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],1\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B1%=\n"             // Jump to next bit
  "B2_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],1\n"         // Load T-bit from next bit

  "B1%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B1_0%=\n"           // Jump if T=0
    "nop\n nop\n nop\n nop\n" // Wait
    "bst %[blue],0\n"         // Load T-bit from next bit
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp B0%=\n"             // Jump to next bit
  "B1_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "nop\n nop\n nop\n nop\n nop\n"  // Wait
    "bst %[blue],0\n"         // Load T-bit from next bit

  "B0%=:\n"                   // Start of bit
    "out %[port], %[high]\n"  // Drive pin high
    "brtc B0_0%=\n"           // Jump if T=0
  "B0_1%=:\n"                 // T=1
    "bst %[green],7\n"        // Load T-bit from G[7] (1 cycle)
    "cpi r16,0\n"             // Last transfer ?
    "brne NotLast1%=\n"       // Jump to start (1/2 cycle)
    "nop\n"
    "nop\n"
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp END%=\n"            // Jump to next bit
  "NotLast1%=:\n"             // Not Last cycle
    "nop\n"
    "out %[port], %[low]\n"   // Drive pin low
    "rjmp G7%=\n"             // Jump to start
  "B0_0%=:\n"                 // T=0
    "out %[port], %[low]\n"   // Drive pin low
    "bst %[green],7\n"        // Load T-bit from G[7] (1 cycle)
    "cpi r16,0\n"             // Last transfer ?
    "brne NotLast0%=\n"       // Jump to start (1/2 cycle)
    "nop\n"
    "rjmp END%=\n"            // Jump to end
  "NotLast0%=:\n"             // Not Last cycle
    "rjmp G7%=\n"             // Jump to start
    "END%=:\n"
    "sei\n"                   // Enable interrupt
    :                         // Output operators
    :                         // Input operators
    [port]"I" (_SFR_IO_ADDR(PORTB)), 
    [red]"r" (r), 
    [green]"r" (g), 
    [blue]"r" (b), 
    [high]"r" (h), 
    [low]"r" (l), 
    [cnt]"r" (c) 
    :                         // Clobbed registers
	"r16" 					  // LEDs counter
  );
  for(j=0;j<400;j++){
    asm volatile("nop");
  }
}
