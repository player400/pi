## Primitive Iterator (PI)

Primitive Iterator (or PI) is a RISC, Von Neumann computer architecture I designed.

It features an incredibly simple assembly - everything can be achieved with just two diferent instructions: MOV and FLAG.
Memory mapping of registers allowed to significantly simplify the architecture.

The core principle behind PI, is that complexity should always be on the programmer's side. Therefore there is no complex, multi-step instructions (like LOOP, that we know from x86 processors).
Both instructions are designed to be executed in just one clock cycle and do only one, simple thing.

With PI assembly, you are essentially programming in micro-code.

It's also possible to implement it using a pipeline, which would make for a whooping 2 instructions per clock cycle. 
Simplicity allows for very few layers of logic gates, which (in theory) should make for low latency and thus a fast clock.

More information is availible in the ISA document. Availible in the [4-bit version](PI_4bit/ISA.pdf) and the [8-bit version](PI_8bit/ISA.pdf)


## Progress

Documentation
_______________________________________________________________________
ISA (Instruction Set Architecture) document.\
Availible for:\
    -4bit version\
    -8bit version\
<br/>
<br/>


RTL Digital Design
_______________________________________________________________________
VHDL design of a PI microcontroller for the Digilent Atlys board with Spartan 6.\
Supporting:\
    -8 bit version\
<br/>
<br/>
    

DTL Schematics
_______________________________________________________________________
Logical design/simulation (on the logic gate level) of a PI computer made with the Circuit Verse software.\ 
Availible for:\
    -4bit version\
<br/>
<br/>



Emulation
_______________________________________________________________________
There is an emulator of a PI machine developed in C++. This one has it's own separate readme file.\
Supporting:\
    -4 bit version\
    -8 bit version\
<br/>
<br/>


Assembler
_______________________________________________________________________
There is an assembler for the PI architecture. That is a program that takes assembly code and interprets it into machine code.\
Supporting:\
    -4 bit version\
    -8 bit version\
<br/>
<br/>

## Further plans

Long term<br/>
_______________________________________________________________________<br/>
    -actually building a computer with logic gates<br/>
    -compilation of C to the PI assembly<br/>

    
## Navigation

PI_4bit folder contains everything pertaining to the 4-bit PI, PI_8bit folder contains everything pertaining to the 8-bit PI (including the VHDL design files), pi_vm folder contains the emulator, pi_asm folder contains the assembler.




