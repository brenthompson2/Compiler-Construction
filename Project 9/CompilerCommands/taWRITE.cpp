/*
  ==============================================================================

	File: taWRITE.cpp
	Author: Brendan Thompson
	Updated: 10/30/17

	Description: Implementation of Functions for processing aWRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "taWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

taWRITE::taWRITE(){
	return;
}

taWRITE::~taWRITE(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void taWRITE::prepareAWRITE(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns number of errors
int taWRITE::handleAWRITE(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	// cout << "\t\t[aWRITE]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	// numVariablesInArray = 0;
	globalNumErrors = 0;

	parseParameters();

	getMemoryLocation();

	if (globalNumErrors == 0){
		outputAWRITECommand();
		// cout << "\t\t[aWRITE]: Successfully compiled aWRITE command\n";
	}
	else {
		cout << "\t\t[aWRITE]: Failed to compile aWRITE command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseVariable() to get globalArrayName, and then parseIndex() twice to get the start & end indexes
void taWRITE::parseParameters(){
	bool continueParsingParameters;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_AWRITE_COMMAND;

	// Get Array Name
	continueParsingParameters = parseVariable(&currentCharIterator, ARRAY_CODE);

	// Parse START Index
	if (continueParsingParameters){
		if ((isdigit(globalCurrentLine[currentCharIterator])) || (globalCurrentLine[currentCharIterator] == '.') || (globalCurrentLine[currentCharIterator] == '-')){
			continueParsingParameters = parseConstant(&currentCharIterator, START_INDEX_CODE);
		}
		else {
			continueParsingParameters = parseVariable(&currentCharIterator, START_INDEX_CODE);
		}
	}
	else {
		cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting End Index: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	// Parse END Index
	if (continueParsingParameters){
		if ((isdigit(globalCurrentLine[currentCharIterator])) || (globalCurrentLine[currentCharIterator] == '.') || (globalCurrentLine[currentCharIterator] == '-')){
			continueParsingParameters = parseConstant(&currentCharIterator, END_INDEX_CODE);
		}
		else {
			continueParsingParameters = parseVariable(&currentCharIterator, END_INDEX_CODE);
		}
	}
	else {
		cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting End Index: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	// Check if Extra Parameters
	if (continueParsingParameters){
		cout << "\t\t\t[aWRITE]: Error: Not Expecting parameters after End index: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool taWRITE::parseVariable(int *currentCharIterator, int parameterNumber){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastParameter = false;
	bool isValidVariableName = true;
	bool caseFound;

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t\t[aWRITE]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[aWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[aWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[aWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Comma ,
		if (currentChar == ','){
			if (parameterNumber == END_INDEX_CODE){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Not Expecting Comma after EndIndex: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			else {
				if (numCharactersInVarName == 0){
					cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting an ID before , " << globalCurrentLine << endl;
					isValidVariableName = false;
					globalNumErrors++;
				}
			}
			continueParsingVariable = false;
			isNotLastParameter = true;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting an ID before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber == START_INDEX_CODE){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting EndIndex after StartIndex: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[aWRITE]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		switch (parameterNumber){
			case ARRAY_CODE:
				globalArrayObject.variableName = currentVariableName;
				break;
			case START_INDEX_CODE:
				globalStartIndex.variableName = currentVariableName;
				globalStartIndex.isConstant = false;
				break;
			case END_INDEX_CODE:
				globalEndIndex.variableName = currentVariableName;
				globalEndIndex.isConstant = false;
				break;
		}
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool taWRITE::parseConstant(int *currentCharIterator, int parameterNumber){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastParameter = false;
	bool isValidVariableName = true;
	bool readingDecimal = false;
	bool caseFound;

	// Handle Negatives
	currentChar = globalCurrentLine[(*currentCharIterator)];
	if (currentChar == '-'){
		currentVariableName += currentChar;
		numCharactersInVarName++;
		(*currentCharIterator)++;
		// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
	}

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t\t[aWRITE]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[aWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[aWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Decimal Point
		if (currentChar == '.'){
			if (readingDecimal){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Multiple Decimal Points in One Constant: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			else {
				readingDecimal = true;
				currentVariableName += currentChar;
				numCharactersInVarName++;
				(*currentCharIterator)++;
			}
			caseFound = true;
			// cout << "\t\t\t[aWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Comma ,
		if (currentChar == ','){
			if (parameterNumber == END_INDEX_CODE){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Not Expecting Comma after EndIndex: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			else {
				if (numCharactersInVarName == 0){
					cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting an ID before , " << globalCurrentLine << endl;
					isValidVariableName = false;
					globalNumErrors++;
				}
			}
			continueParsingVariable = false;
			isNotLastParameter = true;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting a Variable Name before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber == START_INDEX_CODE){
				cout << "\t\t\t[aWRITE]: Invalid Syntax: Expecting EndIndex after StartIndex: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[aWRITE]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		switch (parameterNumber){
			case ARRAY_CODE:
				globalArrayObject.variableName = currentVariableName;
				break;
			case START_INDEX_CODE:
				globalStartIndex.variableName = currentVariableName;
				globalStartIndex.isConstant = true;
				break;
			case END_INDEX_CODE:
				globalEndIndex.variableName = currentVariableName;
				globalEndIndex.isConstant = true;
				break;
		}
	}

	return isNotLastParameter;
}

// Ensures the globalArrayName already exists in the Symbol Table and gets the memory location
void taWRITE::getMemoryLocation(){
	if ((*currentMemoryManager).currentlyExists(globalArrayObject.variableName)){
		globalArrayObject.memoryLocation = (*currentMemoryManager).lookup(globalArrayObject.variableName);
	}
	else {
		cout << "\t\t\t[aWRITE]: Failed to get memory Location as " << globalArrayObject.variableName << " is undeclared: " << globalCurrentLine << endl;
		globalArrayObject.memoryLocation = -1;
		globalNumErrors++;
	}

	globalStartIndex.isArray = false;
	globalStartIndex.size = 1;
	globalEndIndex.isArray = false;
	globalEndIndex.size = 1;

	(*currentMemoryManager).manageMemoryTableObject(&globalStartIndex);
	(*currentMemoryManager).manageMemoryTableObject(&globalEndIndex);
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void taWRITE::outputAWRITECommand(){
	// cout << "\t\t[aWRITE]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(AWRITE_OP_CODE);
	(*currentFileManager).writeStringToObj(" ");
	(*currentFileManager).writeNumToObj((double) globalArrayObject.memoryLocation);
	(*currentFileManager).writeStringToObj(" ");
	(*currentFileManager).writeNumToObj((double) globalStartIndex.memoryLocation);
	(*currentFileManager).writeStringToObj(" ");
	(*currentFileManager).writeNumToObj((double) globalEndIndex.memoryLocation);

	(*currentFileManager).writeStringToObj("\n");
	// cout << "\t\t[aWRITE]: Wrote to .obj\n";
	return;
}

/* ==============================================================================
	Private Accessor Methods
============================================================================== */


