# Brendan Thompson
# 09/05/17
# Makefile for Compiler Construction Project 1

# "make main" = Compile and Link
# "make clean" = remove created files (.o, trimmedOutput.txt)
# "./bjthompson18" = run

main: bjthompson18.o
	g++ -o bjthompson18 bjthompson18.o

bjthompson18.o: bjthompson18.cpp
	g++ -c bjthompson18.cpp

clean:
	rm bjthompson18 bjthompson18.o trimmedOutput.txt