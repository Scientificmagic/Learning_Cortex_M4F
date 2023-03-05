# Preprocessor
The `volatile` keyword is used if a variable can change outside of the program's expected runtime (e.g. GPIO pins). This is required because the compiler can do some heavy optimization which could break your program. By telling the compiler a variable is `volatile`, it will not cut corners when handling the variable.


Some other thing is that this current headerfile is a bit newer and uses `uint32_t` instead of `unsigned long`. You'll need to include `<stdint.h>` to support that data type.