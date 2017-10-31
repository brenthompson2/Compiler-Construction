# Brendan Thompson
# 10/30/17
# Makefile for Compiler V5

# "make main" = Compile and Link
# "make clean" = removes all created files (Compiler, *.o, *.noblanks, *.obj, *.core, *.literal)
# "./Compiler <fileName.transy>" = compile the fileName

#######################
### Main Components ###
#######################

main: CompilerDriver.o Compiler.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o tREAD.o tWRITE.o tSTOP.o tDIM.o taREAD.o taWRITE.o tGOTO.o tLOOP.o tLOOPEND.o tIFA.o tNOP.o tLISTO.o tlREAD.o tlWRITE.o tIF.o tCLS.o tCDUMP.o tSUBP.o
	g++ -o Compiler CompilerDriver.o Compiler.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o tREAD.o tWRITE.o tSTOP.o tDIM.o taREAD.o taWRITE.o tGOTO.o tLOOP.o tLOOPEND.o tIFA.o tNOP.o tLISTO.o tlREAD.o tlWRITE.o tIF.o tCLS.o tCDUMP.o tSUBP.o

CompilerDriver.o: CompilerDriver.cpp Compiler.o
	g++ -c CompilerDriver.cpp

Compiler.o: Compiler.cpp Compiler.h FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o tREAD.o tWRITE.o tSTOP.o tDIM.o taREAD.o taWRITE.o tGOTO.o tLOOP.o tLOOPEND.o tIFA.o tNOP.o tLISTO.o tlREAD.o tlWRITE.o tIF.o tCLS.o tCDUMP.o tSUBP.o
	g++ -c Compiler.cpp

FileManager.o: FileManager.cpp FileManager.h LiteralTable.h LineLabelTable.h
	g++ -c FileManager.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h FileManager.h
	g++ -c SymbolTable.cpp

LiteralTable.o: LiteralTable.cpp LiteralTable.h FileManager.h
	g++ -c LiteralTable.cpp

LineLabelTable.o: LineLabelTable.cpp LineLabelTable.h
	g++ -c LineLabelTable.cpp

########################
###### Commands V2 #####
########################

tREAD.o: tREAD.cpp tREAD.h
	g++ -c tREAD.cpp

tWRITE.o: tWRITE.cpp tWRITE.h
	g++ -c tWRITE.cpp

tSTOP.o: tSTOP.cpp tSTOP.h
	g++ -c tSTOP.cpp

########################
###### Commands V3 #####
########################

tDIM.o: tDIM.cpp tDIM.h
	g++ -c tDIM.cpp

taREAD.o: taREAD.cpp taREAD.h
	g++ -c taREAD.cpp

taWRITE.o: taWRITE.cpp taWRITE.h
	g++ -c taWRITE.cpp

########################
###### Commands V4 #####
########################

tGOTO.o: tGOTO.cpp tGOTO.h
	g++ -c tGOTO.cpp

tLOOP.o: tLOOP.cpp tLOOP.h
	g++ -c tLOOP.cpp

tLOOPEND.o: tLOOPEND.cpp tLOOPEND.h
	g++ -c tLOOPEND.cpp

tIFA.o: tIFA.cpp tIFA.h
	g++ -c tIFA.cpp

tNOP.o: tNOP.cpp tNOP.h
	g++ -c tNOP.cpp

tLISTO.o: tLISTO.cpp tLISTO.h
	g++ -c tLISTO.cpp

########################
###### Commands V5 #####
########################

tlREAD.o: tlREAD.cpp tlREAD.h
	g++ -c tlREAD.cpp

tlWRITE.o: tlWRITE.cpp tlWRITE.h
	g++ -c tlWRITE.cpp

tIF.o: tIF.cpp tIF.h
	g++ -c tIF.cpp

tCLS.o: tCLS.cpp tCLS.h
	g++ -c tCLS.cpp

tCDUMP.o: tCDUMP.cpp tCDUMP.h
	g++ -c tCDUMP.cpp

tSUBP.o: tSUBP.cpp tSUBP.h
	g++ -c tSUBP.cpp

#####################
####### Other #######
#####################

clean:
	rm Compiler *.o *.noblanks *.obj *.core *.literal