/*
  ==============================================================================

	File: aREAD.cpp
	Author: Brendan Thompson
	Updated: 10/09/17

	Description: Implementation of Functions for processing aREAD command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "aREAD.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

aREAD::aREAD(){
	return;
}

aREAD::~aREAD(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void aREAD::prepareAREAD(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns number of errors
int aREAD::handleAREAD(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[aREAD]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	// numVariablesInArray = 0;
	globalNumErrors = 0;

	parseParameters();

	getMemoryLocation();

	if (globalNumErrors == 0){
		outputAREADCommand();
		cout << "\t\t[aREAD]: Successfully compiled aREAD command\n";
	}
	else {
		cout << "\t\t[aREAD]: Failed to compile aREAD command in line "<< correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseVariable() to get globalArrayName, and then parseIndex() twice to get the start & end indexes
void aREAD::parseParameters(){
	bool continueParsingParameters;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_AREAD_COMMAND;

	// Get Array Name
	continueParsingParameters = parseVariable(&currentCharIterator);

	// Get Start Index
	if (continueParsingParameters){
		continueParsingParameters = parseIndex(&currentCharIterator, true);
	}
	else {
		cout << "\t\t\t[aREAD]: Error: Expecting Start index: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	// Get End Index
	if (continueParsingParameters){
		continueParsingParameters = parseIndex(&currentCharIterator, false);
	}
	else {
		cout << "\t\t\t[aREAD]: Error: Expecting End index: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	// Check if Extra Parameters
	if (continueParsingParameters){
		cout << "\t\t\t[aREAD]: Error: Not Expecting parameters after End index: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, adds complete currentVariableName to globalArrayName, and returns whether or not there are any more parameters to parse
bool aREAD::parseVariable(int *currentCharIterator){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastParameter = false;
	bool isValidVariableName = true;

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		// cout << "\t\t[aREAD]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			// cout << "\t\t[aREAD]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aREAD]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			// cout << "\t\t\t[DIM]: Current Variable Name: " << currentVariableName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aREAD]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aREAD]: Invalid Syntax: Expecting at least one character before ,: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			isNotLastParameter = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aREAD]: Invalid Syntax: Expecting at least one character in variable name: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidVariableName = false;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
		}
	}

	if (isValidVariableName){
		globalArrayName = currentVariableName;
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, conditionally adds complete currentIndexString to globalStartIndex or globalEndIndex, and returns whether or not there are any more parameters to parse
bool aREAD::parseIndex(int *currentCharIterator, bool gettingStartIndex){
	char currentChar;
	string currentIndexString = "";
	int numCharactersInIndex = 0;

	bool continueParsingIndex = true;
	bool isNotLastParameter = false;
	bool isValidIndex = false;

	while (continueParsingIndex){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		// cout << "\t\t[aREAD]: Current Character: " << currentChar << endl;

		// Alphabetic
		// if (isalpha(currentChar)){
		// 	currentVariableName += currentChar;
		// 	numCharactersInIndex++;
		// 	(*currentCharIterator)++;
		// 	// cout << "\t\t[tREAD]: Current Variable Name: " << currentVariableName << endl;
		// }

		// Digit
		if (isdigit(currentChar)){
			isValidIndex = true;
			currentIndexString += currentChar;
			numCharactersInIndex++;
			(*currentCharIterator)++;
		}

		// Underscore
		// if (currentChar == '_'){
		// 	if (numCharactersInIndex == 0){
		// 		cout << "\t\t[aREAD]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
		// 		isValidIndex = false;
		// 		globalNumErrors++;
		// 	}
		// 	currentIndexString += currentChar;
		// 	numCharactersInIndex++;
		// 	(*currentCharIterator)++;
		// }

		// Comma
		if (currentChar == ','){
			if (numCharactersInIndex == 0){
				cout << "\t\t\t[aREAD]: Invalid Syntax: Expecting a start index before ,: " << globalCurrentLine << endl;
				isValidIndex = false;
				globalNumErrors++;
			}
			continueParsingIndex = false;
			(*currentCharIterator)++;
			isNotLastParameter = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInIndex == 0){
				cout << "\t\t\t[aREAD]: Invalid Syntax: Expecting at least one digit in index: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			continueParsingIndex = false;
			isNotLastParameter = false;
		}
	}

	if (isValidIndex){
		if (gettingStartIndex){
			globalStartIndex = currentIndexString;
		}
		else {
			globalEndIndex = currentIndexString;
		}
	}

	return isNotLastParameter;
}

// Ensures the globalArrayName already exists in the Symbol Table and gets the memory location
void aREAD::getMemoryLocation(){
	if ((*currentMemoryManager).currentlyExists(globalArrayName)){
		currentArrayObject.memoryLocation = (*currentMemoryManager).lookup(currentArrayObject.variableName);
	}
	else {
		cout << "\t\t\t[aREAD]: Failed to get memory Location as " << globalArrayName << " is undeclared: " << globalCurrentLine << endl;
		currentArrayObject.memoryLocation = -1;
		globalNumErrors++;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void aREAD::outputAREADCommand(){
	// cout << "\t\t[aREAD]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(AREAD_OP_CODE);
	(*currentFileManager).writeCharToObj(' ');
	(*currentFileManager).writeNumToObj(currentArrayObject.memoryLocation);
	(*currentFileManager).writeCharToObj(' ');
	(*currentFileManager).writeStringToObj(globalStartIndex);
	(*currentFileManager).writeCharToObj(' ');
	(*currentFileManager).writeStringToObj(globalEndIndex);

	(*currentFileManager).writeCharToObj('\n');
	// cout << "\t\t[aREAD]: Wrote to .obj\n";
	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */

