# Brendan Thompson
# 09/24/17
# Makefile for Compiler V1

# "make main" = Compile and Link
# "make clean" = remove created files (.o, trimmedOutput.txt)
# "./Compiler" = run

main: CompilerDriver.o Compiler.o FileManager.o LookupTable.o tREAD.o tWRITE.o tSTOP.o
	g++ -o Compiler CompilerDriver.o Compiler.o FileManager.o LookupTable.o tREAD.o tWRITE.o tSTOP.o

CompilerDriver.o: CompilerDriver.cpp Compiler.o
	g++ -c CompilerDriver.cpp

Compiler.o: Compiler.cpp Compiler.h FileManager.o LookupTable.o tREAD.h tWRITE.h
	g++ -c Compiler.cpp

LookupTable.o: LookupTable.cpp LookupTable.h
	g++ -c LookupTable.cpp

FileManager.o: FileManager.cpp FileManager.h
	g++ -c FileManager.cpp

#Commands

tREAD.o: tREAD.cpp tREAD.h
	g++ -c tREAD.cpp

tWRITE.o: tWRITE.cpp tWRITE.h
	g++ -c tWRITE.cpp

tSTOP.o: tSTOP.cpp tSTOP.h
	g++ -c tSTOP.cpp

clean:
	rm Compiler CompilerDriver.o Compiler.o FileManager.o LookupTable.o tREAD.o tWRITE.o tSTOP.o *.noblanks *.obj