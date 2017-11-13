/* ==============================================================================

	File: ExpressionConvertingMatrix.h
	Author: Brendan Thompson
	Updated: 11/09/17

	Description: Interface for ExpressionConvertingMatrix for getting actionTokens for infixToPostFix converter for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- for ExpressionFixConverter

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO

using std::cin;
using std::cout;
using std::cerr;
using std::endl;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define NUM_VALUE_TOKENS 13

#define VALUE_TOKEN_NULL 0
#define VALUE_TOKEN_ID 1
#define VALUE_TOKEN_EQUALS 2
#define VALUE_TOKEN_PLUS 3
#define VALUE_TOKEN_MINUS 4
#define VALUE_TOKEN_TIMES 5
#define VALUE_TOKEN_DIVIDE 6
#define VALUE_TOKEN_LEFT_PARENTHESIS 7
#define VALUE_TOKEN_RIGHT_PARENTHESIS 8
#define VALUE_TOKEN_EXPONENT 9
#define VALUE_TOKEN_LEFT_BRACKET 10
#define VALUE_TOKEN_RIGHT_BRACKET 11
#define VALUE_TOKEN_EOL 12

#define ACTION_TOKEN_S_ONE 0
#define ACTION_TOKEN_S_TWO 1
#define ACTION_TOKEN_U_ONE 2
#define ACTION_TOKEN_U_TWO 3
#define ACTION_TOKEN_U_THREE 4
#define ACTION_TOKEN_U_FOUR 5
#define ACTION_TOKEN_ERROR 6

/* ==============================================================================
	Type Definitions
============================================================================== */

typedef unsigned int ValueToken;
typedef unsigned int ActionToken;

struct InputObject {
	ActionToken topSTwoArray[NUM_VALUE_TOKENS];
};

/* ==============================================================================
	Matrix Class Implementation
============================================================================== */

class ExpressionConvertingMatrix {
public:

	// Indexed According to
	InputObject inputArray[NUM_VALUE_TOKENS];

	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */

	ExpressionConvertingMatrix ();
	~ExpressionConvertingMatrix ();

	/* ==============================================================================
		Public Accessors
	============================================================================== */


	// Takes in the two Matrix Indexes and returns the corresponding Action Token
	ActionToken getActionToken(ValueToken currentInputValue, ValueToken currentTopSTwo);

	// Calls upon private print functions to help print out the matrix
	void printMatrix();

private:

	void createMatrix();

	/* ==============================================================================
		Private Print Functions
	============================================================================== */

	// Takes in an Action Token and prints out the Corresponding Token. Formatted to be part of printMatrix()
	void printActionToken(ActionToken currentActionToken);

	// Prints out the Matrix Header labels corresponding to the Top S Two Value Tokens. Formatted to be part of printMatrix()
	void printMatrixSTwoTokens();

	// Prints out a Matrix Column label that corresponds to the Input Value Token. Formatted to be part of printMatrix()
	void printMatrixValueToken(ValueToken valueTokenNumber);
};