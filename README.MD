# ft_printf

The versatility of the printf function in C represents a great exercise in programming for us. This project is of moderate difficulty. It will enable you to discover variadic functions in C.


The key to a successful ft_printf is a well-structured and good extensible code.

## Installing
1. Use git to clone this repository (the instructions will assume you've done this instead of clicked on "Download ZIP)
2. ```cd ft_printf```
3. ```make```

## Running
1. Compile libftprintf.a with any source files you'd like. And execute the resulting executable i.e:
```bash
gcc libftprintf.a your_source_file.c -o execute_me && execute_me
```

## Common Curiosities
The program handles the following flags, conversions and conversion specifiers:
- "cspdiuxX%" conversion specifiers
- "0-" flags
- Width and precision (including the '*' option)
