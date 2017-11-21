/* ==============================================================================

	File: elWRITE.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing lWRITE command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "elWRITE.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

elWRITE::elWRITE(){
	return;
}

elWRITE::~elWRITE(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to LiteralTable with the compiler's (parent's) versions
void elWRITE::prepareLWRITE(LiteralTable *parentLiteralManager){
	currentliteralManager = parentLiteralManager;
}

// calls the functions necessary to parse the line, sync the literal with the LiteralTable, and print the object code to the file while counting errors
// returns number of errors
int elWRITE::handleLWRITE(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[elWRITE]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	globalLiteralObject.variableName = UNNAMED_LITERAL;
	globalLiteralObject.literalString = UNDEFINED_LITERAL;
	globalLiteralObject.memoryLocation = 0;

	parseParameters();

	if (globalNumErrors == 0){
		syncLiteralToLiteralTable();
		outputLWRITECommand();
		cout << "\t\t[elWRITE]: Successfully completed elWRITE command\n";
	}
	else {
		cout << "\t\t[elWRITE]: Failed to complete elWRITE command in line "<< correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseLiteral until no more variable to parse
void elWRITE::parseParameters(){
	// cout <<"\t\t[elWRITE]: Parsing Parameters...\n";
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
void elWRITE::parseLiteral(int *currentCharIterator){
	// cout <<"\t\t[elWRITE]: Parsing Literal...\n";
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
		cout << "\t\t\t[elWRITE]: Invalid Syntax: Expecting \"Begin Quote: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[elWRITE]: Invalid Syntax: Expecting at least one character before End Quote: " << globalCurrentLine << endl;
				isValidLiteral = false;
				globalNumErrors++;
			}
			continueParsingLiteral = false;
			(*currentCharIterator)++;
			caseFound = true;
			if (globalCurrentLine[(*currentCharIterator)] != '\0'){
				cout << "\t\t\t[elWRITE]: Invalid Syntax: Expecting End of Line after End Quote: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInLiteral == 0){
				cout << "\t\t\t[elWRITE]: Invalid Syntax: Expecting \"Quote\" before end of line: " << globalCurrentLine << endl;
				isValidLiteral = false;
				globalNumErrors++;
			}
			else {
				cout << "\t\t\t[elWRITE]: Invalid Syntax: Expecting End Quote\" before end of line: " << globalCurrentLine << endl;
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
		cout << "\t\t[elWRITE]: Found Literal: \""<< globalLiteralObject.literalString << "\"\n";
	}

	return;
}

// parses through a line one character at a time, sets globalLiteralObject.variableName, and returns whether or not there are any more variables to parse
bool elWRITE::parseVariable(int *currentCharIterator){
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
		cout << "\t\t\t[elWRITE]: Invalid Syntax: Literal names must start with a $ : " << globalCurrentLine << endl;
		isValidVariableName = false;
		globalNumErrors++;
		// continueParsingVariable = false; // Comment Out to Continue Parsing Line Regardless
	}


	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t[elWRITE]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[elWRITE]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[elWRITE]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[elWRITE]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[elWRITE]: Invalid Syntax: Expecting at least one character in variable name before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidVariableName = false;
			}
			continueParsingVariable = false;
			isNotLastVariable = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[elWRITE]: Invalid Syntax: Unknown Character ->" << currentChar << "<- in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
			isValidVariableName = false;
		}
	}

	if (isValidVariableName){
		globalLiteralObject.variableName = currentVariableName;
		globalLiteralObject.literalString = UNDEFINED_LITERAL;
		cout << "\t\t[elWRITE]: Found Literal Variable Name: \""<< globalLiteralObject.variableName << "\"\n";
	}

	return isNotLastVariable;
}

// asks the literalManager to conditionally add the globalLiteralString to the Literal table and gets the globalLiteralAddress
void elWRITE::syncLiteralToLiteralTable(){
	// cout << "\t\t[elWRITE]: Attempting to Add Literal to Literal Table...\n";

	(*currentliteralManager).manageLiteralObject(&globalLiteralObject);

	// (*currentliteralManager).printLiteralTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void elWRITE::outputLWRITECommand(){
	unsigned int currentMemoryLocation;
	// cout << "\t\t[elWRITE]: Attempting to Print Object code to .obj...\n";

	// (*currentFileManager).writeStringToObj(LWRITE_OP_CODE);

	// (*currentFileManager).writeStringToObj(" ");
	// currentMemoryLocation = globalLiteralObject.memoryLocation;
	// (*currentFileManager).writeNumToObj((float) currentMemoryLocation);

	// (*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */


