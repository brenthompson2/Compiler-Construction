# Compiler-Construction

Brendan Thompson

Transylvania University	Compiler Construction Fall 2017 with Dr. Moorman

The BRENxCompiler is written in C++ and turns programs written in the Transy Language (.transy) to Transy Object Code (.obj). An Emulator capable of running the Transy Object Code is currently under construction

This GitHub Repository was created for downloading, compiling, and running the code on a lab computer remotely via SSH

## Use

#### Compiling the Transy Compiler

In order to use this Transy Language (.transy) to Transy Object Code (.obj) compiler, the C++ code that it is written in must first be compiled into an executable

On Ubuntu: navigate the terminal to the directory of the preferred Compiler Version and run `make`

To remove all of the files run `make clean`

#### Using the Transy Compiler

On Ubuntu: The Transy Compiler but first be Compiled. Then, navigate the terminal to the directory with the `Compiler` executable and type `./Compiler <fileName>`

Flags:

	`-n` = keep noblanks file even if it successfully compiles
	`-o` = keep obj file even if it failed compilation
	`-l` = keep literal file even if it failed compilation
	`-c` = keep core file even if it failed compilation

Other Info:
	If no file is specified it will attempt to compile `test1.transy`

#### Running Transy Object Code

An emulator capable of running Transy Object Code on a computer is currently under construction

## Development

Check out the DevLog in each version of the compiler to see a detailed description of the different components as well as to view the status of construction as it was reported during each day of work
