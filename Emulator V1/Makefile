# Brendan Thompson
# 11/16/17
# Makefile for Executor V1

# "make" = Compile and Link
# "make clean" = removes all created files (Execute, *.o)
# "./Execute <fileName.transy>" = Execute the fileName

#######################
### Main Components ###
#######################

main: ExecutorDriver.o Executor.o EFileManager.o SymbolTable.o LiteralTable.o ProgramLineTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eNOP.o eLISTO.o elREAD.o elWRITE.o eCLS.o eCDUMP.o eSUBP.o eASSIGNMENT.o
	g++ -o Execute ExecutorDriver.o Executor.o EFileManager.o SymbolTable.o LiteralTable.o ProgramLineTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eNOP.o eLISTO.o elREAD.o elWRITE.o eCLS.o eCDUMP.o eSUBP.o eASSIGNMENT.o

ExecutorDriver.o: ExecutorDriver.cpp Executor.o
	g++ -c ExecutorDriver.cpp

Executor.o: Executor.cpp Executor.h EFileManager.o SymbolTable.o LiteralTable.o ProgramLineTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eNOP.o eLISTO.o elREAD.o elWRITE.o eCLS.o eCDUMP.o eSUBP.o eASSIGNMENT.o
	g++ -c Executor.cpp

EFileManager.o: EFileManager.cpp EFileManager.h LiteralTable.h
	g++ -c EFileManager.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h EFileManager.h
	g++ -c SymbolTable.cpp

LiteralTable.o: LiteralTable.cpp LiteralTable.h EFileManager.h
	g++ -c LiteralTable.cpp

ProgramLineTable.o: ProgramLineTable.cpp ProgramLineTable.h
	g++ -c ProgramLineTable.cpp

#######################################
###### Infix To Postfix Converter #####
#######################################

ExpressionConvertingMatrix.o: ExpressionConvertingMatrix.cpp ExpressionConvertingMatrix.h
	g++ -c ExpressionConvertingMatrix.cpp

ExpressionFixConverter.o: ExpressionFixConverter.cpp ExpressionFixConverter.h ExpressionConvertingMatrix.o
	g++ -c ExpressionFixConverter.cpp

########################
###### Commands V2 #####
########################

eREAD.o: eREAD.cpp eREAD.h
	g++ -c eREAD.cpp

eWRITE.o: eWRITE.cpp eWRITE.h
	g++ -c eWRITE.cpp

eSTOP.o: eSTOP.cpp eSTOP.h
	g++ -c eSTOP.cpp

########################
###### Commands V3 #####
########################

eDIM.o: eDIM.cpp eDIM.h
	g++ -c eDIM.cpp

eaREAD.o: eaREAD.cpp eaREAD.h
	g++ -c eaREAD.cpp

eaWRITE.o: eaWRITE.cpp eaWRITE.h
	g++ -c eaWRITE.cpp

########################
###### Commands V4 #####
########################

# eGOTO.o: eGOTO.cpp eGOTO.h
# 	g++ -c eGOTO.cpp

# eLOOP.o: eLOOP.cpp eLOOP.h
# 	g++ -c eLOOP.cpp

# eLOOPEND.o: eLOOPEND.cpp eLOOPEND.h
# 	g++ -c eLOOPEND.cpp

# eIFA.o: eIFA.cpp eIFA.h
# 	g++ -c eIFA.cpp

eNOP.o: eNOP.cpp eNOP.h
	g++ -c eNOP.cpp

eLISTO.o: eLISTO.cpp eLISTO.h
	g++ -c eLISTO.cpp

########################
###### Commands V5 #####
########################

elREAD.o: elREAD.cpp elREAD.h
	g++ -c elREAD.cpp

elWRITE.o: elWRITE.cpp elWRITE.h
	g++ -c elWRITE.cpp

# eIF.o: eIF.cpp eIF.h
# 	g++ -c eIF.cpp

eCLS.o: eCLS.cpp eCLS.h
	g++ -c eCLS.cpp

eCDUMP.o: eCDUMP.cpp eCDUMP.h
	g++ -c eCDUMP.cpp

eSUBP.o: eSUBP.cpp eSUBP.h
	g++ -c eSUBP.cpp

########################
###### Commands V6 #####
########################

eASSIGNMENT.o: eASSIGNMENT.cpp eASSIGNMENT.h ExpressionFixConverter.o
	g++ -c eASSIGNMENT.cpp

#####################
####### Other #######
#####################

clean:
	rm Execute *.o