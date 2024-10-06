## Primitive Iterator (PI)

Primitive Iterator (or PI) is a RISC Von Neumann computer architecture I designed.

It features an incredibly simple assembly - everything can be achieved with just two diferent instructions: MOV and FLAG.
Memory mapping of registers allowed to significantly simplify the architecture.

The core principle behind PI, is that complexity should always be on the programmer's side. Therefore there is no complex, multi-step instructions (like LOOP, that we know from x86 processors).
Both instructions are designed to be executed in just one clock cycle and do only one, simple thing.

With PI assembly, you are essentially programming in micro-code.

It's also possible to implement it using a pipeline, which would make for a whooping 2 instructions per clock cycle. 
Simplicity allows for very few layers of logic gates, which (in theory) should make for low latency and thus a fast clock.

More information is availible in the ISA document. Currently only availible only in the [4-bit version](PI_4bit/InstructionSetArchitecture_FullEdition.pdf).


## Progress

Documentation
_______________________________________________________________________
ISA (Instruction Set Architecture) document.\
Availible for:\
    -4bit version\
<br/>
<br/>


Schematic
_______________________________________________________________________
Logical design/simulation (on the logic gate level) of a PI computer made with the Circuit Verse software.\ 
Availible for:\
    -4bit version\
<br/>
<br/>



Emulation
_______________________________________________________________________
There is an emulator of a PI computer developed in C++. This one has it's own separate readme file.\
Supporting:\
    -4 bit version\
<br/>
<br/>
    

## Further plans

Short term<br/>
_______________________________________________________________________<br/>
    -developing an 8-bit version of the architecture (ISA)<br/>
    -continued development of the emulatorm, including support for 8-bit<br/>
    -(maybe) a Circuit Verse schematic for the 8-bit version<br/>
    -an assembler (ie. a program turning assembly into machine code)<br/>


<br/>
<br/>
Long term<br/>
_______________________________________________________________________<br/>
    -developing an 8-bit PI computer on FPGA<br/>
    -actually building a computer with logic gates<br/>
    -compilation of C to the PI assembly<br/>

    
## Navigation

PL_4bit folder contains everything pertaining to the 4-bit PI, pi_vm folder contains the emulator.



