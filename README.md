A simple RISC computer architecture.
________________________________________________

Primitive Iterator, or PI is a computer architecture I designed.

It features an incredibly simple assembly - everything can be achieved with just two diferent instructions: MOV and FLAG.
Co-addressing of registers as memory allowed to significantly simplify the architecture.

The core principle behind PI, is that complexity should always be on the programmer's side. Therefore there is no complex, multi-step instructions (like LOOP, that we know from x86 processors).
Both instructions are designed to be executed in just one clock cycle and do only one, simple thing.

With PI assembly, you are essentially programming in micro-code.

More information is availible in the ISA document. Currently only availible only in the 4-bit version.

Further plans
____________________

I am not in the process of creating a logical simulation of an implementation of this architecture, using Circuit Verse logic simulator. Then probably an FPGA simulation will follow.

Eventually I plan on actually building the CPU based on the 8-bit version of this architecture (since 4-bit is not really practical for anything, except the most basic programs).

 


