int main() {
    // enable gate clocking control for Port F
    *((unsigned int *)0x400FE608U) = 0x20U;    
    // set direction of pins to output
    *((unsigned int *)0x40025400U) = 0x0EU;
    // enable pins as digital I/O
    *((unsigned int *)0x4002551CU) = 0x0EU;
    
    // finally set the LED bits
    *((unsigned int *)0x400253FCU) = 0x08U;
    return 0;
}
