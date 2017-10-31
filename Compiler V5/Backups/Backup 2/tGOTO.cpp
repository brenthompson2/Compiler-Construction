/*
  ==============================================================================

	File: tGOTO.cpp
	Author: Brendan Thompson
	Updated: 10/12/17

	Description: Implementation of Functions for processing GOTO command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tGOTO.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tGOTO::tGOTO(){
	return;
}

tGOTO::~tGOTO(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tGOTO::prepareGOTO(FileManager *parentFileManager, LineLabelTable *parentLineManager){
	currentFileManager = parentFileManager;
	currentLineManager = parentLineManager;
}

// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns number of errors
int tGOTO::handleGOTO(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[GOTO]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	// Get Line Label
	parseParameters();

	// Get Line Number
	globalLineLabelLineNumber = (*currentLineManager).getObjLineNumber(globalLineLabelName);

	if (globalLineLabelLineNumber == NOT_FOUND_IN_ARRAY){
		cout << "\t\t\t[GOTO]: Error: Line Label not found in Line Label Table: " << globalLineLabelName << endl;
		globalNumErrors++;
	}

	if (globalNumErrors == 0){
		outputGOTOCommand();
		cout << "\t\t[GOTO]: Successfully completed GOTO command\n";
	}
	else {
		cout << "\t\t[GOTO]: Error: Failed to complete GOTO command in line " << correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseLineLabelName until no more variable to parse
void tGOTO::parseParameters(){
	bool continueParsingParameters;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_GOTO_COMMAND;

	// Get Line Label Name
	continueParsingParameters = parseLineLabelName(&currentCharIterator);

	// Check if Extra Parameters
	if (continueParsingParameters){
		cout << "\t\t\t[aREAD]: Error: Not Expecting parameters after Line Label: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, sets globalLineLabelName, and returns whether or not there are any more variables to parse
bool tGOTO::parseLineLabelName(int *currentCharIterator){
	char currentChar;
	string currentLineLabelName = "";
	int numCharactersInLabelName = 0;

	bool continueParsingLabel = true;
	bool isNotLastParameter = true;
	bool isValidLineLabel = true;
	bool caseFound;

	while (continueParsingLabel){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t[GOTO]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[GOTO]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[GOTO]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[GOTO]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInLabelName == 0){
				cout << "\t\t\t[GOTO]: Invalid Syntax: Expecting at least one character before ,: " << globalCurrentLine << endl;
				isValidLineLabel = false;
				globalNumErrors++;
			}
			continueParsingLabel = false;
			(*currentCharIterator)++;
			isNotLastParameter = true;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInLabelName == 0){
				cout << "\t\t\t[GOTO]: Invalid Syntax: Expecting line label before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidLineLabel = false;
			}
			continueParsingLabel = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[GOTO]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	if (isValidLineLabel){
		globalLineLabelName = currentLineLabelName;
	}

	return isNotLastParameter;
}

/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tGOTO::outputGOTOCommand(){
	unsigned int currentMemoryLocation;
	// cout << "\t\t[GOTO]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(GOTO_OP_CODE);
	(*currentFileManager).writeStringToObj(" ");
	(*currentFileManager).writeNumToObj((float) globalLineLabelLineNumber);

	(*currentFileManager).writeStringToObj("\n");
	return;
}


