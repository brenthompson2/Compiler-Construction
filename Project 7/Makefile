# Brendan Thompson
# 11/20/17
# Makefile for Compiler V6

# "make main" = Compile and Link Both BREN_Compiler & BREN_Executor
# "make clean" = removes all created files (BREN_Compiler, BREN_Executor, *.o, *.noblanks, *.obj, *.core, *.literal)
# "./BREN_Compiler <fileName.transy>" = Compiles the fileName
# "./BREN_Executor <fileName.obj>" = Executes the fileName

main: BREN_Compiler BREN_Executor

###########################
### Compiler Components ###
###########################

BREN_Compiler: CompilerDriver.o Compiler.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o tREAD.o tWRITE.o tSTOP.o tDIM.o taREAD.o taWRITE.o tGOTO.o tLOOP.o tLOOPEND.o tIFA.o tNOP.o tLISTO.o tlREAD.o tlWRITE.o tIF.o tCLS.o tCDUMP.o tSUBP.o tASSIGNMENT.o
	g++ -o BREN_Compiler CompilerDriver.o Compiler.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o tREAD.o tWRITE.o tSTOP.o tDIM.o taREAD.o taWRITE.o tGOTO.o tLOOP.o tLOOPEND.o tIFA.o tNOP.o tLISTO.o tlREAD.o tlWRITE.o tIF.o tCLS.o tCDUMP.o tSUBP.o tASSIGNMENT.o

CompilerDriver.o: CompilerDriver.cpp Compiler.o
	g++ -c CompilerDriver.cpp

Compiler.o: Compiler.cpp Compiler.h FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o tREAD.o tWRITE.o tSTOP.o tDIM.o taREAD.o taWRITE.o tGOTO.o tLOOP.o tLOOPEND.o tIFA.o tNOP.o tLISTO.o tlREAD.o tlWRITE.o tIF.o tCLS.o tCDUMP.o tSUBP.o tASSIGNMENT.o
	g++ -c Compiler.cpp

FileManager.o: FileManager.cpp FileManager.h LiteralTable.h LineLabelTable.h
	g++ -c FileManager.cpp

LineLabelTable.o: LineLabelTable.cpp LineLabelTable.h
	g++ -c LineLabelTable.cpp

ExpressionConvertingMatrix.o: ExpressionConvertingMatrix.cpp ExpressionConvertingMatrix.h
	g++ -c ExpressionConvertingMatrix.cpp

ExpressionFixConverter.o: ExpressionFixConverter.cpp ExpressionFixConverter.h ExpressionConvertingMatrix.o
	g++ -c ExpressionFixConverter.cpp

###########################
### Executor Components ###
###########################

BREN_Executor: ExecutorDriver.o Executor.o EFileManager.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ProgramLineTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eNOP.o eLISTO.o elREAD.o elWRITE.o eCLS.o eCDUMP.o eSUBP.o
	g++ -o BREN_Executor ExecutorDriver.o Executor.o EFileManager.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ProgramLineTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eNOP.o eLISTO.o elREAD.o elWRITE.o eCLS.o eCDUMP.o eSUBP.o

ExecutorDriver.o: ExecutorDriver.cpp Executor.o
	g++ -c ExecutorDriver.cpp

Executor.o: Executor.cpp Executor.h EFileManager.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ProgramLineTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eNOP.o eLISTO.o elREAD.o elWRITE.o eCLS.o eCDUMP.o eSUBP.o
	g++ -c Executor.cpp

EFileManager.o: EFileManager.cpp EFileManager.h LiteralTable.h
	g++ -c EFileManager.cpp

ProgramLineTable.o: ProgramLineTable.cpp ProgramLineTable.h
	g++ -c ProgramLineTable.cpp

###########################
### Shared Components ###
###########################

SymbolTable.o: SymbolTable.cpp SymbolTable.h FileManager.h
	g++ -c SymbolTable.cpp

LiteralTable.o: LiteralTable.cpp LiteralTable.h FileManager.h
	g++ -c LiteralTable.cpp

#####################
###### Commands #####
#####################

tREAD.o: ./CompilerCommands/tREAD.cpp ./CompilerCommands/tREAD.h
	g++ -c ./CompilerCommands/tREAD.cpp

eREAD.o: ./ExecutorCommands/eREAD.cpp ./ExecutorCommands/eREAD.h ProgramLineTable.h
	g++ -c ./ExecutorCommands/eREAD.cpp

tWRITE.o: ./CompilerCommands/tWRITE.cpp ./CompilerCommands/tWRITE.h
	g++ -c ./CompilerCommands/tWRITE.cpp

eWRITE.o: ./ExecutorCommands/eWRITE.cpp ./ExecutorCommands/eWRITE.h ProgramLineTable.h
	g++ -c ./ExecutorCommands/eWRITE.cpp

tSTOP.o: ./CompilerCommands/tSTOP.cpp ./CompilerCommands/tSTOP.h
	g++ -c ./CompilerCommands/tSTOP.cpp

eSTOP.o: ./ExecutorCommands/eSTOP.cpp ./ExecutorCommands/eSTOP.h
	g++ -c ./ExecutorCommands/eSTOP.cpp

tDIM.o: ./CompilerCommands/tDIM.cpp ./CompilerCommands/tDIM.h
	g++ -c ./CompilerCommands/tDIM.cpp

eDIM.o: ./ExecutorCommands/eDIM.cpp ./ExecutorCommands/eDIM.h
	g++ -c ./ExecutorCommands/eDIM.cpp

taREAD.o: ./CompilerCommands/taREAD.cpp ./CompilerCommands/taREAD.h
	g++ -c ./CompilerCommands/taREAD.cpp

eaREAD.o: ./ExecutorCommands/eaREAD.cpp ./ExecutorCommands/eaREAD.h
	g++ -c ./ExecutorCommands/eaREAD.cpp

taWRITE.o: ./CompilerCommands/taWRITE.cpp ./CompilerCommands/taWRITE.h
	g++ -c ./CompilerCommands/taWRITE.cpp

eaWRITE.o: ./ExecutorCommands/eaWRITE.cpp ./ExecutorCommands/eaWRITE.h
	g++ -c ./ExecutorCommands/eaWRITE.cpp

tGOTO.o: ./CompilerCommands/tGOTO.cpp ./CompilerCommands/tGOTO.h
	g++ -c ./CompilerCommands/tGOTO.cpp

# eGOTO.o: ./ExecutorCommands/eGOTO.cpp ./ExecutorCommands/eGOTO.h
# 	g++ -c ./ExecutorCommands/eGOTO.cpp

tLOOP.o: ./CompilerCommands/tLOOP.cpp ./CompilerCommands/tLOOP.h
	g++ -c ./CompilerCommands/tLOOP.cpp

# eLOOP.o: ./ExecutorCommands/eLOOP.cpp ./ExecutorCommands/eLOOP.h
# 	g++ -c ./ExecutorCommands/eLOOP.cpp

tLOOPEND.o: ./CompilerCommands/tLOOPEND.cpp ./CompilerCommands/tLOOPEND.h
	g++ -c ./CompilerCommands/tLOOPEND.cpp

# eLOOPEND.o: ./ExecutorCommands/eLOOPEND.cpp ./ExecutorCommands/eLOOPEND.h
# 	g++ -c ./ExecutorCommands/eLOOPEND.cpp

tIFA.o: ./CompilerCommands/tIFA.cpp ./CompilerCommands/tIFA.h
	g++ -c ./CompilerCommands/tIFA.cpp

# eIFA.o: ./ExecutorCommands/eIFA.cpp ./ExecutorCommands/eIFA.h
# 	g++ -c ./ExecutorCommands/eIFA.cpp

tNOP.o: ./CompilerCommands/tNOP.cpp ./CompilerCommands/tNOP.h
	g++ -c ./CompilerCommands/tNOP.cpp

eNOP.o: ./ExecutorCommands/eNOP.cpp ./ExecutorCommands/eNOP.h
	g++ -c ./ExecutorCommands/eNOP.cpp

tLISTO.o: ./CompilerCommands/tLISTO.cpp ./CompilerCommands/tLISTO.h
	g++ -c ./CompilerCommands/tLISTO.cpp

eLISTO.o: ./ExecutorCommands/eLISTO.cpp ./ExecutorCommands/eLISTO.h
	g++ -c ./ExecutorCommands/eLISTO.cpp

tlREAD.o: ./CompilerCommands/tlREAD.cpp ./CompilerCommands/tlREAD.h
	g++ -c ./CompilerCommands/tlREAD.cpp

elREAD.o: ./ExecutorCommands/elREAD.cpp ./ExecutorCommands/elREAD.h
	g++ -c ./ExecutorCommands/elREAD.cpp

tlWRITE.o: ./CompilerCommands/tlWRITE.cpp ./CompilerCommands/tlWRITE.h
	g++ -c ./CompilerCommands/tlWRITE.cpp

elWRITE.o: ./ExecutorCommands/elWRITE.cpp ./ExecutorCommands/elWRITE.h
	g++ -c ./ExecutorCommands/elWRITE.cpp

tIF.o: ./CompilerCommands/tIF.cpp ./CompilerCommands/tIF.h
	g++ -c ./CompilerCommands/tIF.cpp

# eIF.o: ./ExecutorCommands/eIF.cpp ./ExecutorCommands/eIF.h
# 	g++ -c ./ExecutorCommands/eIF.cpp

tCLS.o: ./CompilerCommands/tCLS.cpp ./CompilerCommands/tCLS.h
	g++ -c ./CompilerCommands/tCLS.cpp

eCLS.o: ./ExecutorCommands/eCLS.cpp ./ExecutorCommands/eCLS.h
	g++ -c ./ExecutorCommands/eCLS.cpp

tCDUMP.o: ./CompilerCommands/tCDUMP.cpp ./CompilerCommands/tCDUMP.h
	g++ -c ./CompilerCommands/tCDUMP.cpp

eCDUMP.o: ./ExecutorCommands/eCDUMP.cpp ./ExecutorCommands/eCDUMP.h ProgramLineTable.h
	g++ -c ./ExecutorCommands/eCDUMP.cpp

tSUBP.o: ./CompilerCommands/tSUBP.cpp ./CompilerCommands/tSUBP.h
	g++ -c ./CompilerCommands/tSUBP.cpp

eSUBP.o: ./ExecutorCommands/eSUBP.cpp ./ExecutorCommands/eSUBP.h
	g++ -c ./ExecutorCommands/eSUBP.cpp

tASSIGNMENT.o: ./CompilerCommands/tASSIGNMENT.cpp ./CompilerCommands/tASSIGNMENT.h ExpressionFixConverter.o
	g++ -c ./CompilerCommands/tASSIGNMENT.cpp

# eASSIGNMENT.o: ./ExecutorCommands/eASSIGNMENT.cpp ./ExecutorCommands/eASSIGNMENT.h
# 	g++ -c ./ExecutorCommands/eASSIGNMENT.cpp

#####################
####### Other #######
#####################

clean:
	rm BREN_Compiler BREN_Executor *.o *.noblanks *.obj *.core *.literal