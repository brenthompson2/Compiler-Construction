# Compiler-Construction

Brendan Thompson

Transylvania University	Compiler Construction Course Fall 2017 with Dr. Moorman

The BRENxCompiler is written in C++ and turns programs written in the Transy Language (.transy) to Transy Object Code (.obj).

The BRENxExecutor is written in C++ and interprets Transy Object Code (.obj)

This GitHub Repository was created for testing the code on a lab computer remotely via SSH

## Use

#### Compiling the Transy Compiler

In order to use this Transy Language (.transy) to Transy Object Code (.obj) compiler, the C++ code that it is written in must first be compiled into an executable. The Executor needs to be compiled as well, and is compiled using the same command below.

On Ubuntu: navigate the terminal to the directory of the preferred Compiler Version and run `make`

To remove all of the files run `make clean`

#### Using the Transy Compiler

On Ubuntu: The Transy Compiler must first be Compiled. Then, navigate the terminal to the directory with the `Compiler` executable and type `./Compiler <fileName.transy>`

Flags:

	`-c` = keep core file even if it failed compilation
	`-l` = keep literal file even if it failed compilation
	`-n` = keep noblanks file even if it successfully compiles
	`-o` = keep obj file even if it failed compilation
	`-x` = execute the code immediately after compilation

Other Info:
	If no file is specified it will attempt to compile `test1.transy`

#### Running Transy Object Code

On Ubuntu: The Transy Executor must first be Compiled. Then, navigate the terminal to the directory with the `BRENxExecutor` executable and type `./BRENxExecutor <fileName.obj>`

Flags:

	`-r` = range check to ensure array indexes are within the dimensions
	`-z` = use zero for undefined variables

Other Info:
	If no file is specified it will attempt to execute `test1.obj`

## Development

Check out the DevLog in each version of the compiler to see a detailed description of the different components as well as to view the status of construction as it was reported during each day of work
