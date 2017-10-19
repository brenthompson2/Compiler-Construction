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

main: CompilerDriver.o Compiler.o FileManager.o SymbolTable.o LineLabelTable.o tREAD.o tWRITE.o STOP.o DIM.o aREAD.o aWRITE.o GOTO.o LOOP.o LOOPEND.o IFA.o NOP.o LISTO.o
	g++ -o Compiler CompilerDriver.o Compiler.o FileManager.o SymbolTable.o LineLabelTable.o tREAD.o tWRITE.o STOP.o DIM.o aREAD.o aWRITE.o GOTO.o LOOP.o LOOPEND.o IFA.o NOP.o LISTO.o

CompilerDriver.o: CompilerDriver.cpp Compiler.o
	g++ -c CompilerDriver.cpp

Compiler.o: Compiler.cpp Compiler.h FileManager.o SymbolTable.o LineLabelTable.o tREAD.o tWRITE.o STOP.o DIM.o aREAD.o aWRITE.o GOTO.o LOOP.o LOOPEND.o IFA.o NOP.o LISTO.o
	g++ -c Compiler.cpp

FileManager.o: FileManager.cpp FileManager.h
	g++ -c FileManager.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h
	g++ -c SymbolTable.cpp

LineLabelTable.o: LineLabelTable.cpp LineLabelTable.h
	g++ -c LineLabelTable.cpp

#####################
###### Commands #####
#####################

tREAD.o: tREAD.cpp tREAD.h
	g++ -c tREAD.cpp

tWRITE.o: tWRITE.cpp tWRITE.h
	g++ -c tWRITE.cpp

STOP.o: STOP.cpp STOP.h
	g++ -c STOP.cpp

DIM.o: DIM.cpp DIM.h
	g++ -c DIM.cpp

aREAD.o: aREAD.cpp aREAD.h
	g++ -c aREAD.cpp

aWRITE.o: aWRITE.cpp aWRITE.h
	g++ -c aWRITE.cpp

GOTO.o: GOTO.cpp GOTO.h
	g++ -c GOTO.cpp

LOOP.o: LOOP.cpp LOOP.h
	g++ -c LOOP.cpp

LOOPEND.o: LOOPEND.cpp LOOPEND.h
	g++ -c LOOPEND.cpp

IFA.o: IFA.cpp IFA.h
	g++ -c IFA.cpp

NOP.o: NOP.cpp NOP.h
	g++ -c NOP.cpp

LISTO.o: LISTO.cpp LISTO.h
	g++ -c LISTO.cpp

#####################
####### Other #######
#####################

clean:
	rm Compiler *.o *.noblanks *.obj