# Direct Address Access
Previously, we used `GPIO_PORTF_DATA_R` to write to the register and target our LED. The offset for that was `0x3FC`. If we convert that hex to binary, we get `11.1111.1100`. In the physical hardware, left to right, that translates to Pin 7 to Pin 0. The extra two zeros at the end are to ensure the address is divisible by 4.


These 8 bits are the address bits associated with each pin. The hardware is set up such that the data bit cannot be changed unless the address bit is on. That means, with the offset `0x3FC`, all address bits are on and all data bits are able to be changed in a single statement.


If we want to target a specific bit, we can use the base address `GPIO_PORTF_DATA_BITS_R` and individually select our bits with an array indexing. For example, the red LED is on Pin 1. If we want to change that data bit, without overwriting other data bits, we can target the address with `GPIO_PORTF_DATA_BITS_R[LED_RED]`, where `LED_RED = (1U << 1)`. Then we set our target address with `GPIO_PORTF_DATA_BITS_R[LED_RED] = LED_RED`. This expression is like turning on the address bit, but it's more like writing to the specific combo of connected address lines.


With that thought process, if we want full access to the LED pins without worrying about other turning on/off other data bits in the register, we could write to the address `GPIO_PORTF_DATA_BITS_R[0xE]` our LED values. Remember `0xE = 1110` in binary.


# GPIO High-Performance Bus Control `GPIOHBCTL`
Search the datasheet's table of contents for "high-performance" leads to Page 258.
We discover the base address `0x400F.E000` and the offset `0x06C`. We need to set bit 5 for Port F to the value 1.

Set `SYSCTL_GPIOHBCTL_R` bit 5 with and swap all Port F registers with the `AHB` variant
```
SYSCTL_GPIOHBCTL_R = (1U << 5);

GPIO_PORTF_DIR_R        -> GPIO_PORTF_AHB_DIR_R
GPIO_PORTF_DEN_R        -> GPIO_PORTF_AHB_DEN_R
GPIO_PORTF_DATA_BITS_R  -> GPIO_PORTF_AHB_DATA_BITS_R
```

# Testing Behaviors
To test the behavior of the individual addresses working and our new AHB, we can simply toggle two LEDs individually.
```
GPIO_PORTF_AHB_DATA_BITS_R[LED_RED] = LED_RED;
GPIO_PORTF_AHB_DATA_BITS_R[LED_BLUE] = LED_BLUE;
```
Observe the old behavior. If we wrote to `GPIO_PORTF_AHB_DATA_R` and turned on the red LED, the LED would of course be red. Then, if we only turn on the blue LED, the red LED would turn off, leaving us with blue.

Now, with the new `GPIO_PORTF_AHB_DATA_BITS_R` addressing, turning on red, then blue, results in both being on. You don't need to worry about the side effects of accidently turning off other LEDs.