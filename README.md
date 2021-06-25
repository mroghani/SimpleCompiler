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
<!-- f(f(x))
[ r] [ r] 
r ==> v
ret -->

- We use `$s1` as the base refrence of our local variables.
- We use `$s0` as the base refrence of our global variables.
- S registers are callee preserved.
<!-- - We use `$v0` for the return value of a funciton call. -->
- We use `JALR` for function calls. Return address is stored in `$ra`.
- We use `$t` registers for computation purposes. These registers are caller preserved.


<!-- - Calculation experation are stored in `$t0`.
- Mutable address is stored in `$t2`.
- Every experation only use `$t0` and `$t1` for calculation and `$t2` and `$t3` to store mutable addresses. -->

### Stack

- We use stack for the calculations and storing variables.

#### Function structure in stack

1. return value
2. return address (go to caller)
3. preserved registers value (`$s[0-1]`)
4. local variables (including args)
    
<!-- - Global variables are stored at the base of the stack.
- Every local variable is stored with an offset from the `$sp`.
- When calling a function first we reserve two words for it's return value and return address. Then it's input arguments are stored on top of the stack. -->

### function calls

First the caller put the input arguments on top of stack. and then calls the callee.
The callee then stores the return address.
Before returning, the callee brings the stack pointer on return value.
