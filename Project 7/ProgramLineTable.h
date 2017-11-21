/* ==============================================================================

	File: ProgramLineTable.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Interface for ProgramLineTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- Manages Program Counter & Lines of Obj Code
		- MAX_NUM_LINES = 1000 lines in the program

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <algorithm>	// std::transform()
#include <sstream> //std::stringstream str(" ")
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_NUM_LINES 1000
#define INDEX_NOT_VALID_PROGRAM (MAX_NUM_LINES + 1)
#define MAX_NUM_PARAMETERS 40
#define NOT_VALID_PROGRAM -1
#define END_OF_PROGRAM -2

// Command Op Codes
// #define DIM_OP_CODE 0
#define READ_OP_CODE 1
#define WRITE_OP_CODE 2
#define STOP_OP_CODE 3
// // 4
// #define CDUMP_OP_CODE 5
// #define LISTO_OP_CODE 6
// #define NOP_OP_CODE 7
// #define GOTO_OP_CODE 8
// // 9
// #define IFA_OP_CODE 10
// #define AREAD_OP_CODE 11
// #define AWRITE_OP_CODE 12
// #define SUBP_OP_CODE 13
// #define LOOP_OP_CODE 14
// #define LOOPEND_OP_CODE 15
#define LREAD_OP_CODE 16
// #define LWRITE_OP_CODE 17
// #define IF_OP_CODE 18
// #define CLS_OP_CODE 19
// #define ASSIGNMENT_OP_CODE 20

/* ==============================================================================
	Type Definitions
============================================================================== */

struct ProgramLineObject {
	int lineOfCodeArray[MAX_NUM_PARAMETERS];
	int numElementsInLine;
	int opCode;
};

/* ==============================================================================
	ProgramLineTable Class Interface
============================================================================== */

class ProgramLineTable {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	ProgramLineTable();
	~ProgramLineTable();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// adds a new line of obj code to the ProgramLineTable
	void addLine(string newLine);

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// Turns the currentLine into a ProgramLineObject
	void tokenizeLine(string currentLine, ProgramLineObject *currentProgramLine);

	// Returns a pointer to a copy of the ProgramLineObject for the next line indexed at nextProgramCounter
	ProgramLineObject* getCopyOfNextProgramObject(int nextProgramCounter);

	// Returns a pointer to a copy of the programObjectToCopy
	ProgramLineObject* getCopyOfProgramObject(ProgramLineObject programObjectToCopy);

	// returns the op code for the line at objLineNumber
	int getOpCode(int objLineNumber);

	// iterates through the ProgramLineTable and prints the lineOfObj
	void printProgramLineTable();

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	ProgramLineObject programLineArray[MAX_NUM_LINES + 1]; // array of code indexed in order of objLineNumber
	int globalNumLinesOfCode;

	/* ==============================================================================
		Private Methods
	============================================================================== */

};