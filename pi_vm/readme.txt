This is an emulator for the PI architecture.

There is a CMake file availible for compilation.


Usage:

There is a lot of exceptin throwing done in the application - if something doesn't work, READ the exception - I tried to make those messages rather helpful.

In general, you need to provide a file with the program for the emulated machine. Those can come in 3 formats: binary, hex and decimal. Here is how you run the program:

Hex file:	'pi_vm -h code.hex'
Binary file:	'pi_vm -b code.bin'
Decimal file:	'pi vm -d code.dec' 


Navigation:

-readme.txt - you are here
-CMakeLists.txt - (up to date) cmake
-.gitignore - git ignore
/example_executables - folder containing example code to run on the emulator
	-readme.txt - details about the example code (including the file structure)
	-example_program.hex - Hexadecimal file with a program calculating the Fibonacci sequence
	-example_program.bin - Binary file with a program calculating the Fibonacci sequence
	-example_program.dec - Decimal file with a program calculating the Fibonacci sequence
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
/programmer - (as in, the device that programms flash memory of a microcontroler)
	-Programmer.h - class responsible for programming (uploading exacutable file) into the emulator
	/ExecutableFileReader - code used by the Programmer class to read files
		-ExecutableFileReader.h - abstract parent class
		-BinaryFileReader.h - for binary
		-DecimalFileReader.h - for decimal file (as in, decimal numers written with ASCII characters)
		-HexadecimalFileReader.h - for hex files





