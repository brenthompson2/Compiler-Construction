/*
  ==============================================================================

	File: ExpressionFixConverter.h
	Author: Brendan Thompson
	Updated: 11/09/17

	Description: Interface for Functions for processing LOOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- only implemented infix to postfix

  ==============================================================================
*/

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat

#include "ExpressionConvertingMatrix.h"

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

// #define MAX_STRING_LENGTH 50
// #define MAX_VARIABLE_NAME_LENGTH 128	// currently using strings which may or may not allow for 128 characters
// #define MAX_ARGUMENTS 7
// #define INDEX_FIRST_CHAR_AFTER_ASSIGNMENT_COMMAND 4

#define MAX_NUM_INPUT_VALUES 40
#define END_OF_LINE_SENTINEL '@'

// const string ASSIGNMENT_OP_CODE = "14";

/* ==============================================================================
	Type Definitions
============================================================================== */

/* ==============================================================================
	ExpressionFixConverter Class Interface
============================================================================== */

class ExpressionFixConverter {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	ExpressionFixConverter();
	~ExpressionFixConverter();

	/* ==============================================================================
		Converters
	============================================================================== */

	// takes in an expression in infix and returns an expression in postfix
	string infixToPostfix(string currentExpression);



private:

	/* ==============================================================================
		Private Members
	============================================================================== */

	ExpressionConvertingMatrix conversionMatrix;

	int numTokensInSOne, numTokensInSTwo;
	string sOneArray[MAX_NUM_INPUT_VALUES];
	ValueToken sTwoArray[MAX_NUM_INPUT_VALUES];

	/* ==============================================================================
		Private Parsing Methods
	============================================================================== */

	// parses through the expression one character at a time and returns the next InputValue
	string getNextInputValue(int *currentCharIterator, string currentLine);

	// Gets ActionToken from ExpressionConvertingMatrix then takes the appropriate action
	void handleInputValue_In_Post(string currentInputValue);

	// Returns ValueToken related to currentInputValue
	ValueToken getValueToken(string currentInputValue);

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */
};