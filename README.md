# Abstract VM

_A C++ 42 project._

## About

The purpose of the project is to create a simple virtual machine that can interpret programs written in a basic assembly language.

More information in the [subject](subject/abstract-vm.en.pdf).

## Installation

Clone the project.

```bash
$> git clone https://github.com/ebaudet/abstract-vm.git
$> cd abstract-vm
$> make
$> ./avm [-civh] [FILE]
```

## Usage :

```bash
$> ./avm --usage
Usage: ./avm [-civh] [FILE]

Abstract VM : Virtual Machine that can interpret programs written in basic assembly language.

optional arguments:
  -c, --continue	Continue after first error
  -i, --interactive	Interactive mode for entry. Directly execute the command without expecting
  -v, --verbose		Verbose mode
  -h, --help, --usage	Show this help message
```

## Exemple :

```bash
$> ./avm
push int32(2)
push int32(3)
add
assert int32(5)
dump
exit
;;
5
```

```bash
$> cat test/sample.avm
; -------------
; sample.avm -
; -------------

push int32(42)
push int32(33)
add
push float(44.55)
mul
push double(42.42)
push int32(42)
dump
pop
assert double(42.42)
push int8(42)
print
exit
$> ./avm test/sample.avm
42
42.42
3341.25
*
```

```bash
$> ./avm
pop
;;
Exception on line 1: pop
pop: Stack is empty.
```

```bash
$> ./avm --interactive
> push int32(42)
> push int32(33)
> add
> push float(44.55)
> mul
> push double(42.42)
> push int32(42)
> dump
42
42.42
3341.25
> pop
> assert double(42.42)
> exit
```

Errors example :
```bash
$> ./avm --interactive --continue
> unknown instruction
LexerError:1:0: error: unkown expression "unknown instruction"
unknown instruction
^
> push int8(128)
Exception on line 2: push int8(128)
Overflow on a value
> push int8(-129)
Exception on line 3: push int8(-129)
Underflow on a value
> pop
Exception on line 4: pop
pop: Stack is empty.
> push int8(0)
> push int8(1)
> div
Exception on line 7: div
Divide by zero exception.
> push int8(5)
> dump
5
> assert int16(6)
Exception on line 10: assert int16(6)
Assert exception
> dump
5
> add
Exception on line 12: add
add: Stack is lower 2.
> ;;
Exit instruction is missing.
______________________
8 errors generated.
```

Lexing errors :
```bash
$ cat -n test/sampleWithLexerError.avm
     1	push int32(42); comment
     2	push int32(33) 	; comment
     3	add
     4	push float(44.55)
     5	mul
     6	push double(42.42)
     7		 push 	int32(42)
     8	dump
     9	pop
    10	assert double(42.42)
    11	exit
    12
    13	; test Pas ok :
    14	push int128(42)
    15	ad d
    16	popp
    17	push int(33)
$> ./avm -c test/sampleWithLexerError.avm
LexerError:14:5: error: unkown expression "int128(42)"
push int128(42)
     ^
LexerError:15:0: error: unkown expression "ad d"
ad d
^
LexerError:16:3: error: unkown expression "p"
popp
   ^
LexerError:17:5: error: unkown expression "int(33)"
push int(33)
     ^
______________________
4 errors generated.
```

Parsing errors :
```bash
$> cat -n test/sampleWithParserError.avm
     1	push ; push without param
     2	push
     3	push 55 ; push with bad value
     4	push int32() ; without value
     5	push int32(25.5) ; int with zvalue
     6	push float(55) ; float with nvalue
     7	push float(55.5)
     8	push int32(42)
     9	push int32(2)
    10	sub int32(12) ; push with extra param
    11	dump
    12	exit
$> ./avm -c test/sampleWithParserError.avm
ParserError:1:5: Argument expected.
push ; push without param
     ^
ParserError:2:4: Argument expected.
push
    ^
ParserError:3:5: Type expected.
push 55 ; push with bad value
     ^
ParserError:4:11: Type NVal expected.
push int32() ; without value
           ^
ParserError:5:11: Type NVal expected.
push int32(25.5) ; int with zvalue
           ^
ParserError:6:11: Type ZVal expected.
push float(55) ; float with nvalue
           ^
ParserError:10:4: No argument expected.
sub int32(12) ; push with extra param
    ^
______________________
7 errors generated.
```

### Grammar

The assembly language of __AbstractVM__ is generated from the following grammar (`#` corresponds to the end of the input, not to the character ’#’):

```
S := INSTR [SEP INSTR]* #

INSTR :=
      push VALUE
    | pop
    | dump
    | assert VALUE
    | add
    | sub
    | mul
    | div
    | mod
    | print
    | exit
< bonus instructions >
    | ls
    | abs
    | min
    | max
    | pow
    | debug
    | clear
    | sep
    | help

VALUE :=
      int8(N)
    | int16(N)
    | int32(N)
    | float(Z)
    | double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'+
```

### Project files :
```
.
├── Makefile
├── README.md
├── auteur
├── includes
│   ├── Color.hpp
│   ├── Exception.hpp
│   ├── Factory.hpp
│   ├── IOperand.hpp
│   ├── Instruction.hpp
│   ├── Lexer.hpp
│   ├── Operand.hpp
│   ├── Parser.hpp
│   ├── Token.hpp
│   ├── argparse.hpp
│   └── main.hpp
├── srcs
│   ├── Exception.cpp
│   ├── Factory.cpp
│   ├── Instruction.cpp
│   ├── Lexer.cpp
│   ├── Parser.cpp
│   ├── Token.cpp
│   ├── argparse.cpp
│   └── main.cpp
├── subject
│   └── abstract-vm.en.pdf
└── test
    ├── sample.avm
    ├── sampleBonus1.avm
    ├── sampleOverflow.avm
    ├── sampleWithLexerError.avm
    ├── sampleWithParserError.avm
    ├── sampleWithoutExit.avm
    ├── test-abs.avm
    ├── test-min-max.avm
    ├── test-pow.avm
    ├── test.avm
    └── test.vm
```
