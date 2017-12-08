/*
  ==============================================================================

	File: tCDUMP.cpp
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: Implementation of Functions for processing CDUMP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tCDUMP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tCDUMP::tCDUMP(){
	return;
}

tCDUMP::~tCDUMP(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tCDUMP::prepareCDUMP(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
int tCDUMP::handleCDUMP(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	// cout << "\t\t[CDUMP]: Compiling Line: " << globalCurrentLine << endl;

	globalNumErrors = 0;

	parseParameters();

	if (globalNumErrors == 0){
		syncVariablesToSymbolTable();
		outputCDUMPCommand();
		// cout << "\t\t[CDUMP]: Successfully completed CDUMP command\n";
	}
	else {
		cout << "\t\t[CDUMP]: Failed to complete CDUMP command with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the CDUMPensions
void tCDUMP::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_CDUMP_COMMAND;

	string currentArrayName;

	// Parse START Index
	if ((isdigit(globalCurrentLine[currentCharIterator])) || (globalCurrentLine[currentCharIterator] == '.') || (globalCurrentLine[currentCharIterator] == '-')){
		continueParsingParameters = parseConstant(&currentCharIterator, START_ID_CODE);
	}
	else {
		continueParsingParameters = parseVariable(&currentCharIterator, START_ID_CODE);
	}

	// Parse END Index
	if (continueParsingParameters){
		if ((isdigit(globalCurrentLine[currentCharIterator])) || (globalCurrentLine[currentCharIterator] == '.')){
			continueParsingParameters = parseConstant(&currentCharIterator, END_ID_CODE);
		}
		else {
			continueParsingParameters = parseVariable(&currentCharIterator, END_ID_CODE);
		}
	}
	else {
		cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting End Index: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	if (continueParsingParameters){
		cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tCDUMP::parseVariable(int *currentCharIterator, int parameterNumber){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastParameter = false;
	bool isValidVariableName = true;
	bool caseFound;

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t\t[CDUMP]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Comma ,
		if (currentChar == ','){
			if (parameterNumber == END_ID_CODE){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Not Expecting Comma after EndIndex: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			else {
				if (numCharactersInVarName == 0){
					cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting an ID before , " << globalCurrentLine << endl;
					isValidVariableName = false;
					globalNumErrors++;
				}
			}
			continueParsingVariable = false;
			isNotLastParameter = true;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting an ID before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber == START_ID_CODE){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting EndIndex after StartIndex: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[GOTO]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		switch (parameterNumber){
			case START_ID_CODE:
				globalStartIndex.variableName = currentVariableName;
				globalStartIndex.isConstant = false;
				break;
			case END_ID_CODE:
				globalEndIndex.variableName = currentVariableName;
				globalEndIndex.isConstant = false;
				break;
		}
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tCDUMP::parseConstant(int *currentCharIterator, int parameterNumber){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastParameter = false;
	bool isValidVariableName = true;
	bool readingDecimal = false;
	bool caseFound;

	// Handle Negatives
	currentChar = globalCurrentLine[(*currentCharIterator)];
	if (currentChar == '-'){
		currentVariableName += currentChar;
		numCharactersInVarName++;
		(*currentCharIterator)++;
		// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
	}

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t\t[CDUMP]: Current Character: " << currentChar << endl;

		// Alphabetic (wont happen first time since already checked)
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Decimal Point
		if (currentChar == '.'){
			if (readingDecimal){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Multiple Decimal Points in One Constant: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			else {
				readingDecimal = true;
				currentVariableName += currentChar;
				numCharactersInVarName++;
				(*currentCharIterator)++;
			}
			caseFound = true;
			// cout << "\t\t\t[CDUMP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Comma ,
		if (currentChar == ','){
			if (parameterNumber == END_ID_CODE){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Not Expecting Comma after EndIndex: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			else {
				if (numCharactersInVarName == 0){
					cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting an ID before , " << globalCurrentLine << endl;
					isValidVariableName = false;
					globalNumErrors++;
				}
			}
			continueParsingVariable = false;
			isNotLastParameter = true;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting a Variable Name before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber == START_ID_CODE){
				cout << "\t\t\t[CDUMP]: Invalid Syntax: Expecting EndIndex after StartIndex: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[GOTO]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		switch (parameterNumber){
			case START_ID_CODE:
				globalStartIndex.variableName = currentVariableName;
				globalStartIndex.isConstant = true;
				break;
			case END_ID_CODE:
				globalEndIndex.variableName = currentVariableName;
				globalEndIndex.isConstant = true;
				break;
		}
	}

	return isNotLastParameter;
}

// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
void tCDUMP::syncVariablesToSymbolTable(){
	// cout << "\t\t[CDUMP]: Attempting to Add Arguments to Symbol Table...\n";
	globalStartIndex.isArray = false;
	globalStartIndex.size = 1;
	globalEndIndex.isArray = false;
	globalEndIndex.size = 1;

	(*currentMemoryManager).manageMemoryTableObject(&globalStartIndex);
	(*currentMemoryManager).manageMemoryTableObject(&globalEndIndex);

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tCDUMP::outputCDUMPCommand(){
	unsigned int currentMemoryLocation;
	unsigned int size;
	// cout << "\t\t[CDUMP]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(CDUMP_OP_CODE);
	(*currentFileManager).writeStringToObj(" ");

	(*currentFileManager).writeNumToObj((double) globalStartIndex.memoryLocation);
	(*currentFileManager).writeStringToObj(" ");

	(*currentFileManager).writeNumToObj((double) globalEndIndex.memoryLocation);
	(*currentFileManager).writeStringToObj("\n");

	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */