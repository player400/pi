Those files are example executables for the PI emulator.

Look into the PI emulator readme for information on how to run them.


File structure:

<architecture (4 for 4-bit, 8 for 8-bit etc)>	|	1 byte
						
<machine code>					|	n bytes


The entire machine code is uploaded into the memory.
Note, that all CPU registers are memory-mapped (meaning that register 0 is also memory address 0).
Therefore first X bytes of machine code will actually go into the registers, allowing you to set start values in them!



 
