#include <stdint.h>
#include "tm4c-cmsis.h"

#define LED_RED         (1U << 1)
#define LED_BLUE        (1U << 2)
#define LED_GREEN       (1U << 3)

void delay(void);

void delay(void) {
    int volatile counter = 0;
    while (counter < 1000000) {
      counter++;
    }
}

int main() {
    // enable gate clocking control for Port F
    SYSCTL->RCGC2 = (1U << 5);
    // enable high-performance bus for Port F
    SYSCTL->GPIOHSCTL = (1U << 5);
    // set direction of pins to output
    GPIOF_HS->DIR = 0x0EU;
    // enable pins as digital I/O
    GPIOF_HS->DEN = 0x0EU;
    

    // finally set the LED bits
    GPIOF_HS->DATA_Bits[LED_RED] = LED_RED;
    while(1) {
        delay();
        GPIOF_HS->DATA_Bits[LED_BLUE] = LED_BLUE;
        delay();
        GPIOF_HS->DATA_Bits[LED_BLUE] = ~LED_BLUE;
    }
  
    return 0;
}
