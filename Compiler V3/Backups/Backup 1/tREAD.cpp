/*
  ==============================================================================

	File: tREAD.cpp
	Author: Brendan Thompson
	Updated: 10/09/17

	Description: Implementation of Functions for processing READ command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tREAD.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tREAD::tREAD(){
	return;
}

tREAD::~tREAD(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tREAD::prepareREAD(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}

// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns number of errors
int tREAD::handleREAD(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[tREAD]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	numVariablesInArray = 0;
	globalNumErrors = 0;

	parseParameters();

	// printVariableArray();
	syncVariableArrayToSymbolTable();

	if (globalNumErrors == 0){
		outputREADCommand();
		cout << "\t\t[tREAD]: Successfully completed tREAD command\n";
	}
	else {
		cout << "\t\t[tREAD]: Failed to complete tREAD command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseVariable until no more variable to parse
void tREAD::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_READ_COMMAND;

	while (continueParsingParameters){
		continueParsingParameters = parseVariable(&currentCharIterator);
	}

	return;
}

// parses through a line one character at a time, adds complete variables to VariableArray, and returns whether or not there are any more variables to parse
bool tREAD::parseVariable(int *currentCharIterator){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastVariable = true;
	bool isValidVariableName = true;

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		// cout << "\t\t[tREAD]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			// cout << "\t\t[tREAD]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[tREAD]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[tREAD]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[tREAD]: Invalid Syntax: Expecting at least one character before ,: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			isNotLastVariable = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				if (numVariablesInArray == 0){
					cout << "\t\t\t[tREAD]: Invalid Syntax: Expecting at least variable before end of line: " << globalCurrentLine << endl;
					globalNumErrors++;
				}
				else {
					cout << "\t\t\t[tREAD]: Invalid Syntax: Expecting at least one character in variable name before end of line: " << globalCurrentLine << endl;
					globalNumErrors++;
				}
				isValidVariableName = false;
			}
			continueParsingVariable = false;
			isNotLastVariable = false;
		}
	}

	if (isValidVariableName){
		addToVariableArray(currentVariableName);
		// printVariableArray();
	}

	return isNotLastVariable;
}

// adds the currentVariableName to the variableArray and increments numVariablesInArray
void tREAD::addToVariableArray(string currentVariableName){
	if (numVariablesInArray == (MAX_ARGUMENTS - 1)){
		cout << "\t\t\t[tREAD]: Invalid Syntax: Number of Arguments in READ Command Exceeds " << MAX_ARGUMENTS << ": " << globalCurrentLine << endl;
		globalNumErrors++;
		return;
	}

	variableArray[numVariablesInArray].variableName = currentVariableName;
	variableArray[numVariablesInArray].isArray = false;
	variableArray[numVariablesInArray].size = 1;
	numVariablesInArray++;
	// cout << "\t\t[tREAD]: Added Variable to Array: " << currentVariableName << endl;
	return;
}

// iterates through the variableArray and tells the memoryManager to conditionally add them to the symbol table
void tREAD::syncVariableArrayToSymbolTable(){
	// cout << "\t\t[tREAD]: Attempting to Add Variable Array to Lookup Table...\n";

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentMemoryManager).manageMemoryTableObject(&variableArray[i]);
	}

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tREAD::outputREADCommand(){
	unsigned int currentMemoryLocation;
	// cout << "\t\t[tREAD]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeCharToObj(READ_OP_CODE);

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentFileManager).writeCharToObj(' ');
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		(*currentFileManager).writeNumToObj(currentMemoryLocation);
	}

	(*currentFileManager).writeCharToObj('\n');
	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// prints the variableArray to the console
void tREAD::printVariableArray(){
	string currentVariableName;
	unsigned int currentMemoryLocation;

	cout << "\t\t[tREAD]: Variable Array: " << currentVariableName << endl;

	for (int i = 0; i < numVariablesInArray; i++){
		currentVariableName = (variableArray[i]).variableName;
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		cout << "\t\t\t" << currentVariableName << ": " << currentMemoryLocation << endl;
	}
	return;
}


