#include <stdint.h>
#include "tm4c123gh6pm.h"

#define LED_RED         (1U << 1)
#define LED_BLUE        (1U << 2)
#define LED_GREEN       (1U << 3)

int main() {
    // enable gate clocking control for Port F
    SYSCTL_RCGCGPIO_R = (1U << 5);
    // enable high-performance bus for Port F
    SYSCTL_GPIOHBCTL_R = (1U << 5);
    // set direction of pins to output
    GPIO_PORTF_AHB_DIR_R = 0x0EU;
    // enable pins as digital I/O
    GPIO_PORTF_AHB_DEN_R = 0x0EU;
    
    // finally set the LED bits
    GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
    GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
    return 0;
}
