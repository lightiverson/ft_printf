# ft_printf
A personal rewrite of stdio.h's printf function. It was coded to be easily extendible.

The main purpose of this project was to study variadic arguments. Additionally, this code will prove usefull in future projects. Since stdio.h's printf is not allowed.

A more detailed explanation of this project can be found in in the [assignment sheet](en.subject.pdf).

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
