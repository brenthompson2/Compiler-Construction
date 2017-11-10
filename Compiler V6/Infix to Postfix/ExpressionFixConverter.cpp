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

// takes in an infix expression, converts it to postfix and puts it into newExpression, and also manipulates numValsInNewExpression
void ExpressionFixConverter::infixToPostfix(string currentExpression, string newExpression[], int *numValsInNewExpression){
	bool continueParsingParameters = true;
	int currentCharIterator = 0;
	string currentInputValue;

	indexTopSOne = -1;
	indexTopSTwo = -1;
	globalNumErrors = 0;

	int tempCounter = 0;

	while (continueParsingParameters){
		currentInputValue = getNextInputValue(&currentCharIterator, currentExpression);
		// cout << "\t\t\t\t[ExpressionFixConverter]: Got Input Value " << currentInputValue << endl;
		handleInputValue_In_Post(currentInputValue);

		// printStacks();

		if (currentInputValue[0] == END_OF_LINE_SENTINEL){
			continueParsingParameters = false;
		}

		if (tempCounter > 10) {
			continueParsingParameters = false;
		}
		tempCounter++;
	}

	// Deep Copy S1 into newExpression
	for (int i = 0; i <= indexTopSOne; i++) {
		newExpression[i] = sOneArray[i];
	}
	(*numValsInNewExpression) = indexTopSOne;

	return;
}

/* ==============================================================================
	Private Parsing Methods
============================================================================== */

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
		// cout << "\t\t\t\t[ExpressionFixConverter]: Current Character: " << currentChar << endl;

		// ID: Variable or Constant
		if ((isalpha(currentChar)) || (isdigit(currentChar))){
			currentValueName += currentChar;
			numCharactersInValueName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t\t[ExpressionFixConverter]: Current ID Name: " << currentValueName << endl;
		}

		// OPERATOR: = ^ + - * / ( ) [ ]
		if ((currentChar == '=') || (currentChar == '^') ||
				(currentChar == '+') || (currentChar == '-') ||
				(currentChar == '*') || (currentChar == '/') ||
				(currentChar == '(') || (currentChar == ')') ||
				(currentChar == '[') || (currentChar == ']')){

			if (numCharactersInValueName == 0){
				currentValueName += currentChar;
				numCharactersInValueName++;
				(*currentCharIterator)++;
				// cout << "\t\t\t\t[ExpressionFixConverter]: Found Operator: " << currentValueName << endl;
			}
			continueParsingValue = false;
			caseFound = true;
		}

		// EOL
		if (currentChar == '\0'){
			if (numCharactersInValueName == 0){
				currentValueName += END_OF_LINE_SENTINEL;
				numCharactersInValueName++;
				(*currentCharIterator)++;
				// cout << "\t\t\t\t[ExpressionFixConverter]: Found End Of Line: " << currentValueName << endl;
			}
			continueParsingValue = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t\t[ExpressionFixConverter]: Invalid Syntax: Unknown Character ->" << currentChar << "<- in line: " << currentLine << endl;
			globalNumErrors++;
			(*currentCharIterator)++;
		}
	}

	return currentValueName;
}

/* ==============================================================================
	Private Handler Methods
============================================================================== */

// Gets ActionToken from ExpressionConvertingMatrix then takes the appropriate action
void ExpressionFixConverter::handleInputValue_In_Post(string currentInputValue){
	string topSTwo;
	ValueToken inputValueToken;
	ValueToken topSTwoToken;
	ActionToken nextAction;

	topSTwo = getTopSTwo();
	topSTwoToken = getValueToken(topSTwo);
	// cout << "\t\t\t\t[ExpressionFixConverter]: Top S2: " << topSTwo << endl;

	inputValueToken = getValueToken(currentInputValue);
	// cout << "\t\t\t\t[ExpressionFixConverter]: Input Value: " << currentInputValue << endl;

	nextAction = conversionMatrix.getActionToken(inputValueToken ,topSTwoToken);
	// cout << "\t\t\t\t[ExpressionFixConverter]: Got Action Token " << nextAction << endl;
	handleAction(nextAction, currentInputValue);

	return;
}

// Handles executing the action referred to be currentAction
void ExpressionFixConverter::handleAction(ActionToken currentAction, string currentInputValue){
	switch (currentAction){
		case ACTION_TOKEN_S_ONE:
			pushSOne(currentInputValue);
			break;
		case ACTION_TOKEN_S_TWO:
			pushSTwo(currentInputValue);
			break;
		case ACTION_TOKEN_U_ONE:
			handleUOne(currentInputValue);
			break;
		case ACTION_TOKEN_U_TWO:
			handleUTwo(currentInputValue);
			break;
		case ACTION_TOKEN_U_THREE:
			handleUThree(currentInputValue);
			break;
		case ACTION_TOKEN_U_FOUR:
			handleUFour(currentInputValue);
			break;
		case ACTION_TOKEN_ERROR:
			cout << "\t\t\t\t[ExpressionFixConverter]: Error! Invalid Expression!\n";
			globalNumErrors++;
			break;
	}
}

// Handles executing the U1 action
void ExpressionFixConverter::handleUOne(string currentInputValue){
	string tempValue = getTopSTwo();
	popSTwo();
	pushSOne(tempValue);
	pushSTwo(currentInputValue);
	return;
}

// Handles executing the U2 action
void ExpressionFixConverter::handleUTwo(string currentInputValue){
	bool openContainer = true;
	string tempValue;
	while (openContainer) {
		tempValue = getTopSTwo();
		popSTwo();
		if (tempValue != "(") {
			pushSOne(tempValue);
		}
		else {
			openContainer = false;
		}
	}
	return;
}

// Handles executing the U3 action
void ExpressionFixConverter::handleUThree(string currentInputValue){
	string tempValue;
	while (indexTopSTwo > -1) {
		tempValue = getTopSTwo();
		popSTwo();
		pushSOne(tempValue);
	}
	return;
}

// Handles executing the U4 action
void ExpressionFixConverter::handleUFour(string currentInputValue){
	bool openContainer;
	string tempValue;
	while (openContainer) {
		tempValue = getTopSTwo();
		popSTwo();
		if (tempValue != "[") {
			pushSOne(tempValue);
		}
		else {
			pushSOne("[");
			openContainer = false;
		}
	}
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// Pushes newValue onto the SOne stack
void ExpressionFixConverter::pushSOne(string newValue){
	indexTopSOne++;
	sOneArray[indexTopSOne] = newValue;
	// cout << "\t\t\t\t[ExpressionFixConverter]: Pushed " << sOneArray[indexTopSOne] << " to top S1\n";
	return;
}

// Pops top off SOne
void ExpressionFixConverter::popSOne(){
	indexTopSOne--;
	return;
}

// Pushes newValue onto the STwo stack
void ExpressionFixConverter::pushSTwo(string newValue){
	indexTopSTwo++;
	sTwoArray[indexTopSTwo] = newValue;
	// cout << "\t\t\t\t[ExpressionFixConverter]: Pushed " << sTwoArray[indexTopSTwo] << " to top S2\n";
	return;
}

// Pops top off STwo
void ExpressionFixConverter::popSTwo(){
	indexTopSTwo--;
	return;
}

/* ==============================================================================
	Private Accessor Methods
============================================================================== */

void ExpressionFixConverter::printStacks(){
	int counter;

	cout << "\t\t\t\t\tS1:";
	if (indexTopSOne > -1){
		counter = 0;
		while (counter <= indexTopSOne){
			cout << "\t" << sOneArray[counter];
			counter++;
		}
	}
	cout << "\t--\n";

	cout << "\t\t\t\t\tS2:";
	if (indexTopSTwo > -1){
		counter = 0;
		while (counter <= indexTopSTwo){
			cout << "\t" << sTwoArray[counter];
			counter++;
		}
	}
	cout << "\t--\n";

	return;
}

string ExpressionFixConverter::getTopSOne(){
	if (indexTopSTwo == -1){
		return "NULL";
	}
	else {
		return sOneArray[indexTopSOne];
	}
}
string ExpressionFixConverter::getTopSTwo(){
	if (indexTopSTwo == -1){
		return "NULL";
	}
	else {
		return sTwoArray[indexTopSTwo];
	}
}

// Return ValueToken related to currentInputValue
ValueToken ExpressionFixConverter::getValueToken(string currentInputValue){
	ValueToken currentValueToken;
	bool caseFound = false;


	if (currentInputValue == "NULL"){
		currentValueToken = VALUE_TOKEN_NULL;
		caseFound = true;
	}
	if (currentInputValue == "="){
		currentValueToken = VALUE_TOKEN_EQUALS;
		caseFound = true;
	}
	if (currentInputValue == "+"){
		currentValueToken = VALUE_TOKEN_PLUS;
		caseFound = true;
	}
	if (currentInputValue == "-"){
		currentValueToken = VALUE_TOKEN_MINUS;
		caseFound = true;
	}
	if (currentInputValue == "*"){
		currentValueToken = VALUE_TOKEN_TIMES;
		caseFound = true;
	}
	if (currentInputValue == "/"){
		currentValueToken = VALUE_TOKEN_DIVIDE;
		caseFound = true;
	}
	if (currentInputValue == "("){
		currentValueToken = VALUE_TOKEN_LEFT_PARENTHESIS;
		caseFound = true;
	}
	if (currentInputValue == ")"){
		currentValueToken = VALUE_TOKEN_RIGHT_PARENTHESIS;
		caseFound = true;
	}
	if (currentInputValue == "["){
		currentValueToken = VALUE_TOKEN_LEFT_BRACKET;
		caseFound = true;
	}
	if (currentInputValue == "]"){
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

