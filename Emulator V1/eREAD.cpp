/* ==============================================================================

	File: eREAD.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing READ command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eREAD.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eREAD::eREAD(){
	return;
}

eREAD::~eREAD(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to ParentMemoryManager
void eREAD::prepareREAD(SymbolTable *currentMemoryManager){
	ParentMemoryManager = currentMemoryManager;
}

// calls the functions necessary to parse and execute the read command
void eREAD::handleREAD(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[READ]: Executing Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumVariablesInArray = 0;
	globalNumErrors = 0;

	parseParameters();

	// printVariableArray();
	syncVariableArrayToSymbolTable();
	executeREADCommand();

	if (globalNumErrors == 0){
		cout << "\t\t[READ]: Successfully completed READ command\n";
	}
	else {
		cout << "\t\t[READ]: Failed to complete READ command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseVariable until no more variable to parse
void eREAD::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_READ_COMMAND;
	char currentChar;

	while (continueParsingParameters){
		currentChar = globalCurrentLine[currentCharIterator];

		// continueParsingParameters = parseObjectCode(&currentCharIterator);
	}

	return;
}

// adds the currentVariableName to the variableArray and increments globalNumVariablesInArray
void eREAD::addToVariableArray(string currentVariableName){
	if (globalNumVariablesInArray == (MAX_ARGUMENTS - 1)){
		cout << "\t\t\t[eREAD]: Invalid Syntax: Number of Arguments in READ Command Exceeds " << MAX_ARGUMENTS << ": " << globalCurrentLine << endl;
		globalNumErrors++;
		return;
	}

	// variableArray[globalNumVariablesInArray].variableName = currentVariableName;
	globalNumVariablesInArray++;
	// cout << "\t\t[eREAD]: Added Variable to Array: " << currentVariableName << endl;
	return;
}

// iterates through the variableArray and tells the memoryManager to conditionally add them to the symbol table
void eREAD::syncVariableArrayToSymbolTable(){
	// cout << "\t\t[eREAD]: Attempting to Add Variable Array to Lookup Table...\n";

	// for (int i = 0; i < globalNumVariablesInArray; i++){
	// 	(*currentMemoryManager).manageMemoryTableObject(&variableArray[i]);
	// }

	// // (*currentMemoryManager).printSymbolTable();
	// return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void eREAD::executeREADCommand(){
	// unsigned int currentMemoryLocation;
	// // cout << "\t\t[eREAD]: Attempting to Print Object code to .obj...\n";

	// (*currentFileManager).writeStringToObj(READ_OP_CODE);

	// for (int i = 0; i < globalNumVariablesInArray; i++){
	// 	(*currentFileManager).writeStringToObj(" ");
	// 	currentMemoryLocation = (variableArray[i]).memoryLocation;
	// 	(*currentFileManager).writeNumToObj((float) currentMemoryLocation);
	// }

	// (*currentFileManager).writeStringToObj("\n");
	// return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// prints the variableArray to the console
void eREAD::printVariableArray(){
	// string currentVariableName;
	// unsigned int currentMemoryLocation;

	// cout << "\t\t[eREAD]: Variable Array: " << currentVariableName << endl;

	// for (int i = 0; i < globalNumVariablesInArray; i++){
	// 	currentVariableName = (variableArray[i]).variableName;
	// 	currentMemoryLocation = (variableArray[i]).memoryLocation;
	// 	cout << "\t\t\t" << currentVariableName << ": " << currentMemoryLocation << endl;
	// }
	// return;
}


