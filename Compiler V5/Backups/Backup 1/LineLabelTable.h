/*
  ==============================================================================

	File: LineLabelTable.cpp
	Author: Brendan Thompson
	Updated: 10/13/17

	Description: Interface for LineLabelTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <algorithm>	// std::transform()
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_STRING_LENGTH 50
#define MAX_VARIABLE_NAME_LENGTH 128
#define MAX_NUM_LINES 1000
#define NOT_FOUND_IN_ARRAY -1

/* ==============================================================================
	Type Definitions
============================================================================== */

struct lineLabelObject {
	string labelName;
	int transyLineNumber;
	int objLineNumber;
};

/* ==============================================================================
	Line Label Table Class Interface
============================================================================== */

class LineLabelTable {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	LineLabelTable();
	~LineLabelTable();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */

	// adds a new line to the LineLabelTable by mapping it's transyLineNumber
	void addLine(int actualTransyLineNumber);

	// adds a label to the table index associated with the transyLineNumber
	void addLineLabel(string newLineLabel, int newTransyLineNumber);

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// returns the TransyLineNumber for the currentObjLineNumber
	int getTransyLineNumber(int currentObjLineNumber);

	// returns the currentObjLineNumber for the nameOfLabel
	int getObjLineNumber(string nameOfLabel);

	// iterates through the LineLabelTable and prints the labelName & memoryLocation
	void printLineLabelTable();

private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	int LineNumberArray[MAX_NUM_LINES]; // array for mapping line numbers, indexed in order of objLineNumber
	lineLabelObject LineLabelArray[MAX_NUM_LINES]; // array for mapping line labels to line numbers, indexed in order of appearance
	int globalNumLinesOfCode;
	int globalNumLabels;


	/* ==============================================================================
		Private Methods
	============================================================================== */

	// returns whether or not the line label already exists
	bool alreadyExists(string currentLineLabel);

};