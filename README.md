# Monty Interpreter

Monty 0.98 is a scripting language that is first compiled into Monty byte code (just like in Python). It relies on a unique stack, with specific instructions to manipulate it. 

The goal of this project is to create an interpreter for Monty ByteCode files, utilizing Stacks (LIFO) and Queues (FIFO). Also included are [BrainFuck](https://en.wikipedia.org/wiki/Brainfuck) files.



## Quick Start

<u>Monty</u>:

Simply Compile: `$ gcc *.c -o monty`

Then Run: `$ ./monty filename.m`

A sample bytecode file is located at `/bytecodes/test.txt`.



<u>BrainFuck</u>:

Install the interpreter: `$ sudo apt-get install bf`

Then Run: `$ bf filename.bf`

Sample BrainFuck files are located at `/brainfuck`



## Commands Overview

The Monty Interpreter will tokenize command inputs, ignoring all whitespaces and comments which start with a `#` sign. When tokenizing, the interpreter only looks at the first 2 inputs per line.

Potential failures and their messages will be mentioned for each operation. Failures that can occur at this time include:

- USAGE: monty file      *# If given no file or too many arguments*
- Error: Can't open file <file name>      *# If given invalid file*
- Error: unknown instruction <opcode>      *# If unknown operation given*
- Error: malloc failed      *# if malloc fails*



There are 17 valid operation codes:

1. **push**

   Push only valid integers into the doubly linked list. Defaults to a Stack LIFO status. 

   Given:

   ```
   $ cat test.m
   push 1
   push 2
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   2
   1
   ```

   Failures:

   - Error: usage: push integer      *# if no argument given or invalid argument*

   ​


1. **pall**

   Print the values within the linked list.

   ​

2. **pint**

   Print only the value at the top of the linked list (head of linked list).

   Given:

   ```
   $ cat test.m
   push 1
   push 2
   pint
   ```

   Expected:

   ```
   $ ./monty test.m
   2
   ```

   Failures:

   - Error: can't pint, stack empty      *# If linked list is empty, can't print*

   ​

3. **pop**

   Remove the top element of the linked list.

   Given:

   ```
   $ cat test.m
   push 1
   push 2
   push 3
   pop
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   2
   1
   ```

   Failures:

   - Error: can't pop an empty stack      *# If linked list is empty*

   ​

4. **swap**

   Swap the top 2 elements of the linked list.

   Given:

   ```
   $ cat test.m
   push 1
   push 2
   swap
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   1
   2
   ```

   Failures:

   - Error: can't swap, stack too short      *# must have at least 2 elements*

   ​

5. **add**

   Add the top 2 elements of the linked list and store as the new head of the linked list.

   Given:

   ```
   $ cat test.m
   push 1
   push 2
   add
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   3
   ```

   Failures:

   - Error: can't add, stack too short      *# must have at least 2 elements*

   ​

6. **nop**

   This operation doesn't do anything.

   Given:

   ```
   $ cat test.m
   push 1
   nop
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   1
   ```

   ​

7. **sub**

   Subtract the top element of the linked list from the second top element of the linked list.

   Given:

   ```
   $ cat test.m
   push 1
   push 2
   sub
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   -1
   ```

   Failures:

   - Error: can't sub, stack too short      *# must have at least 2 elements*

   ​

8. **div**

   Divide the second top element of the stack by the top element of the stack.

   Given:

   ```
   $ cat test.m
   push 20
   push 10
   div
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   2
   ```

   Failures:

   - Error: can't div, stack too short      *# must have at least 2 elements*
   - Error: division by zero      *# cannot divide by 0*

   ​

9. **mul**

   Multiply the top 2 elements in the linked list and store as the new head of the linked list.

   Given:

   ```
   $ cat test.m
   push 2
   push 3
   mul
   pall
   ```

   Expected:

   ```
   $ ./monty test.m
   6
   ```

   Failures:

   - Error: can't mul, stack too short      *# must have at least 2 elements*

   ​

10. **mod**

    Uses the modulus of the second top element of the linked list by the top element of the linked list. The new value is stored as the new head.

    Given:

    ```
    $ cat test.m
    push 7
    push 3
    mod
    pall
    ```

    Expected:

    ```
    $ ./monty test.m
    1
    ```

    Failures:

    - Error: can't mod, stack too short      *# must have at least 2 elements*
    - Error: division by zero      *# cannot divide by 0*

    ​

11. **pchar**

    Convert the integer at the top of the linked list into a character using [ASCII](http://www.asciitable.com/).

    Given:

    ```
    $ cat test.m
    push 72
    pchar
    ```

    Expected:

    ```
    $ ./monty test.m
    H
    ```

    Failures:

    - Error: can't pchar, value out of range      *# if value is out of range of ASCII*
    - Error: can't pchar, stack empty      *# if linked list is empty*

    ​

12. **pstr**

    Print the string starting at the top of the linked list, using ASCII values. The string should stop printing if the stack is over, the value of the element is 0, or if the value is not an ASCII value.

    Given:

    ```
    $ cat test.m
    push 1
    push 110
    push 0
    push 110
    push 111
    push 116
    push 114
    push 101
    push 98
    push 108
    push 111
    push 72
    pstr
    ```

    Expected:

    ```
    $ ./monty test.m
    Holberton
    ```

    ​

13. **rotl**

    Rotates the first element of the linked list to the end of the list. The new head is the second top element of the linked list.

    Given:

    ```
    $ cat test.m
    push 1
    push 2
    push 3
    rotl
    pall
    ```

    Expected:

    ```
    $ ./monty test.m
    2
    1
    3
    ```

    ​

14. **rotr**

    Rotates the last element of the linked list to the head, so that it becomes the new head.

    Given:

    ```
    $ cat test.m
    push 1
    push 2
    push 3
    rotr
    pall
    ```

    Expected:

    ```
    $ ./monty test.m
    1
    3
    2
    ```

    ​

15. **stack**

    Mode Change: operations that add or remove from the linked list work using [LIFO](https://en.wikipedia.org/wiki/Stack_(abstract_data_type)). This is the default setting.

    ​

16. **queue**

    Mode Change: operations that add or remove from the linked list work using [FIFO](https://en.wikipedia.org/wiki/FIFO_(computing_and_electronics)). 

    Given:

    ```
    $ cat test.m
    queue
    push 1
    push 2
    push 3
    pall
    ```

    Expected:

    ```
    $ ./monty test.m
    1
    2
    3
    ```



## File Descriptions

- `monty.h` - Header file which contains library includes, structs created, and all function prototypes.
- `main.c`  - Main monty file handling the core operations, including reading user input arguments, opening bytecode file, parsing inputs, and calling correct operations.
- `get_opcode_func.c` - Returns the correct operation function.
- `string_helper.c` - Contains tokenizer, comment check, and helper functions.
- `helper.c` - Contains number argument conversion for the push operation, mode switch for queue vs stack, and helper functions for push, rotl, and rotr.
- `failures.c` - Fail checks and exits given certain conditions.
- `stack_funcs.c` - Core functions to manipulate and change the linked list. Other file(s): `stack_funcs2.c`
- `opcode_func.c` - Functions for each operation. Other file(s): `opcode_func2.c`, `opcode_func3.c`, `opcode_func4.c`
- `brainfuck` - Directory with brainfuck files.



## Team

Monicah Odipo - [Github](https://github.com/MonahDipsy) || [Twitter](https://twitter.com/odipo_monicah)

Omara Augustine - [Github](https://github.com/omara256) || [Twitter](https://twitter.com/ugaSwap)
