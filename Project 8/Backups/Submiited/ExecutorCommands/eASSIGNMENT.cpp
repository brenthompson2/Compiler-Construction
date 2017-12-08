/* ==============================================================================

	File: eASSIGNMENT.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing ASSIGNMENT command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eASSIGNMENT.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eASSIGNMENT::eASSIGNMENT(){
	return;
}

eASSIGNMENT::~eASSIGNMENT(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to SymbolTable with the parent's (compiler's) versions
void eASSIGNMENT::prepareASSIGNMENT(SymbolTable *parentMemoryManager){
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
int eASSIGNMENT::handleASSIGNMENT(string currentLine, int correspondingLineNumber){
	cout << "\t\t[ASSIGNMENT]: Compiling Line: " << currentLine << endl;

	globalNumErrors = 0;
	globalNumVariablesInArray = 0;
	string postfixExpression[MAX_NUM_INPUT_VALUES];
	int numInputValues;

	globalNumErrors += mainExpressionConverter.infixToPostfix(currentLine, postfixExpression, &numInputValues);
	// printPostfixExpression(postfixExpression, numInputValues);

	syncExpressionToVariableArray(postfixExpression, numInputValues);
	syncVariablesToSymbolTable();

	outputASSIGNMENTCommand(postfixExpression, numInputValues);

	if (globalNumErrors == 0){
		cout << "\t\t[ASSIGNMENT]: Successfully completed ASSIGNMENT command\n";
	}
	else {
		cout << "\t\t[ASSIGNMENT]: Failed to complete ASSIGNMENT command with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}


/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// Conditionally adds the postfix input values to the globalVariableArray
void eASSIGNMENT::syncExpressionToVariableArray(string newExpression[], int numValsInNewExpression){
	char firstChar;
	for (int i = 0; i <= numValsInNewExpression; i++){
		firstChar = (newExpression[i])[0];
		if ((isalpha(firstChar)) || (isdigit(firstChar))){
			globalVariableArray[globalNumVariablesInArray].variableName = newExpression[i];
			globalNumVariablesInArray++;
		}
	}
	return;
}

/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
void eASSIGNMENT::syncVariablesToSymbolTable(){
// 	// cout << "\t\t[ASSIGNMENT]: Attempting to Add Arguments to Lookup Table...\n";
	for (int i = 0; i < globalNumVariablesInArray; i++){
		globalVariableArray[i].isArray = false;
		globalVariableArray[i].size = 1;
		(*currentMemoryManager).manageMemoryTableObject(&globalVariableArray[i]);
	}
	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void eASSIGNMENT::outputASSIGNMENTCommand(string newExpression[], int numValsInNewExpression){
	// char firstChar;
	// int idCounter = 0;
	// int valueToOutput;

	// (*currentFileManager).writeStringToObj(ASSIGNMENT_OP_CODE);
	// (*currentFileManager).writeStringToObj(" ");

	// for (int i = 0; i <= numValsInNewExpression; i++){
	// 	firstChar = (newExpression[i])[0];
	// 	if ((isalpha(firstChar)) || (isdigit(firstChar))){
	// 		valueToOutput = (globalVariableArray[idCounter]).memoryLocation;
	// 		idCounter++;
	// 	}
	// 	else {
	// 		valueToOutput = getObjectCodeMapping(newExpression[i]);
	// 	}
	// 	(*currentFileManager).writeNumToObj((float) valueToOutput);
	// 	(*currentFileManager).writeStringToObj(" ");
	// }
	// (*currentFileManager).writeStringToObj("\n");
	return;
}

// Takes in an operator and returns the appropriate token for the obj file
int eASSIGNMENT::getObjectCodeMapping(string currentInputValue){
	int currentValueToken;
	bool caseFound = false;

	if (currentInputValue == "="){
		currentValueToken = OBJ_VALUE_EQUALS;
		caseFound = true;
	}
	if (currentInputValue == "["){
		currentValueToken = OBJ_VALUE_LEFT_BRACKET;
		caseFound = true;
	}
	if (currentInputValue == "^"){
		currentValueToken = OBJ_VALUE_EXPONENT;
		caseFound = true;
	}
	if (currentInputValue == "*"){
		currentValueToken = OBJ_VALUE_TIMES;
		caseFound = true;
	}
	if (currentInputValue == "/"){
		currentValueToken = OBJ_VALUE_DIVIDE;
		caseFound = true;
	}
	if (currentInputValue == "+"){
		currentValueToken = OBJ_VALUE_PLUS;
		caseFound = true;
	}
	if (currentInputValue == "-"){
		currentValueToken = OBJ_VALUE_MINUS;
		caseFound = true;
	}
	if (!caseFound) {
		cout << "\t\t[ASSIGNMENT]: Failed to map operator to obj code \"" << currentInputValue << "\". Unclosed Container?\n";
		currentValueToken = -1;
		globalNumErrors++;
	}

	return currentValueToken;
}

// Prints out the postfix array
void eASSIGNMENT::printPostfixExpression(string newExpression[], int numValsInNewExpression){
	cout << "\t\t[ASSIGNMENT]: Postfix:\t";
	for (int i = 0; i <= numValsInNewExpression; i++){
		cout << newExpression[i] << " ";
	}
	cout << endl;
}