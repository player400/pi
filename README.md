A simple RISC computer architecture.
________________________________________________

Primitive Iterator, or PI is a computer architecture I designed.

It features an incredibly simple assembly - everything can be achieved with just two diferent instructions: MOV and FLAG.
Co-addressing of registers as memory allowed to significantly simplify the architecture.

The core principle behind PI, is that complexity should always be on the programmer's side. Therefore there is no complex, multi-step instructions (like LOOP, that we know from x86 processors).
Both instructions are designed to be executed in just one clock cycle and do only one, simple thing.

With PI assembly, you are essentially programming in micro-code.

More information is availible in the ISA document. Currently only availible only in the 4-bit version.

There is also a logical simulation of a 4-bit PI CPU availible (the .cv) file. This is a simulation made by Circuit Verse software.



Virtual Machine
____________________

Folder pi_vm contains a simple virtual machine for PI architecture, that is currently being developed.



Further plans
____________________

Eventually I plan on actually building the CPU based on the 8-bit version of this architecture (since 4-bit is not really practical for anything, except the most basic programs).

 


