/* ==============================================================================

	File: eWRITE.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing WRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eWRITE::eWRITE(){
	return;
}

eWRITE::~eWRITE(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the compiler's (parent's) versions
void eWRITE::prepareWRITE(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}

// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns number of errors
int eWRITE::handleWRITE(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[eWRITE]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	numVariablesInArray = 0;
	globalNumErrors = 0;

	parseParameters();

	// printVariableArray();
	syncVariableArrayToSymbolTable();

	if (globalNumErrors == 0){
		outputWRITECommand();
		cout << "\t\t[eWRITE]: Successfully completed eWRITE command\n";
	}
	else {
		cout << "\t\t[eWRITE]: Failed to complete eWRITE command in line "<< correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseVariable until no more variable to parse
void eWRITE::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_WRITE_COMMAND;

	while (continueParsingParameters){
		continueParsingParameters = parseVariable(&currentCharIterator);
	}

	return;
}

// parses through a line one character at a time, adds complete variables to VariableArray, and returns whether or not there are any more variables to parse
bool eWRITE::parseVariable(int *currentCharIterator){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastVariable = true;
	bool isValidVariableName = true;
	bool caseFound;

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		// cout << "\t\t[eWRITE]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[eWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[eWRITE]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[eWRITE]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[eWRITE]: Invalid Syntax: Expecting at least one character before ,: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			isNotLastVariable = true;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				if (numVariablesInArray == 0){
					cout << "\t\t\t[eWRITE]: Invalid Syntax: Expecting at least variable before end of line: " << globalCurrentLine << endl;
					globalNumErrors++;
				}
				else {
					cout << "\t\t\t[eWRITE]: Invalid Syntax: Expecting at least one character in variable name before end of line: " << globalCurrentLine << endl;
					globalNumErrors++;
				}
				isValidVariableName = false;
			}
			continueParsingVariable = false;
			isNotLastVariable = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[GOTO]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	if (isValidVariableName){
		addToVariableArray(currentVariableName);
		// printVariableArray();
	}

	return isNotLastVariable;
}

// adds the currentVariableName to the variableArray and increments numVariablesInArray
void eWRITE::addToVariableArray(string currentVariableName){
	if (numVariablesInArray == (MAX_ARGUMENTS - 1)){
		cout << "\t\t\t[eWRITE]: Invalid Syntax: Number of Arguments in WRITE Command Exceeds " << MAX_ARGUMENTS << ": " << globalCurrentLine << endl;
		return;
	}

	variableArray[numVariablesInArray].variableName = currentVariableName;
	variableArray[numVariablesInArray].isArray = false;
	variableArray[numVariablesInArray].size = 1;
	numVariablesInArray++;
	// cout << "\t\t[eWRITE]: Added Variable to Array: " << currentVariableName << endl;
	return;
}

// iterates through the variableArray and asks the memoryManager to conditionally add them to the symbol table
void eWRITE::syncVariableArrayToSymbolTable(){
	string currentVariableName;
	// cout << "\t\t[eWRITE]: Attempting to Add Variable Array to Lookup Table...\n";

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentMemoryManager).manageMemoryTableObject(&variableArray[i]);
	}

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void eWRITE::outputWRITECommand(){
	unsigned int currentMemoryLocation;
	// cout << "\t\t[eWRITE]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(WRITE_OP_CODE);

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentFileManager).writeStringToObj(" ");
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		(*currentFileManager).writeNumToObj((float) currentMemoryLocation);
	}

	(*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// prints the variableArray to the console
void eWRITE::printVariableArray(){
	string currentVariableName;
	unsigned int currentMemoryLocation;

	cout << "\t\t[eWRITE]: Variable Array: " << currentVariableName << endl;

	for (int i = 0; i < numVariablesInArray; i++){
		currentVariableName = (variableArray[i]).variableName;
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		cout << "\t\t\t" << currentVariableName << ": " << currentMemoryLocation << endl;
	}
	return;
}

