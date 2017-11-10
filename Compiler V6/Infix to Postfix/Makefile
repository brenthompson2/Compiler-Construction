# Brendan Thompson
# 11/09/17
# Makefile for Infix to Postfix Converter

# "make main" = Compile and Link
# "make clean" = removes all created files (Compiler, *.o, *.noblanks, *.obj, *.core, *.literal)
# "./Compiler <fileName.transy>" = compile the fileName

#######################
### Main Components ###
#######################

InfixToPostfix: Main.o ExpressionFixConverter.o ExpressionConvertingMatrix.o
	g++ -o InfixToPostfix Main.o ExpressionFixConverter.o ExpressionConvertingMatrix.o

Main.o: Main.cpp
	g++ -c Main.cpp

ExpressionConvertingMatrix.o: ExpressionConvertingMatrix.cpp ExpressionConvertingMatrix.h
	g++ -c ExpressionConvertingMatrix.cpp

ExpressionFixConverter.o: ExpressionFixConverter.cpp ExpressionFixConverter.h ExpressionConvertingMatrix.o
	g++ -c ExpressionFixConverter.cpp

clean:
	rm *.o
