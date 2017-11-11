/*
  ==============================================================================

	File: tlWRITE.cpp
	Author: Brendan Thompson
	Updated: 11/05/17

	Description: Implementation of Functions for processing lWRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tlWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tlWRITE::tlWRITE(){
	return;
}

tlWRITE::~tlWRITE(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & LiteralTable with the compiler's (parent's) versions
void tlWRITE::prepareLWRITE(FileManager *parentFileManager, LiteralTable *parentLiteralManager){
	currentFileManager = parentFileManager;
	currentliteralManager = parentLiteralManager;
}

// calls the functions necessary to parse the line, sync the literal with the LiteralTable, and print the object code to the file while counting errors
// returns number of errors
int tlWRITE::handleLWRITE(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[tlWRITE]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	globalLiteralObject.variableName = UNNAMED_LITERAL;
	globalLiteralObject.literalString = UNDEFINED_LITERAL;
	globalLiteralObject.memoryLocation = 0;

	parseParameters();

	if (globalNumErrors == 0){
		syncLiteralToLiteralTable();
		outputLWRITECommand();
		cout << "\t\t[tlWRITE]: Successfully completed tlWRITE command\n";
	}
	else {
		cout << "\t\t[tlWRITE]: Failed to complete tlWRITE command in line "<< correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseLiteral until no more variable to parse
void tlWRITE::parseParameters(){
	// cout <<"\t\t[tlWRITE]: Parsing Parameters...\n";
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_LWRITE_COMMAND;
	char currentChar = globalCurrentLine[currentCharIterator];

	if (currentChar == '\"'){
		parseLiteral(&currentCharIterator);
	}
	else {
		parseVariable(&currentCharIterator);
	}

	return;
}

// parses through a line one character at a time, and sets globalLiteralObject.literalString
void tlWRITE::parseLiteral(int *currentCharIterator){
	// cout <<"\t\t[tlWRITE]: Parsing Literal...\n";
	char currentChar;
	string currentLiteral = "";
	int numCharactersInLiteral = 0;

	bool continueParsingLiteral = true;
	bool isValidLiteral;
	bool caseFound;

	currentChar = globalCurrentLine[(*currentCharIterator)];
	if (currentChar == '\"'){
		isValidLiteral = true;
		continueParsingLiteral = true;
		(*currentCharIterator)++;
	}
	else {
		cout << "\t\t\t[tlWRITE]: Invalid Syntax: Expecting \"Begin Quote: " << globalCurrentLine << endl;
		isValidLiteral = false;
		globalNumErrors++;
		continueParsingLiteral = false;
	}

	while (continueParsingLiteral){
		caseFound = false;
		currentChar = globalCurrentLine[(*currentCharIterator)];

		// End Quote
		if (currentChar == '\"'){
			if (numCharactersInLiteral == 0){
				cout << "\t\t\t[tlWRITE]: Invalid Syntax: Expecting at least one character before End Quote: " << globalCurrentLine << endl;
				isValidLiteral = false;
				globalNumErrors++;
			}
			continueParsingLiteral = false;
			(*currentCharIterator)++;
			caseFound = true;
			if (globalCurrentLine[(*currentCharIterator)] != '\0'){
				cout << "\t\t\t[tlWRITE]: Invalid Syntax: Expecting End of Line after End Quote: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInLiteral == 0){
				cout << "\t\t\t[tlWRITE]: Invalid Syntax: Expecting \"Quote\" before end of line: " << globalCurrentLine << endl;
				isValidLiteral = false;
				globalNumErrors++;
			}
			else {
				cout << "\t\t\t[tlWRITE]: Invalid Syntax: Expecting End Quote\" before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			continueParsingLiteral = false;
			caseFound = true;
		}

		if (!caseFound){
			currentLiteral += currentChar;
			numCharactersInLiteral++;
			(*currentCharIterator)++;
		}
	}

	if (isValidLiteral){
		globalLiteralObject.variableName = UNNAMED_LITERAL;
		globalLiteralObject.literalString = currentLiteral;
		cout << "\t\t[tlWRITE]: Found Literal: \""<< globalLiteralObject.literalString << "\"\n";
	}

	return;
}

// parses through a line one character at a time, sets globalLiteralObject.variableName, and returns whether or not there are any more variables to parse
bool tlWRITE::parseVariable(int *currentCharIterator){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastVariable = true;
	bool isValidVariableName = true;
	bool caseFound;

	// Check For $
	currentChar = globalCurrentLine[(*currentCharIterator)];
	if (currentChar == '$'){
		currentVariableName += currentChar;
		numCharactersInVarName++;
		(*currentCharIterator)++;
	}
	else {
		cout << "\t\t\t[tlWRITE]: Invalid Syntax: Literal names must start with a $ : " << globalCurrentLine << endl;
		isValidVariableName = false;
		globalNumErrors++;
		// continueParsingVariable = false; // Comment Out to Continue Parsing Line Regardless
	}


	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t[tlWRITE]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[tlWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[tlWRITE]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[tlWRITE]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
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
			isValidVariableName = false;
			globalNumErrors++;
			continueParsingVariable = false;
			(*currentCharIterator)++;
			isNotLastVariable = true;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[tlWRITE]: Invalid Syntax: Expecting at least one character in variable name before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidVariableName = false;
			}
			continueParsingVariable = false;
			isNotLastVariable = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[tlWRITE]: Invalid Syntax: Unknown Character ->" << currentChar << "<- in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
			isValidVariableName = false;
		}
	}

	if (isValidVariableName){
		globalLiteralObject.variableName = currentVariableName;
		globalLiteralObject.literalString = UNDEFINED_LITERAL;
		cout << "\t\t[tlWRITE]: Found Literal Variable Name: \""<< globalLiteralObject.variableName << "\"\n";
	}

	return isNotLastVariable;
}

// asks the literalManager to conditionally add the globalLiteralString to the Literal table and gets the globalLiteralAddress
void tlWRITE::syncLiteralToLiteralTable(){
	// cout << "\t\t[tlWRITE]: Attempting to Add Literal to Literal Table...\n";

	(*currentliteralManager).manageLiteralObject(&globalLiteralObject);

	// (*currentliteralManager).printLiteralTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tlWRITE::outputLWRITECommand(){
	unsigned int currentMemoryLocation;
	// cout << "\t\t[tlWRITE]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(LWRITE_OP_CODE);

	(*currentFileManager).writeStringToObj(" ");
	currentMemoryLocation = globalLiteralObject.memoryLocation;
	(*currentFileManager).writeNumToObj((float) currentMemoryLocation);

	(*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */


