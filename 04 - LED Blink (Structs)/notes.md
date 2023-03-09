# LED Blink
Just a simple delay function that chews up clock cycles before toggling an LED.

# Header File Swap to Struct Members
In the new file `"tm4c-cmsis.h"`, scrolling all the way to the bottom shows the peripheral declarations. These are the big struct names we start with. To access elements in the struct, we get the names from the relevant sections above. For example:

```
SYSCTL->RCGC2
GPIOF_HS->DIR
GPIOF_HS->DATA_Bits
```

## Getting `tm4c-cmsis.h` to work
This header file has a `#include "core_cm4.h"` statement which won't naturally be in your project directory. Get the file to link by going to Project->Options->General Options and toggle "Use CMSIS".