/*
  ==============================================================================

	File: aWRITE.cpp
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Implementation of Functions for processing aWRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "aWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

aWRITE::aWRITE(){
	return;
}

aWRITE::~aWRITE(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void aWRITE::prepareAWRITE(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
bool aWRITE::newAWRITE(string currentLine, int *MainNumErrors){
	globalCurrentLine = currentLine;
	cout << "\t\t[aWRITE]: Compiling Line: " << globalCurrentLine << endl;

	// numVariablesInArray = 0;
	globalNumErrors = 0;
	validSyntax = true;

	parseParameters();

	getMemoryLocation();
	outputAWRITECommand();

	if (!validSyntax){
		cout << "\t\t[aWRITE]: Successfully completed aWRITE command with " << globalNumErrors << " errors\n";
	}

	*MainNumErrors += globalNumErrors;
	return validSyntax;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iterates through the variables passed to the command one character at a time and inserts them into variableArray
void aWRITE::parseParameters(){
	// bool continueParsingParameters = true;
	bool continueParsingVariable = true;
	unsigned int currentLineIterator = 6;
	unsigned int numCharactersInVarName;
	char currentChar;

	// PARSE Variable Name
	string currentVariableName = "";
	numCharactersInVarName = 0;
	continueParsingVariable = true;
	while (continueParsingVariable){
		currentChar = globalCurrentLine[currentLineIterator];
		// cout << "\t\t[aWRITE]: Current Character: " << currentChar << endl;

		analyzeCharInVarName(currentChar, currentVariableName, numCharactersInVarName, &continueParsingVariable);

		if (continueParsingVariable){
			currentVariableName += currentChar;
		}

		// cout << "\t\t[aWRITE]: Current Variable Name: " << currentVariableName << endl;
		currentLineIterator++;
		numCharactersInVarName++;
	}
	globalVariableName = currentVariableName;
	if (!((*currentMemoryManager).currentlyExists(currentVariableName))){
		cout << "\t\t[aWRITE]: Using undeclared array " << globalVariableName << " in line: " << globalCurrentLine << endl;
		globalNumErrors++;
		validSyntax = false;
	}
	// cout << "\t\t[aWRITE]: Got Variable Name: " << globalVariableName << endl;

	// PARSE START INDEX
	currentVariableName = "";
	numCharactersInVarName = 0;
	continueParsingVariable = true;
	while (continueParsingVariable){
		currentChar = globalCurrentLine[currentLineIterator];
		// cout << "\t\t[aWRITE]: Current Character: " << currentChar << endl;

		analyzeCharInIndex(currentChar, currentVariableName, numCharactersInVarName, &continueParsingVariable, false);

		if (continueParsingVariable){
			currentVariableName += currentChar;
		}
		currentLineIterator++;
		numCharactersInVarName++;
	}
	globalStartIndex = currentVariableName;
	// cout << "\t\t[aWRITE]: Got Start Index: " << globalStartIndex << endl;

	// PARSE END INDEX
	currentVariableName = "";
	numCharactersInVarName = 0;
	continueParsingVariable = true;
	while (continueParsingVariable){
		currentChar = globalCurrentLine[currentLineIterator];
		// cout << "\t\t[aWRITE]: Current Character: " << currentChar << endl;

		analyzeCharInIndex(currentChar, currentVariableName, numCharactersInVarName, &continueParsingVariable, true);

		if (continueParsingVariable){
			currentVariableName += currentChar;
		}
		currentLineIterator++;
		numCharactersInVarName++;
	}
	globalEndIndex = currentVariableName;
	// cout << "\t\t[aWRITE]: Got End Index: " << globalEndIndex << endl;

	return;
}

// analyzeCharInVarName =
	// manipulates globalNumErrors
	// changes the index to the currentChar
	// calls addToVariableArray(string currentVariableName)
	// manipulates the status of parsing given pointers to status information
void aWRITE::analyzeCharInVarName(	char currentChar,
									string currentVariableName,
									unsigned int numCharactersInVarName,
									bool *continueParsingVariable){
	if(currentChar == '\0'){
		cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE Command requires a variable, startIndex, and endIndex before end of line: " << globalCurrentLine << endl;
		validSyntax = false;
		globalNumErrors++;
		*continueParsingVariable = false;
	}

	if(currentChar == ','){
		if (numCharactersInVarName == 0){
			cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE Command requires at least one variable before , : " << globalCurrentLine << endl;
			validSyntax = false;
			globalNumErrors++;
		}
		else { // end of variable name
			// cout << "\t\t[aWRITE]: Found variable name: " << currentVariableName << endl;
		}
		*continueParsingVariable = false;
	}

	return;
}

// analyzeCharInIndex =
	// manipulates globalNumErrors
	// changes the index to the currentChar
	// calls addToVariableArray(string currentVariableName)
	// manipulates the status of parsing given pointers to status information
void aWRITE::analyzeCharInIndex(	char currentChar,
								string currentVariableName,
								unsigned int numCharactersInVarName,
								bool *continueParsingVariable,
								bool isEndIndex){
	if(currentChar == '\0'){
		if (numCharactersInVarName == 0){ // no value entered
			if (isEndIndex){
				cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE Command expects end index after start index: " << globalCurrentLine << endl;
			}
			else {
				cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE Command expects start index after variable name: " << globalCurrentLine << endl;
			}
			validSyntax = false;
			globalNumErrors++;
		}
		else { // endline after input
			if (isEndIndex){
				// end of line
			}
			else {
				cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE Command expects end index after start index: " << globalCurrentLine << endl;
				validSyntax = false;
				globalNumErrors++;
			}
		}
		*continueParsingVariable = false;
	}

	if(currentChar == ','){
		if (numCharactersInVarName == 0){ // no value entered
			if (isEndIndex){
				cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE command didn't expect , after end index : " << globalCurrentLine << endl;
			}
			else {
				cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE Command expects start index before , : " << globalCurrentLine << endl;
			}
			validSyntax = false;
			globalNumErrors++;
		}
		else { // comma after input
			if (isEndIndex){
				cout << "\t\t[aWRITE]: Invalid Syntax: aWRITE command didn't expect , after end index : " << globalCurrentLine << endl;
				validSyntax = false;
				globalNumErrors++;
			}
			else {
				// end of start index
			}
		}
		*continueParsingVariable = false;
	}

	return;
}

// iterates through the variableArray and tells the memoryManager to conditionally add them to the symbol table
void aWRITE::getMemoryLocation(){
	if ((*currentMemoryManager).currentlyExists(globalVariableName)){
		currentMemoryTableObject.memoryLocation = (*currentMemoryManager).lookup(currentMemoryTableObject.variableName);
	}
	else {
		cout << "\t\t\t[aREAD]: Failed to get memory Location as " << globalVariableName << " is undeclared: " << globalCurrentLine << endl;
		currentMemoryTableObject.memoryLocation = -1;
	}
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void aWRITE::outputAWRITECommand(){
	// cout << "\t\t[aWRITE]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(AWRITE_OP_CODE);
	(*currentFileManager).writeCharToObj(' ');
	(*currentFileManager).writeNumToObj(currentMemoryTableObject.memoryLocation);
	(*currentFileManager).writeCharToObj(' ');
	(*currentFileManager).writeStringToObj(globalStartIndex);
	(*currentFileManager).writeCharToObj(' ');
	(*currentFileManager).writeStringToObj(globalEndIndex);

	(*currentFileManager).writeCharToObj('\n');
	// cout << "\t\t[aWRITE]: Wrote to .obj\n";
	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */


