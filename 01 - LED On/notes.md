# Turning On LEDs

## Quick terminology
- GPIO - General-purpose input/output
    - These are the signal pins on the board

## Where to start?
According to the evaluation board user's guide:
- Page 7, Figure 2-1
    - LEDs are connected to GPIO.
- Page 9, Table 2-2
    - LEDs are mapped to GPIO PF1, PF2, and PF3.
    - It's read as: "GPIO pin F1, F2, and F3"

*GPIO F pins need to be turned on somehow.*
    
## Consult the datasheet
Searching for "memory map" in the table of contents leads to Table 2-4 on Page 92.
If you look for peripherals, you will find "GPIO Port F" listed and its associated memory address.
`0x4002.5000`
(All memory addresses have a decimal in there for readability. Remove before use)

## Inaccessible memory?
If you try to go to the address `0x4002.5000` in the memory debugger, it will appear to be empty.
The hardware block is switched off by default to save power and needs to be manually turned on.
This process of blocking the clock signal is called "clock-gating"

## Enable clock gating control
Searching for "clock gating" in the datasheet, you will go to Page 340, Title "General-Purpose Input/Output Run Mode Clock Gating Control (`RCGCGPIO`)".
If we focus on the description for bit 5, we will discover that setting its value to 1 will enable GPIO Port F.

- We will need the base address `0x400F.E000` and the offset `0x608` to get the complete register address.

Go to the symbolic memory panel in the debugger and use the base address then add the offset. The resulting address is `0x400F.E608`.

Set the data value for bit 5 to be 1 (`0x00000020`).
In the memory debugger, you'll notice that the memory block at `0x4002.5000` is now accessible.

## Finding GPIO F registers
In the table of contents, you'll see a section dedicated to GPIO. In the subsection "Initialization and Configuration", you'll head to Page 656. There's a lot to read and decipher.

### Initialization and Configuration
Every step involves some register manipulation, scrolling past the checklist will reveal the register map in Table 10-6, Page 660. **This will be frequently refered to during the process**.


#### Step 1 - Enable the clock to the port.
We've already done that in the previous step.

#### Step 2 - Set direction of GPIO pins with the `GPIODIR` register.
Referring to Table 10-6, head to Page 663.

We already know Port F's base address in the previous steps, but we learn about the appropriate offset (`0x400`). We're trying to target pins 1, 2, and 3 and set their values to 1 which makes them function as outputs for our LEDs.

Applying the offset to our base address, we get `0x4002.5400`. Set the value to `0x0000.000e` to hit those 3 bits.

#### Step 6 - To enable GPIO pins as digital I/Os, set the appropriate `DEN` bit in the `GPIODEN` register.
With a bit of reading and foresight, we can skip steps 3, 4, and 5 as they are not relevant to our needs.
Referring to Table 10-6, head to Page 682.

Scroll down to the next page and obtain the offset value `0x51C`. Similar to step 2, we want to enable our 3 pins, so set address `0x4002.551C` to value `0x0000.000e` to target our bits.


## Finally controlling the LED
In memory address `0x4002.53FC`, you can set the first 3 bits to 1.
*As of now, I have no idea how to derive this memory address*

Remember, toggling the 1st bit to 1 requires you to write hex `0x0000.0002`. Subsequently, toggling the 2nd or 3rd bit to 1 requires you to write hex `0x0000.0004` or `0x0000.0008`, respectively.



## Converting to code
As for coding all this up, it's actually painless compared to all the other steps.
*ARM registers uses unsigned int for its memory address.*

We can create a pointer to a memory address by typecasting the address. Notice the 'U' suffix at the end of the address. Dereference the variable like normal to set a value.
```
unsigned int *p_address = (unsigned int *)0x00000000U;
*p_address = 0x05U;
```
If you don't need the variable for anything, you can condense it into 1 line by directly dereferencing the typecast.
```
*((unsigned int *)0x00000000U) = 0x05U;
```



