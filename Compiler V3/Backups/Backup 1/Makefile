# Brendan Thompson
# 10/08/17
# Makefile for Compiler V3

# "make main" = Compile and Link
# "make clean" = removes created files
# "./Compiler <fileName.transy>" = compile the file
	# Currently doesn't work with flags

#####################
### Main Compiler ###
#####################

main: CompilerDriver.o Compiler.o FileManager.o SymbolTable.o tREAD.o tWRITE.o tSTOP.o DIM.o aREAD.o aWRITE.o
	g++ -o Compiler CompilerDriver.o Compiler.o FileManager.o SymbolTable.o tREAD.o tWRITE.o tSTOP.o DIM.o aREAD.o aWRITE.o

CompilerDriver.o: CompilerDriver.cpp Compiler.o
	g++ -c CompilerDriver.cpp

Compiler.o: Compiler.cpp Compiler.h FileManager.o SymbolTable.o tREAD.h tWRITE.h
	g++ -c Compiler.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	g++ -c SymbolTable.cpp

FileManager.o: FileManager.cpp FileManager.h
	g++ -c FileManager.cpp

#####################
###### Commands #####
#####################

tREAD.o: tREAD.cpp tREAD.h
	g++ -c tREAD.cpp

tWRITE.o: tWRITE.cpp tWRITE.h
	g++ -c tWRITE.cpp

tSTOP.o: tSTOP.cpp tSTOP.h
	g++ -c tSTOP.cpp

DIM.o: DIM.cpp DIM.h
	g++ -c DIM.cpp

aREAD.o: aREAD.cpp aREAD.h
	g++ -c aREAD.cpp

aWRITE.o: aWRITE.cpp aWRITE.h
	g++ -c aWRITE.cpp

#####################
####### Other #######
#####################

clean:
	rm Compiler *.o *.noblanks *.obj