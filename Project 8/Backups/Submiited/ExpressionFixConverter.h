/*
  ==============================================================================

	File: ExpressionFixConverter.h
	Author: Brendan Thompson
	Updated: 11/10/17

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

	// takes in an infix expression, converts it to postfix and puts it into newExpression, and also manipulates numValsInNewExpression. Returns num errors
	int infixToPostfix(string currentExpression, string newExpression[], int *numValsInNewExpression);



private:

	/* ==============================================================================
		Private Members
	============================================================================== */
	int globalNumErrors;

	ExpressionConvertingMatrix conversionMatrix;

	int indexTopSOne, indexTopSTwo;
	string sOneArray[MAX_NUM_INPUT_VALUES];
	string sTwoArray[MAX_NUM_INPUT_VALUES];

	/* ==============================================================================
		Private Parsing Methods
	============================================================================== */

	// parses through the expression one character at a time and returns the next InputValue
	string getNextInputValue(int *currentCharIterator, string currentLine);

	/* ==============================================================================
		Private Handler Methods
	============================================================================== */

	// Gets ActionToken from ExpressionConvertingMatrix then takes the appropriate action
	void handleInputValue_In_Post(string currentInputValue);

	// Handles executing the action referred to be currentAction
	void handleAction(ActionToken currentAction, string currentInputValue);

	// Handles executing the U1 action
	void handleUOne(string currentInputValue);

	// Handles executing the U2 action
	void handleUTwo(string currentInputValue);

	// Handles executing the U3 action
	void handleUThree(string currentInputValue);

	// Handles executing the U4 action
	void handleUFour(string currentInputValue);

	/* ==============================================================================
		Private Manipulator Methods
	============================================================================== */

	// Pushes newValue onto the S1 stack
	void pushSOne(string newValue);

	// Pops top off S1
	void popSOne();

	// Pushes newValue onto the S2 stack
	void pushSTwo(string newValue);

	// Pops top off S2
	void popSTwo();

	/* ==============================================================================
		Private Accessor Methods
	============================================================================== */

	void printStacks();

	// Gets the top of S1
	string getTopSOne();

	// Gets the top of S2
	string getTopSTwo();

	// Gets ValueToken related to currentInputValue
	ValueToken getValueToken(string currentInputValue);

};