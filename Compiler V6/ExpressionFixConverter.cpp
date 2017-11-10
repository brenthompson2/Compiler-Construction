/* ==============================================================================

	File: ExpressionFixConverter.cpp
	Author: Brendan Thompson
	Updated: 11/09/17

	Description: Implementation of Functions for ExpressionFixConverter for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- only implemented infix to postfix

============================================================================== */

#include "ExpressionFixConverter.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

ExpressionFixConverter::ExpressionFixConverter(){
	return;
}

ExpressionFixConverter::~ExpressionFixConverter(){
	return;
}

/* ==============================================================================
	Converters
============================================================================== */

// takes in an expression in infix and returns an expression in postfix
string ExpressionFixConverter::infixToPostfix(string currentExpression){
	bool continueParsingParameters = true;
	int currentCharIterator = 0;
	string currentInputValue;
	string newExpression;

	numTokensInSOne = 0;
	numTokensInSTwo = 0;

	while (continueParsingParameters){
		currentInputValue = getNextInputValue(&currentCharIterator, currentExpression);

		handleInputValue_In_Post(currentInputValue);

		if (currentInputValue[0] == END_OF_LINE_SENTINEL){
			continueParsingParameters = false;
		}
	}

	return newExpression;
}

// parses through the expression one character at a time and returns the next InputValue
string ExpressionFixConverter::getNextInputValue(int *currentCharIterator, string currentLine){
	char currentChar;
	string currentValueName = "";
	int numCharactersInValueName = 0;

	bool continueParsingValue = true;
	bool parsingVariableName = false;
	bool caseFound;

	while (continueParsingValue){
		currentChar = currentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t\t[ExpressionFixConverter]: Current Character: " << currentChar << endl;

		// ID: Variable or Constant
		if ((isalpha(currentChar)) || (isdigit(currentChar))){
			currentValueName += currentChar;
			numCharactersInValueName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[ExpressionFixConverter]: Current ID Name: " << currentValueName << endl;
		}

		// OPERATOR: = ^ + - * / ( ) [ ]
		if ((currentChar == '=') || (currentChar == '^') ||
				(currentChar == '+') || (currentChar == '-') ||
				(currentChar == '*') || (currentChar == '/') ||
				(currentChar == '(') || (currentChar == ')') ||
				(currentChar == '[') || (currentChar == ']')){

			if (numCharactersInValueName == 0){
				currentValueName[0] = currentChar;
				numCharactersInValueName++;
				(*currentCharIterator)++;
				// cout << "\t\t\t[ExpressionFixConverter]: Found Operator: " << currentValueName << endl;
			}
			continueParsingValue = false;
			caseFound = true;
		}

		// EOL
		if (currentChar == '\0'){
			if (numCharactersInValueName == 0){
				currentValueName[0] = END_OF_LINE_SENTINEL;
				numCharactersInValueName++;
				(*currentCharIterator)++;
				// cout << "\t\t\t[ExpressionFixConverter]: Found End Of Line: " << currentValueName << endl;
			}
			continueParsingValue = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[ExpressionFixConverter]: Invalid Syntax: Unknown Character ->" << currentChar << "<- in line: " << currentLine << endl;
			(*currentCharIterator)++;
		}
	}

	return currentValueName;
}

// Gets ActionToken from ExpressionConvertingMatrix then takes the appropriate action
void ExpressionFixConverter::handleInputValue_In_Post(string currentInputValue){

	ValueToken topSTwoToken;
	ValueToken InputValueToken;
	ActionToken nextAction;

	if (numTokensInSTwo == 0){
		topSTwoToken = VALUE_TOKEN_NULL;
	}
	else {
		topSTwoToken = sTwoArray[numTokensInSTwo - 1];
	}

	InputValueToken = getValueToken(currentInputValue);
	nextAction = conversionMatrix.getActionToken(InputValueToken ,topSTwoToken);

	// handleAction(nextAction);

	return;
}

// Return ValueToken related to currentInputValue
ValueToken ExpressionFixConverter::getValueToken(string currentInputValue){
	ValueToken currentValueToken;
	bool caseFound = false;

	if (currentInputValue[0] == '='){
		currentValueToken = VALUE_TOKEN_EQUALS;
		caseFound = true;
	}
	if (currentInputValue[0] == '+'){
		currentValueToken = VALUE_TOKEN_PLUS;
		caseFound = true;
	}
	if (currentInputValue[0] == '-'){
		currentValueToken = VALUE_TOKEN_MINUS;
		caseFound = true;
	}
	if (currentInputValue[0] == '*'){
		currentValueToken = VALUE_TOKEN_TIMES;
		caseFound = true;
	}
	if (currentInputValue[0] == '/'){
		currentValueToken = VALUE_TOKEN_DIVIDE;
		caseFound = true;
	}
	if (currentInputValue[0] == '('){
		currentValueToken = VALUE_TOKEN_LEFT_PARENTHESIS;
		caseFound = true;
	}
	if (currentInputValue[0] == ')'){
		currentValueToken = VALUE_TOKEN_RIGHT_PARENTHESIS;
		caseFound = true;
	}
	if (currentInputValue[0] == '['){
		currentValueToken = VALUE_TOKEN_LEFT_BRACKET;
		caseFound = true;
	}
	if (currentInputValue[0] == ']'){
		currentValueToken = VALUE_TOKEN_RIGHT_BRACKET;
		caseFound = true;
	}
	if (currentInputValue[0] == END_OF_LINE_SENTINEL){
		currentValueToken = VALUE_TOKEN_EOL;
		caseFound = true;
	}
	if (!caseFound){
		currentValueToken = VALUE_TOKEN_ID;
	}

	return currentValueToken;
}