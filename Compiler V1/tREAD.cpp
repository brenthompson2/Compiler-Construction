/*
  ==============================================================================

	File: tREAD.cpp
	Author: Brendan Thompson
	Updated: 09/26/17

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

void tREAD::shutdown(){
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
bool tREAD::newREAD(string currentLine, int *numErrors){
	globalCurrentLine = currentLine;
	cout << "\t\t[tREAD]: Compiling Line: " << globalCurrentLine << endl;

	numVariablesInArray = 0;
	globalNumErrors = 0;
	validSyntax = true;

	parseVariables();

	// printVariableArray();
	syncVariableArrayToSymbolTable();
	outputReadCommand();

	if (!validSyntax){
		cout << "\t\t[tREAD]: Successfully completed read command with " << globalNumErrors << " errors\n";
	}

	*numErrors += globalNumErrors;
	return validSyntax;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iterates through the variables passed to the command one character at a time and inserts them into variableArray
void tREAD::parseVariables(){
	bool continueParsingParameters = true;
	bool continueParsingVariable = true;
	unsigned int currentLineIterator = 4;
	unsigned int numCharactersInVarName;

	while (continueParsingParameters){
		string currentVariableName = "";
		numCharactersInVarName = 0;
		continueParsingVariable = true;
		// cout << "\t\t[tREAD]: Set Current Variable Name to: " << currentVariableName << endl;

		char currentChar = globalCurrentLine[currentLineIterator];
		// cout << "\t\t[tREAD]: Current Character: " << currentChar << endl;

		while (continueParsingVariable){
			if (numVariablesInArray > 0){
				// cout << "\t\t[tREAD]: numVariablesInArray: " << numVariablesInArray << endl;
				// cout << "\t\t[tREAD]: Continue: " << continueParsingVariable << endl;
				// printVariableArray();
			}

			currentChar = globalCurrentLine[currentLineIterator];
			// cout << "\t\t[tREAD]: Current Character: " << currentChar << endl;

			globalNumErrors = analyzeCharacter(currentChar, currentVariableName, numCharactersInVarName, &currentLineIterator, &continueParsingParameters, &continueParsingVariable);

			currentVariableName += currentChar;
			// cout << "\t\t[tREAD]: Current Variable Name: " << currentVariableName << endl;
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
unsigned int tREAD::analyzeCharacter(char currentChar,
									string currentVariableName,
									unsigned int numCharactersInVarName, unsigned int *currentLineIterator,
									bool *continueParsingParameters, bool *continueParsingVariable){
	unsigned int numErrors = 0;

	if(currentChar == '\0'){
		if (numCharactersInVarName == 0){
			// cout << "\t\t[tREAD]: currentChar: " << currentChar << "numCharactersInVarName: " << numCharactersInVarName << endl;
			if (numVariablesInArray == 0){ // empty variable name and no variables in array
				cout << "\t\t[tREAD]: Invalid Syntax: READ Command requires at least one variable before end of line: " << globalCurrentLine << endl;
				validSyntax = false;
				numErrors++;
			}
			else { // empty variable name but at least one variable in array
				cout << "\t\t[tREAD]: Invalid Syntax: Expecting another variable name before end of line: " << globalCurrentLine << endl;
				validSyntax = false;
				numErrors++;
			}
		}
		else { // end of variable name
			// cout << "\t\t[tREAD]: Found variable name: " << currentVariableName << endl;
			// cout << "\t\t[tREAD]: Reached end of line\n";
			addToVariableArray(currentVariableName);
			// printVariableArray();
		}
		*continueParsingParameters = false;
		*continueParsingVariable = false;
	}

	if(currentChar == ','){
		if (numCharactersInVarName == 0){
			// cout << "\t\t[tREAD]: currentChar: " << currentChar << "numCharactersInVarName: " << numCharactersInVarName << endl;
			if (numVariablesInArray == 0){ // empty variable name and no variables in array
				cout << "\t\t[tREAD]: Invalid Syntax: READ Command requires at least one variable before ,: " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				numErrors++;
			}
			else { // empty variable name but at least one variable in array
				cout << "\t\t[tREAD]: Invalid Syntax: Expecting another variable name before ,: " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				numErrors++;
			}
		}
		else { // end of variable name
			// cout << "\t\t[tREAD]: Found variable name: " << currentVariableName << endl;
			addToVariableArray(currentVariableName);
			// printVariableArray();
			*currentLineIterator++;
		}
		*continueParsingVariable = false;
	}

	return numErrors;
}

// adds the currentVariableName to the variableArray and increments numVariablesInArray
void tREAD::addToVariableArray(string currentVariableName){
	if (numVariablesInArray == (MAX_ARGUMENTS - 1)){
		cout << "\t\t[tREAD]: Invalid Syntax: Number of Arguments in READ Command Exceeds " << MAX_ARGUMENTS << ": " << globalCurrentLine << endl;
		return;
	}

	variableArray[numVariablesInArray].variableName = currentVariableName;
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
void tREAD::outputReadCommand(){
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


