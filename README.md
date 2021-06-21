# Simple compiler

## Requirements

- Bison version 3.7.6
- Flex version 2.6.4

## build

Run `make` command.

## Usage

Run `./compiler [Filename]`.
The output will be stored in `[filename].out`.

## Inside the compiler

### Register usage

- Calculation experation are stored in `$v0`.
- Mutable address are stored in `$v2`.
- Every experation only use `$v0` and `$v1` for calculation and `$v2` to store mutable addresses.

### Stack

- Global variables are stored at the base of the stack.
- Every local variable is stored with an offset from the `$sp`.
- When calling a function first we reserve two words for it's return value and return address. Then it's input arguments are stored on top of the stack.

### function calls

First the caller put the input arguments on top of stack. and then calls the callee.
The callee then stores the return address. then makes room for it's variables and initialize them.
Before returning, the callee brings the stack pointer on return value.
