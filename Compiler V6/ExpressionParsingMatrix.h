/* ==============================================================================

	File: ExpressionParsingMatrix.h
	Author: Brendan Thompson
	Updated: 11/08/17

	Description: Matrix Used to Parse an Expression for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat
// #include <sstream> // std::stringstream str(" ")

#include "SymbolTable.h"
#include "FileManager.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_STWO 20
#define MAX_INPUT_STRINGS 20

/* ==============================================================================
	Type Definitions
============================================================================== */

struct STwoOject {
	bool isID;
	char operatorSymbol;
};

struct InputObject {
	bool isID;
	char operatorSymbol;
	STwoOject topSTWOArray[MAX_STWO];
};


/* ==============================================================================
	Matrix Class Implementation
============================================================================== */

class ExpressionParsingMatrix {
	public:




};