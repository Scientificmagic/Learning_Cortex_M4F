#include <stdint.h>
#include "tm4c123gh6pm.h"

int main() {
    // enable gate clocking control for Port F
    SYSCTL_RCGCGPIO_R = 0x20U;    
    // set direction of pins to output
    GPIO_PORTF_DIR_R = 0x0EU;
    // enable pins as digital I/O
    GPIO_PORTF_DEN_R = 0x0EU;
    
    // finally set the LED bits
    GPIO_PORTF_DATA_R = 0x08U;
    return 0;
}
