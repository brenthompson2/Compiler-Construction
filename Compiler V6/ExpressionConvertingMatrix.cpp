/* ==============================================================================

	File: ExpressionConvertingMatrix.cpp
	Author: Brendan Thompson
	Updated: 11/09/17

	Description: Implementation of ExpressionConvertingMatrix for getting actionTokens for infixToPostFix converter for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- for infixToPostFixConverter

============================================================================== */

#include "ExpressionConvertingMatrix.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

ExpressionConvertingMatrix::ExpressionConvertingMatrix(){
	createMatrix();
	// printMatrix();
	return;
}

ExpressionConvertingMatrix::~ExpressionConvertingMatrix(){
	return;
}

/* ==============================================================================
	Public Accessor Functions
============================================================================== */

// Takes in the two Matrix Indexes and returns the corresponding Action Token
ActionToken ExpressionConvertingMatrix::getActionToken(ValueToken currentInputValue, ValueToken currentTopSTwo){
	ActionToken currentActionToken;
	currentActionToken = inputArray[currentInputValue].topSTwoArray[currentTopSTwo];
	return currentActionToken;
}

/* ==============================================================================
	Print Functions
============================================================================== */

// Calls upon private print functions to help print out the matrix
void ExpressionConvertingMatrix::printMatrix(){

	InputObject *currentInput;
	ActionToken currentActionToken;

	printMatrixSTwoTokens();

	for (ValueToken currentInputValueToken = VALUE_TOKEN_ID; currentInputValueToken < NUM_VALUE_TOKENS; currentInputValueToken++){
		(*currentInput) = inputArray[currentInputValueToken];
		printMatrixValueToken(currentInputValueToken);

		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_NULL];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_EQUALS];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_PLUS];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_MINUS];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_TIMES];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_DIVIDE];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_LEFT_BRACKET];
		printActionToken(currentActionToken);
		currentActionToken = (*currentInput).topSTwoArray[VALUE_TOKEN_EXPONENT];
		printActionToken(currentActionToken);
		cout << endl;
	}
	return;
}

// Takes in an Action Token and prints out the Corresponding Token. Formatted to be part of printMatrix()
void ExpressionConvertingMatrix::printActionToken(ActionToken currentActionToken){
	switch (currentActionToken){
		case ACTION_TOKEN_S_ONE:
			cout << "\tS1";
			break;
		case ACTION_TOKEN_S_TWO:
			cout << "\tS2";
			break;
		case ACTION_TOKEN_U_ONE:
			cout << "\tU1";
			break;
		case ACTION_TOKEN_U_TWO:
			cout << "\tU2";
			break;
		case ACTION_TOKEN_U_THREE:
			cout << "\tU3";
			break;
		case ACTION_TOKEN_U_FOUR:
			cout << "\tU4";
			break;
		case ACTION_TOKEN_ERROR:
			cout << "\tE ";
			break;
	}
	return;
}


// Prints out the Matrix Header labels corresponding to the Top S Two Value Tokens. Formatted to be part of printMatrix()
void ExpressionConvertingMatrix::printMatrixSTwoTokens(){
	cout << "\tNULL\t=\t+\t-\t*\t/\t(\t[\t^\n";
	cout << "==========================================================================\n";
	return;
}

// Prints out a Matrix Column label that corresponds to the Input Value Token. Formatted to be part of printMatrix()
void ExpressionConvertingMatrix::printMatrixValueToken(ValueToken valueTokenNumber){
	switch (valueTokenNumber){
		case VALUE_TOKEN_ID:
			cout << "ID  ||";
			break;
		case VALUE_TOKEN_EQUALS:
			cout << "=   ||";
			break;
		case VALUE_TOKEN_PLUS:
			cout << "+   ||";
			break;
		case VALUE_TOKEN_MINUS:
			cout << "-   ||";
			break;
		case VALUE_TOKEN_TIMES:
			cout << "*   ||";
			break;
		case VALUE_TOKEN_DIVIDE:
			cout << "/   ||";
			break;
		case VALUE_TOKEN_LEFT_PARENTHESIS:
			cout << "(   ||";
			break;
		case VALUE_TOKEN_RIGHT_PARENTHESIS:
			cout << ")   ||";
			break;
		case VALUE_TOKEN_EXPONENT:
			cout << "^   ||";
			break;
		case VALUE_TOKEN_LEFT_BRACKET:
			cout << "[   ||";
			break;
		case VALUE_TOKEN_RIGHT_BRACKET:
			cout << "]   ||";
			break;
		case VALUE_TOKEN_EOL:
			cout << "EOL ||";
			break;
	}
	return;
}

/* ============================================================================================
	Private Matrix Constructor: Relates every VALUE_TOKEN of both arrays with the correct ACTION_TOKEN
============================================================================================ */

void ExpressionConvertingMatrix::createMatrix(){

	// Input ID
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_ONE;
	inputArray[VALUE_TOKEN_ID].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_S_ONE;

	// Input =
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EQUALS].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_ERROR;

	// Input +
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_PLUS].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_S_TWO;

	// Input -
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_MINUS].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_S_TWO;

	// Input *
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_TIMES].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_S_TWO;

	// Input /
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_U_ONE;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_DIVIDE].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_S_TWO;

	// Input (
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_S_TWO;

	// Input )
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_U_TWO;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_U_TWO;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_U_TWO;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_U_TWO;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_U_TWO;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_RIGHT_PARENTHESIS].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_U_TWO;

	// Input ^
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_EXPONENT].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_U_ONE;

	// Input [
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_S_TWO;
	inputArray[VALUE_TOKEN_LEFT_BRACKET].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_U_ONE;

	// Input ]
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_U_FOUR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_U_FOUR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_U_FOUR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_U_FOUR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_U_FOUR;
	inputArray[VALUE_TOKEN_RIGHT_BRACKET].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_U_FOUR;

	// Input EOL
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_NULL] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_EQUALS] = ACTION_TOKEN_U_THREE;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_PLUS] = ACTION_TOKEN_U_THREE;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_MINUS] = ACTION_TOKEN_U_THREE;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_TIMES] = ACTION_TOKEN_U_THREE;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_DIVIDE] = ACTION_TOKEN_U_THREE;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_LEFT_PARENTHESIS] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_LEFT_BRACKET] = ACTION_TOKEN_ERROR;
	inputArray[VALUE_TOKEN_EOL].topSTwoArray[VALUE_TOKEN_EXPONENT] = ACTION_TOKEN_U_THREE;
}