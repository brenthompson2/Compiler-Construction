# Brendan Thompson
# 11/13/17
# Makefile for Executor V1

# "make main" = Compile and Link
# "make clean" = removes all created files (Executor, *.o)
# "./Executor <fileName.transy>" = Execute the fileName

#######################
### Main Components ###
#######################

main: ExecutorDriver.o Executor.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eGOTO.o eLOOP.o eLOOPEND.o eIFA.o eNOP.o eLISTO.o elREAD.o elWRITE.o eIF.o eCLS.o eCDUMP.o eSUBP.o eASSIGNMENT.o
	g++ -o Executor ExecutorDriver.o Executor.o FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eGOTO.o eLOOP.o eLOOPEND.o eIFA.o eNOP.o eLISTO.o elREAD.o elWRITE.o eIF.o eCLS.o eCDUMP.o eSUBP.o eASSIGNMENT.o

ExecutorDriver.o: ExecutorDriver.cpp Executor.o
	g++ -c ExecutorDriver.cpp

Executor.o: Executor.cpp Executor.h FileManager.o SymbolTable.o LiteralTable.o LineLabelTable.o ExpressionConvertingMatrix.o ExpressionFixConverter.o eREAD.o eWRITE.o eSTOP.o eDIM.o eaREAD.o eaWRITE.o eGOTO.o eLOOP.o eLOOPEND.o eIFA.o eNOP.o eLISTO.o elREAD.o elWRITE.o eIF.o eCLS.o eCDUMP.o eSUBP.o eASSIGNMENT.o
	g++ -c Executor.cpp

FileManager.o: FileManager.cpp FileManager.h LiteralTable.h LineLabelTable.h
	g++ -c FileManager.cpp

SymbolTable.o: SymbolTable.cpp SymbolTable.h FileManager.h
	g++ -c SymbolTable.cpp

LiteralTable.o: LiteralTable.cpp LiteralTable.h FileManager.h
	g++ -c LiteralTable.cpp

LineLabelTable.o: LineLabelTable.cpp LineLabelTable.h
	g++ -c LineLabelTable.cpp

# ProgramLineTable.o: ProgramLineTable.cpp ProgramLineTable.h
# 	g++ -c ProgramLineTable.cpp

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

eGOTO.o: eGOTO.cpp eGOTO.h
	g++ -c eGOTO.cpp

eLOOP.o: eLOOP.cpp eLOOP.h
	g++ -c eLOOP.cpp

eLOOPEND.o: eLOOPEND.cpp eLOOPEND.h
	g++ -c eLOOPEND.cpp

eIFA.o: eIFA.cpp eIFA.h
	g++ -c eIFA.cpp

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

eIF.o: eIF.cpp eIF.h
	g++ -c eIF.cpp

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
	rm Executor *.o