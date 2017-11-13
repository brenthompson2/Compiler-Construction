/* ==============================================================================

	File: elREAD.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing LREAD command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "elREAD.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

elREAD::elREAD(){
	return;
}

elREAD::~elREAD(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & LiteralTable with the compiler's (parent's) versions
void elREAD::prepareLREAD(FileManager *parentFileManager, LiteralTable *parentLiteralManager){
	currentFileManager = parentFileManager;
	currentliteralManager = parentLiteralManager;
}

// calls the functions necessary to parse the line, sync the variables with the LiteralTable, and print the object code to the file while counting errors
// returns number of errors
int elREAD::handleLREAD(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[elREAD]: Compiling Line " << correspondingLineNumber << ": " << globalCurrentLine << endl;

	globalNumErrors = 0;

	globalLiteralObject.variableName = UNNAMED_LITERAL;
	globalLiteralObject.literalString = UNDEFINED_LITERAL;
	globalLiteralObject.memoryLocation = 0;

	parseParameters();

	if (globalNumErrors == 0){
		syncLiteralToLiteralTable();
		outputLREADCommand();
		cout << "\t\t[elREAD]: Successfully completed elREAD command\n";
	}
	else {
		cout << "\t\t[elREAD]: Failed to complete elREAD command in line "<< correspondingLineNumber << " with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// calls parseLiteral until no more variable to parse
void elREAD::parseParameters(){
	// cout <<"\t\t[elREAD]: Parsing Parameters...\n";
	bool continueParsingVariable;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_LREAD_COMMAND;

	continueParsingVariable = parseVariable(&currentCharIterator);

	if (continueParsingVariable){
		cerr << "\t\t\t[elREAD]: Invalid Syntax: Expecting End Of Line after Literal Variable: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, adds complete variables to VariableArray, and returns whether or not there are any more variables to parse
bool elREAD::parseVariable(int *currentCharIterator){
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
		// cout << "\t\t[elREAD]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[elREAD]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[elREAD]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[elREAD]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[elREAD]: Invalid Syntax: Expecting at least one character in variable name before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidVariableName = false;
			}
			continueParsingVariable = false;
			isNotLastVariable = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[elREAD]: Invalid Syntax: Unknown Character ->" << currentChar << "<- in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
			isValidVariableName = false;
		}
	}

	if (isValidVariableName){
		globalLiteralObject.variableName = currentVariableName;
		cout << "\t\t[elREAD]: Found Literal Variable Name: \""<< globalLiteralObject.variableName << "\"\n";
	}

	return isNotLastVariable;
}

// asks the literalManager to conditionally add the globalLiteralString to the Literal table and gets the globalLiteralAddress
void elREAD::syncLiteralToLiteralTable(){
	// cout << "\t\t[elREAD]: Attempting to Add Literal to Literal Table by Variable Name...\n";

	globalLiteralObject.literalString = UNDEFINED_LITERAL;
	(*currentliteralManager).manageLiteralObject(&globalLiteralObject);

	// (*currentliteralManager).printLiteralTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void elREAD::outputLREADCommand(){
	unsigned int currentMemoryLocation;
	// cout << "\t\t[elREAD]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(LREAD_OP_CODE);

	(*currentFileManager).writeStringToObj(" ");
	currentMemoryLocation = globalLiteralObject.memoryLocation;
	(*currentFileManager).writeNumToObj((float) currentMemoryLocation);

	(*currentFileManager).writeStringToObj("\n");
	return;
}



/* ==============================================================================
	Private Accessor Methods
============================================================================== */


