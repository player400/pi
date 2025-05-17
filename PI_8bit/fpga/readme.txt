This is a VHDL FPGA design of a PI computer, for the Digilent Atlys board with the Xilinx Spartan-6 LX45 chip. 
It was developed using the Xlinx ISE WebPack software.

Files:
	readme.txt - you're here
	*.vhdl - design and simulation sources
	const.ucf - design constraint file for the top.vhdl module (defining a clock source and a couple of basic IOs, like switches, buttons and LEDs)
	pi.xise - proprietary file format used by the Xilinx ISE WebPack IDE for managing projects
	run.bat - script for deploying a generated top.bit file to the Atlys board, using CLI of the Digilent Adept software

Building and running:
	Prerequisites: Xilinx ISE WebPack 14.7 installed, Digilent Adept installed, Digilent Atlys board with the Xilinx Spartan-6 LX45 chip connected
	
	1. Run Xilinx ISE WebPack
	2. Go to ,,Open Project"
	3. Choose the pi.xise file in the dialog window
	4. On the bottom of the upper left window choose the Design tab
	5. On the top of that window ("View:" option) select Implementation
	6. In the dropdown list select xc6slx45-3csg324 > top.vhdl
	7. Click on the Generate Programming File option in the small window below, wait for the build to finish
	8. On Windows: left click on the run.bat file and press Enter. On Linux: run command "djtgcfg prog -d Atlys -i 0 -f top.bit" in this folder. 