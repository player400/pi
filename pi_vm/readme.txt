This is an emulator for the PI architecture.

There is a CMake file availible for compilation.


Usage:

There is a robust error handling system in the application - if something doesn't work, READ the error - I tried to make those messages rather helpful.

In general, you need to provide a file with the program for the emulated machine. Those can come in 3 formats: binary, hex and decimal. Here is how you run the program:


Command line arguments:

pi_vm <-h|-b|-d> <file name> [-a] [architecture (4 bit, 8 bit etc) - 8 bit is default] [-debug|-p] [-c]

Hex file - 8 bit:			'pi_vm -h code.hex -p -c'
Binary file - 8 bit, debug mode:	'pi_vm -b code.bin -a 8 -debug'
Decimal file - 4 bit:			'pi vm -d code.dec -a 4 -c' 


Additional options:

'-debug' starts the emulator in debug mode

'-p' Optimizes the emulator output for writing into a text file (as opposed to providing an interactive CLI) - it turns off console clearing and text prompts.

Those two options (debug and p) can't be used together!

'-c' Displays number of CPU clock cycles executed since the emulator was started.




Navigation:

-readme.txt - you are here
-CMakeLists.txt - (up to date) cmake
-.gitignore - git ignore
/example_executables - folder containing example code to run on the emulator
	-readme.txt - details about the example code (including the file structure)
	/4-bit
		-example_program.hex - Hexadecimal file with a program calculating the Fibonacci sequence
		-example_program.bin - Binary file with a program calculating the Fibonacci sequence
		-example_program.dec - Decimal file with a program calculating the Fibonacci sequence
		-is_odd.bin - Binary file with a program deciding if a number is odd
	/8-bit 
		-hello_world.hex - Hexadecimal file with a program sending Hello, world! to output
-ControllerInterface.h - Class responsible for interacting between the user and the emulated machine.
-main.cpp - main function that sets everything up
-ProgramArgumentProcessing.h - Code for parsing command line program arguments
-utils.h - general utility code, used in many places
/computer - the core of this application - the emulated machine itself
	-Computer.h - class encapsulating the entire emulated machine into a nice black box, contains Processor and Memory classes
	-Processor.h - class representing the CPU
	-Memory.h - class representing the Memory
	/architecture - here there are several classes, that serve as the injected dependency in the dependency injection design pattern.
		-ComputerArchitecture.h - abstract parent class, provides multiple methods (mostly to the Processor) that are responsible for differenciating between 4bit, 8bit, 16bit etc. architectures
		-Bit4.h - dependency injected into the CPU for the 4-bit version of PI
		-Bit8.h - dependency injected into the CPU for the 8-bit version of PI
/programmer - (as in, the device that programms flash memory of a microcontroler)
	-Programmer.h - class responsible for programming (uploading exacutable file) into the emulator
	/ExecutableFileReader - code used by the Programmer class to read files
		-ExecutableFileReader.h - abstract parent class
		-BinaryFileReader.h - for binary
		-DecimalFileReader.h - for decimal file (as in, decimal numers written with ASCII characters)
		-HexadecimalFileReader.h - for hex files





