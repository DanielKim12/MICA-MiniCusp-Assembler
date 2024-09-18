# MICA: A MiniCUSP Assembler

This project is an implementation of an assembler called MICA (MiniCUSP Assembler) that translates MiniCUSP assembly code into machine code. The implementation was done in `assembly.cpp`, adhering to the MiniCUSP ISA as described in the ECS 50 programming assignment.

## MiniCUSP ISA Overview

MiniCUSP is a simplified instruction set architecture (ISA) that includes:
- A CPU with registers like ACC, XR, SP, and FP.
- A memory system consisting of 4096 (1000h) 24-bit words.
- A set of instructions for data movement, arithmetic operations, stack manipulation, and control flow.

## Features of MICA Assembler

- **Instruction Set Support**: The assembler supports all instructions in the MiniCUSP ISA, converting them to their corresponding machine code.
- **Addressing Modes**: The assembler handles various addressing modes including immediate, direct, indexed, indirect, and frame-related modes.
- **Symbol Table Management**: It uses a symbol table to manage labels, allowing forward references and ensuring that labels are replaced with their correct addresses in the generated machine code.
- **Error Handling**: MICA checks for errors such as multiple label definitions, undefined labels, and unsupported addressing modes.
- **Directives**: Supports the `.word` directive for creating and initializing variables in memory.

## How to Run the Assembler

To assemble a MiniCUSP assembly file into machine code:

1. **Compile the Assembler**:
   ```bash
     g++ -Wall -Werror -std=c++14 -g assembly.cpp -o assembler
    ```
   
2. **Run the Assembler**:
   ```bash
     ./assembler input.csp output.txt
    ```

## Example Usage 
  ```bash
    label1:
    POPA
    label2:
    label3:
    LDA # label4
    LDA label4
    JLT label1
    HLT
    label4:
    .word 53
    .word 9
```
## Output
```bash
  FFF013
  000005
  002005
  4A2000
  FFFFFF
  000053
  000009
```
## Error Handling
MICA will report assembler errors in the following scenarios:
- Label Defined Multiple Times: If a label is defined more than once.
- Label Undefined: If a label is used but never defined.
- Unsupported Addressing Mode: If an instruction is used with an unsupported addressing mode.

## Acknowledgments
This assembler was implemented as part of the ECS 50 Programming Assignment #6. The assignment was designed to provide hands-on experience with assembly language and assembler implementation, following the specifications provided by the course instructor.

## Copyright 
All rights given to GUK IL KIM 
