This is an assembler for the PI architecture (a program that takes assembly code and interprets it into machine code).

There is a CMake file availible for compilation.



Usage:

There is a robust error handling system in the application - if something doesn't work, READ the error - I tried to make those messages rather helpful.

In general, you need to provide a file with the program and name of the output file.

Command line arguments:

pi_vm <-4|-8> <input file name> <-b|-d|-h> <output file name>



Example:

Hex file - 8 bit:	'pi_vm -8 code.pi -h code.hex'
Binary file - 8 bit:	'pi_vm -8 code.pi -b code.bin'
Decimal file - 4 bit:	'pi vm -4 code.pi -d code.decs' 



How to code?

PI assembly has 2 instructions: MOV and FLAG.

MOV syntax: MOV <destination>, <source>;
Destination and source can be registry numbers and memory addresses (please note, that you can't MOV from memory to memory - at least one of the addresses has to be a register)
Values have to be given in decimal form.

FLAG syntax: FLAG <flag number>, <value>;
Flag number is... a flag number. Value has a form of an arithmetic expression.

Flag value specifics: 

- You can put into a flag one of these things: Direct value, Carry Bit from the last operation and a logical sum of all bits on a specified memory address (for 4-bit PI this address has to be the register NO. 3 (the accumulator)).
- You can also put into a flag a combination of the aforementioned values (either a logical sum (OR) or a logical product (AND)
- You can negate the input byt putting the whole expression in parenthesis: () and putting a ~ operator in fromt of it.


FLAG examples:

FLAG 2, true; - Setting flag 2 to True;
FLAG 0, ~false - Setting flag 0 to True (negated false)
FLAG 1, true*CARRY - Setting flag 1 to AND of true and carry bit from the last operation
FLAG 1, ~(true*CARRY) - Same as above, but negated
FLAG 3, false+CARRY+67 - Setting flag 3 to OR of: false, carry bit from the last operation and sum of all bits at memory address 67
FLAG 3, ~(false+CARRY+67) - Same as above, but negated

You CAN'T do that: FLAG 3, false*CARRY+67 - it's either '+' or '*'



Data segments:

You can put data in memory by typing out the bytes:

65, 12, 45;

The above line would put those 3 numbers in 3 consecutive memory cells.

You can also repeat this by using the TIMES keyword:

65, 12, 45 TIMES 3;
is the same as:
65, 12, 45, 65, 12, 45, 65, 12, 45;



Hooks:

You can reference a memory address by name using a ,,hook", which is basically a label:

examplehook:
MOV 3, 4;

Now under the name examplehook there is address of that instruction. 

Doing:
MOV examplehook, 0;
will override the first byte of that MOV instruction.

You can use this for jumps by doing:

examplehook:	-referencing this address
MOV 3, 4;

jmp_examplehook: examplehook;	-putting this address in memory (basically a pointer)

Here we have both a hook and a data statement.

You can jump with:

MOV 0, jmp_examplehook;



Declarations:


Declarations can be used to de-reference pointers. For example:

MOV example, 6;		-referencing a declaration
MOV 3, >example;	-creating a declaration

This way we edit our own code (by pasting the contents of register 6 into the source field of a MOV instruction).
Result: Memory under the pointer stored at register 6 will be put into register 3.


The same can be done with a FLAG instruction:
FLAG 2, ~>example


Enjoy!
