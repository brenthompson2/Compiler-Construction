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

#define NUM_INDEX_VALUES 13

#define INDEX_NULL 0
#define INDEX_ID 1
#define INDEX_EQUALS 2
#define INDEX_PLUS 3
#define INDEX_MINUS 4
#define INDEX_TIMES 5
#define INDEX_DIVIDE 6
#define INDEX_LEFT_PARENTHESIS 7
#define INDEX_RIGHT_PARENTHESIS 8
#define INDEX_EXPONENT 9
#define INDEX_LEFT_BRACKET 10
#define INDEX_RIGHT_BRACKET 11
#define INDEX_EOL 12

#define TOKEN_S_ONE 0
#define TOKEN_S_TWO 1
#define TOKEN_U_ONE 2
#define TOKEN_U_TWO 3
#define TOKEN_U_THREE 4
#define TOKEN_U_FOUR 5
#define TOKEN_ERROR 6

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
	STwoOject topSTWOArray[NUM_INDEX_VALUES];
};


/* ==============================================================================
	Matrix Class Implementation
============================================================================== */

class ExpressionParsingMatrix {
public:

	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */

	ExpressionParsingMatrix ();
	~ExpressionParsingMatrix ();

private:

	void createMatrix();

	/* ==============================================================================
		Public Parsing Functions
	============================================================================== */




};