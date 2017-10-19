/*
  ==============================================================================

	File: tWRITE.cpp
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Implementation of Functions for processing WRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tWRITE::tWRITE(){
	return;
}

tWRITE::~tWRITE(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the compiler's (parent's) versions
void tWRITE::prepareWRITE(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}

// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
bool tWRITE::newWRITE(string currentLine, int *numErrors){
	globalCurrentLine = currentLine;
	cout << "\t\t[tWRITE]: Compiling Line: " << globalCurrentLine << endl;

	numVariablesInArray = 0;
	globalNumErrors = 0;
	validSyntax = true;

	parseVariables();

	// printVariableArray();
	syncVariableArrayToSymbolTable();
	outputWRITECommand();

	if (!validSyntax){
		cout << "\t\t[tWRITE]: Successfully completed WRITE command with " << globalNumErrors << " errors\n";
	}

	// cout << "\t\t[tWRITE]: Valid Syntax: " << validSyntax << endl;
	*numErrors += globalNumErrors;
	return validSyntax;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iterates through the variables passed to the command one character at a time and inserts them into variableArray
void tWRITE::parseVariables(){
	bool continueParsingParameters = true;
	bool continueParsingVariable = true;
	unsigned int currentLineIterator = 5;
	unsigned int numCharactersInVarName;

	while (continueParsingParameters){
		string currentVariableName = "";
		numCharactersInVarName = 0;
		continueParsingVariable = true;
		// cout << "\t\t[tWRITE]: Set Current Variable Name to: " << currentVariableName << endl;

		char currentChar = globalCurrentLine[currentLineIterator];
		// cout << "\t\t[tWRITE]: Current Character: " << currentChar << endl;

		while (continueParsingVariable){
			if (numVariablesInArray > 0){
				// cout << "\t\t[tWRITE]: numVariablesInArray: " << numVariablesInArray << endl;
				// cout << "\t\t[tWRITE]: Continue: " << continueParsingVariable << endl;
				// printVariableArray();
			}

			currentChar = globalCurrentLine[currentLineIterator];
			// cout << "\t\t[tWRITE]: Current Character: " << currentChar << endl;

			globalNumErrors = analyzeCharacter(currentChar, currentVariableName, numCharactersInVarName, &currentLineIterator, &continueParsingParameters, &continueParsingVariable);

			currentVariableName += currentChar;
			// cout << "\t\t[tWRITE]: Current Variable Name: " << currentVariableName << endl;
			currentLineIterator++;
			numCharactersInVarName++;
		}
	}

	return;
}

// analyzeCharacter = returns the number of errors in the line
	// changes the index to the currentChar
	// calls addToVariableArray(string currentVariableName)
	// manipulates the status of parsing given pointers to status information
unsigned int tWRITE::analyzeCharacter(char currentChar,
									string currentVariableName,
									unsigned int numCharactersInVarName, unsigned int *currentLineIterator,
									bool *continueParsingParameters, bool *continueParsingVariable){
	unsigned int numErrors = 0;

	if(currentChar == '\0'){
		if (numCharactersInVarName == 0){
			// cout << "\t\t[tWRITE]: currentChar: " << currentChar << "numCharactersInVarName: " << numCharactersInVarName << endl;
			if (numVariablesInArray == 0){ // empty variable name and no variables in array
				cout << "\t\t[tWRITE]: Invalid Syntax: WRITE Command requires at least one variable before end of line: " << globalCurrentLine << endl;
				validSyntax = false;
				numErrors++;
			}
			else { // empty variable name but at least one variable in array
				cout << "\t\t[tWRITE]: Invalid Syntax: Expecting another variable name before end of line: " << globalCurrentLine << endl;
				validSyntax = false;
				numErrors++;
			}
		}
		else { // end of variable name
			// cout << "\t\t[tWRITE]: Found variable name: " << currentVariableName << endl;
			// cout << "\t\t[tWRITE]: Reached end of line\n";
			addToVariableArray(currentVariableName);
			// printVariableArray();
		}
		*continueParsingParameters = false;
		*continueParsingVariable = false;
	}

	if(currentChar == ','){
		if (numCharactersInVarName == 0){
			// cout << "\t\t[tWRITE]: currentChar: " << currentChar << "numCharactersInVarName: " << numCharactersInVarName << endl;
			if (numVariablesInArray == 0){ // empty variable name and no variables in array
				cout << "\t\t[tWRITE]: Invalid Syntax: WRITE Command requires at least one variable before ,: " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				numErrors++;
			}
			else { // empty variable name but at least one variable in array
				cout << "\t\t[tWRITE]: Invalid Syntax: Expecting another variable name before ,: " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				numErrors++;
			}
		}
		else { // end of variable name
			// cout << "\t\t[tWRITE]: Found variable name: " << currentVariableName << endl;
			addToVariableArray(currentVariableName);
			// printVariableArray();
		}
		*continueParsingVariable = false;
	}

	return numErrors;
}

// adds the currentVariableName to the variableArray and increments numVariablesInArray
void tWRITE::addToVariableArray(string currentVariableName){
	if (numVariablesInArray == (MAX_ARGUMENTS - 1)){
		cout << "\t\t[tWRITE]: Invalid Syntax: Number of Arguments in WRITE Command Exceeds " << MAX_ARGUMENTS << ": " << globalCurrentLine << endl;
		return;
	}

	variableArray[numVariablesInArray].variableName = currentVariableName;
	variableArray[numVariablesInArray].isArray = false;
	variableArray[numVariablesInArray].size = 1;
	numVariablesInArray++;
	// cout << "\t\t[tWRITE]: Added Variable to Array: " << currentVariableName << endl;
	return;
}

// iterates through the variableArray and asks the memoryManager to conditionally add them to the symbol table
void tWRITE::syncVariableArrayToSymbolTable(){
	string currentVariableName;
	// cout << "\t\t[tWRITE]: Attempting to Add Variable Array to Lookup Table...\n";

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentMemoryManager).manageMemoryTableObject(&variableArray[i]);
	}

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tWRITE::outputWRITECommand(){
	unsigned int currentMemoryLocation;
	// cout << "\t\t[tWRITE]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeCharToObj(WRITE_OP_CODE);

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
void tWRITE::printVariableArray(){
	string currentVariableName;
	unsigned int currentMemoryLocation;

	cout << "\t\t[tWRITE]: Variable Array: " << currentVariableName << endl;

	for (int i = 0; i < numVariablesInArray; i++){
		currentVariableName = (variableArray[i]).variableName;
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		cout << "\t\t\t" << currentVariableName << ": " << currentMemoryLocation << endl;
	}
	return;
}


