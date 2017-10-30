/*
  ==============================================================================

	File: tIF.cpp
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: Implementation of Functions for processing IF command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tIF.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tIF::tIF(){
	return;
}

tIF::~tIF(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager, SymbolTable, and LineLabelTable with the parent's (compiler's) versions
void tIF::prepareIF(FileManager *parentFileManager, SymbolTable *parentMemoryManager, LineLabelTable *parentLineManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
	currentLineManager = parentLineManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
int tIF::handleIF(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[IF]: Compiling Line: " << globalCurrentLine << endl;

	globalNumErrors = 0;

	parseParameters();

	// printVariableArray();
	syncVariablesToSymbolTable();

	if (globalNumErrors == 0){
		outputIFCommand();
		cout << "\t\t[IF]: Successfully completed IF command\n";
	}
	else {
		cout << "\t\t[IF]: Failed to complete IF command with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
void tIF::syncVariablesToSymbolTable(){
	// cout << "\t\t[IF]: Attempting to Add Arguments to Lookup Table...\n";

	firstID.isArray = false;
	firstID.size = 1;
	secondID.isArray = false;
	secondID.size = 1;

	(*currentMemoryManager).manageMemoryTableObject(&firstID);
	(*currentMemoryManager).manageMemoryTableObject(&secondID);

	// Line Label 1
	globalLineLabel.memoryLocation = (*currentLineManager).getObjLineNumber(globalLineLabel.variableName);
	if (globalLineLabel.memoryLocation == NOT_FOUND_IN_ARRAY){
		cout << "\t\t\t[IF]: Syntax Error: Undeclared Line Label: " << globalCurrentLine << endl;
	}

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tIF::outputIFCommand(){
	// cout << "\t\t[IF]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(IF_OP_CODE);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(firstID.memoryLocation);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(secondID.memoryLocation);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(testCondition);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(globalLineLabel.memoryLocation);
	(*currentFileManager).writeCharToObj('\n');

	return;
}

/* ==============================================================================
	Private Parsing Methods
============================================================================== */

// conditionally calls parseVariable(), parseConstant(), and parseLineLabelName()
void tIF::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_IF_COMMAND;

	string currentArrayName;

	// Handle First "("
	if (globalCurrentLine[currentCharIterator] != '('){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting ( After Command: " << globalCurrentLine << endl;
		globalNumErrors++;
		continueParsingParameters = false; // comment out to continue checking rest of line for errors
	}
	currentCharIterator++;

	// Get First ID
	if (isalpha(globalCurrentLine[currentCharIterator])){
		continueParsingParameters = parseVariable(&currentCharIterator, 0);
	}
	else {
		continueParsingParameters = parseConstant(&currentCharIterator, 0);
	}

	// Get test-condition
	if (!continueParsingParameters){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting Test Condition: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	else {
		parseTestCond(&currentCharIterator);
	}

	// Get Second ID
	if (!continueParsingParameters){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting Second Condition: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	else {
		if (isalpha(globalCurrentLine[currentCharIterator])){
			continueParsingParameters = parseVariable(&currentCharIterator, 1);
		}
		else {
			continueParsingParameters = parseConstant(&currentCharIterator, 1);
		}
	}

	// Skip Past "then"
	if (!continueParsingParameters){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting: then + <lineLabel> : " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	else {
		continueParsingParameters = checkForThen(&currentCharIterator);
	}

	// Get Line Label
	if (!continueParsingParameters){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting Line Label: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	else {
		continueParsingParameters = parseLineLabelName(&currentCharIterator);
	}

	// Should be end of line
	if (continueParsingParameters){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tIF::parseVariable(int *currentCharIterator, int parameterNumber){
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
		// cout << "\t\t\t[IF]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[IF]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[IF]: Current Variable Name: " << currentVariableName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[IF]: Current Variable Name: " << currentVariableName << endl;
		}

		// End Parenthesis
		if (currentChar == ')'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting a Variable Name before ) " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			if (parameterNumber != 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Not Expecting Another ) " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// Comma ,
		if (currentChar == ','){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting a Variable Name before , " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			if (parameterNumber == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting End Parenthesis: " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			if (parameterNumber == 3){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting a Variable Name before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber < 3){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting More Variables before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[IF]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		switch (parameterNumber){
			case 0:
				firstID.variableName = currentVariableName;
				break;
			case 1:
				secondID.variableName = currentVariableName;
				break;
		}
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tIF::parseConstant(int *currentCharIterator, int parameterNumber){
	char currentChar;
	string currentVariableName = "";
	int numCharactersInVarName = 0;

	bool continueParsingVariable = true;
	bool isNotLastParameter = false;
	bool isValidVariableName = true;
	bool readingDecimal = false;
	bool caseFound;

	while (continueParsingVariable){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t\t[LOOP]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[LOOP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[LOOP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Decimal Point
		if (currentChar == '.'){
			if (readingDecimal){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Multiple Decimal Points in One Constant: " << globalCurrentLine << endl;
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
			// cout << "\t\t\t[LOOP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Equals =
		if (currentChar == '='){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Expecting a Variable Name before = " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			if (parameterNumber != 0){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Not Expecting Another Equals Sign " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// Comma ,
		if (currentChar == ','){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Expecting a Variable Name before , " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			if (parameterNumber == 0){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Expecting Equals Sign: " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			if (parameterNumber == 3){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Expecting a Variable Name before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber < 3){
				cout << "\t\t\t[LOOP]: Invalid Syntax: Expecting More Variables before End of Line: " << globalCurrentLine << endl;
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
			case 0:
				firstID.variableName = currentVariableName;
				break;
			case 1:
				secondID.variableName = currentVariableName;
				break;
		}
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, sets global Line Label Names, and returns whether or not there are any more variables to parse
bool tIF::parseLineLabelName(int *currentCharIterator){
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
		// cout << "\t\t[IF]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[IF]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[IF]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[IF]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInLabelName == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting at least one character before ,: " << globalCurrentLine << endl;
				isValidLineLabel = false;
				globalNumErrors++;
			}
			continueParsingLabel = false;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInLabelName == 0){
				cout << "\t\t\t[IF]: Invalid Syntax: Expecting line label before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidLineLabel = false;
			}
			continueParsingLabel = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[IF]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidLineLabel){
		globalLineLabel.variableName = currentLineLabelName;
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, manages the global testCondition
void tIF::parseTestCond(int *currentCharIterator){
	char currentChar;
	bool caseFound = false;

	currentChar = globalCurrentLine[(*currentCharIterator)];
	caseFound = false;
	// cout << "\t\t[IF]: Current Character: " << currentChar << endl;

	// Less Than
	if (currentChar == '<'){
		(*currentCharIterator)++;
		currentChar = globalCurrentLine[(*currentCharIterator)];
		// Check if Less than or Equal To
		testCondition = LESS_CODE;
		if (currentChar == '='){
			(*currentCharIterator)++;
			testCondition = LESS_EQUAL_CODE;
		}
		caseFound = true;
	}

	// Greater Than
	if (currentChar == '>'){
		(*currentCharIterator)++;
		currentChar = globalCurrentLine[(*currentCharIterator)];
		testCondition = GREATER_CODE;
		// Check if Greater than or Equal To
		if (currentChar == '='){
			(*currentCharIterator)++;
			testCondition = GREATER_EQUAL_CODE;
		}
		caseFound = true;
	}

	// Equal To
	if (currentChar == '='){
		(*currentCharIterator)++;
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = true;
		testCondition = EQUAL_CODE;
	}

	// Not Equal To
	if (currentChar == '!'){
		(*currentCharIterator)++;
		currentChar = globalCurrentLine[(*currentCharIterator)];
		// Check if Less than or Equal To
		if (currentChar == '='){
			(*currentCharIterator)++;
			caseFound = true;
			testCondition = NOT_EQUAL_CODE;
		}
	}

	if (!caseFound){
		cout << "\t\t\t[IF]: Invalid Syntax: Unable to Parse Test Condition: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time and returns whether or not there are any more parameters to parse
bool tIF::checkForThen(int *currentCharIterator){
	bool validThen;
	int lengthOfLine = globalCurrentLine.length();
	string thenCommand = globalCurrentLine.substr((*currentCharIterator), lengthOfLine);

	if ((lengthOfLine - (*currentCharIterator)) < 4){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting: then + <lineLabel> : " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	else {
		currentCharIterator += 4;
	}

	if (strncmp(thenCommand.c_str(), "THEN", 3)){
		cout << "\t\t\t[IF]: Invalid Syntax: Expecting: then + <lineLabel> : " << globalCurrentLine << endl;
		globalNumErrors++;
	}
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */