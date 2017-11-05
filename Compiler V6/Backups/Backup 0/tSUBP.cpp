/*
  ==============================================================================

	File: tSUBP.cpp
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: Implementation of Functions for processing SUBP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tSUBP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tSUBP::tSUBP(){
	return;
}

tSUBP::~tSUBP(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager and SymbolTable with the parent's (compiler's) versions
void tSUBP::prepareSUBP(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
int tSUBP::handleSUBP(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[SUBP]: Compiling Line: " << globalCurrentLine << endl;

	globalNumErrors = 0;

	parseParameters();

	// printVariableArray();
	syncVariablesToSymbolTable();

	if (globalNumErrors == 0){
		outputSUBPCommand();
		cout << "\t\t[SUBP]: Successfully completed SUBP command\n";
	}
	else {
		cout << "\t\t[SUBP]: Failed to complete SUBP command with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
void tSUBP::syncVariablesToSymbolTable(){
	// cout << "\t\t[SUBP]: Attempting to Add Arguments to Lookup Table...\n";

	globalVariable.isArray = false;
	globalVariable.size = 1;
	secondID.isArray = false;
	secondID.size = 1;

	(*currentMemoryManager).manageMemoryTableObject(&globalVariable);
	(*currentMemoryManager).manageMemoryTableObject(&secondID);

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tSUBP::outputSUBPCommand(){
	// cout << "\t\t[SUBP]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(SUBP_OP_CODE);
	(*currentFileManager).writeStringToObj(" ");

	(*currentFileManager).writeNumToObj(globalOperation);
	(*currentFileManager).writeStringToObj(" ");

	(*currentFileManager).writeNumToObj((float) globalVariable.memoryLocation);
	(*currentFileManager).writeStringToObj(" ");

	(*currentFileManager).writeNumToObj((float) secondID.memoryLocation);
	(*currentFileManager).writeStringToObj("\n");

	return;
}

/* ==============================================================================
	Private Parsing Methods
============================================================================== */

// conditionally calls parseVariable(), parseConstant(), and parseLineLabelName()
void tSUBP::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_SUBP_COMMAND;

	string currentArrayName;
	char currentChar = globalCurrentLine[currentCharIterator];

	// Parse Operation
	parseOperation(&currentCharIterator);

	// Handle First "("
	currentChar = globalCurrentLine[currentCharIterator];
	if (currentChar != '('){
		cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting (<variable>, <id>) : " << globalCurrentLine << endl;
		globalNumErrors++;
		continueParsingParameters = false; // comment out to continue checking rest of line for errors
	}
	currentCharIterator++;


	// Get Variable
	if (!continueParsingParameters){
		cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting A Variable: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	else {
		continueParsingParameters = parseVariable(&currentCharIterator, VARIABLE_ID_CODE);
	}

	// Get Second ID
	if (!continueParsingParameters){
		cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting Second Condition: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	else {
		currentChar = globalCurrentLine[currentCharIterator];
		if (isalpha(currentChar)){
			continueParsingParameters = parseVariable(&currentCharIterator, OTHER_ID_CODE);
		}
		else {
			continueParsingParameters = parseConstant(&currentCharIterator, OTHER_ID_CODE);
		}
	}

	// Should be end of line
	if (continueParsingParameters){
		cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tSUBP::parseVariable(int *currentCharIterator, int parameterNumber){
	// cout << "\t\t\t[SUBP]: Parsing Variable...\n";
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
		// cout << "\t\t\t[SUBP]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[SUBP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[SUBP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[SUBP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting (<variable>, <ID>): " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber == OTHER_ID_CODE){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting ) instead of , : " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = true;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Parenthesis
		if (currentChar == ')'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting (<variable>, <ID>): " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber == VARIABLE_ID_CODE){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting , before ) : " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = true;
			(*currentCharIterator)++;
			if (globalCurrentLine[(*currentCharIterator)] == '\0'){
				isNotLastParameter = false;
			}
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting (<variable>, <ID>): " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			else {
				if (parameterNumber == VARIABLE_ID_CODE){
					cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting , before End of Line: " << globalCurrentLine << endl;
					globalNumErrors++;
				}
				if (parameterNumber == OTHER_ID_CODE){
					cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting ) before End of Line : " << globalCurrentLine << endl;
					globalNumErrors++;
				}
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[SUBP]: Invalid Syntax: Unknown Character ->" << currentChar << "<- in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		switch (parameterNumber){
			case VARIABLE_ID_CODE:
				globalVariable.variableName = currentVariableName;
				break;
			case OTHER_ID_CODE:
				secondID.variableName = currentVariableName;
				secondID.isConstant = false;
				break;
		}
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tSUBP::parseConstant(int *currentCharIterator, int parameterNumber){
	// cout << "\t\t[SUBP]: Parsing Constant...\n";
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
		// cout << "\t\t\t[SUBP]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[SUBP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[SUBP]: Current Variable Name: " << currentVariableName << endl;
		}

		// Decimal Point
		if (currentChar == '.'){
			if (readingDecimal){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Multiple Decimal Points in One Constant: " << globalCurrentLine << endl;
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
			// cout << "\t\t\t[SUBP]: Current Variable Name: " << currentVariableName << endl;
		}

		// End Parenthesis
		if (currentChar == ')'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting an ID instead of ) " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = true;
			(*currentCharIterator)++;
			if (globalCurrentLine[(*currentCharIterator)] == '\0'){
				isNotLastParameter = false;
			}
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[SUBP]: Invalid Syntax: Expecting ID before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[SUBP]: Invalid Syntax: Unknown Character ->" << currentChar << "<- in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		secondID.variableName = currentVariableName;
		secondID.isConstant = true;
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, manages the global globalOperation
void tSUBP::parseOperation(int *currentCharIterator){
	// cout << "\t\t[SUBP]: Parsing Test Cond...\n";
	string operationString;
	bool caseFound = false;

	operationString = globalCurrentLine.substr(4, 3);
	caseFound = false;
	// cout << "\t\t\t[SUBP]: Matching Operation: " << operationString << "...\n";

	if (operationString == "SIN"){
		// cout << "\t\t\t[SUBP]: Found SIN Command\n";
		caseFound = true;
		globalOperation = SIN_CODE;
	}

	if (operationString == "COS"){
		// cout << "\t\t\t[SUBP]: Found COS Command\n";
		caseFound = true;
		globalOperation = COS_CODE;
	}

	if (operationString == "EXP"){
		// cout << "\t\t\t[SUBP]: Found EXP Command\n";
		caseFound = true;
		globalOperation = EXP_CODE;
	}

	if (operationString == "ABS"){
		// cout << "\t\t\t[SUBP]: Found ABS Command\n";
		caseFound = true;
		globalOperation = ABS_CODE;
	}

	if (operationString == "ALG"){
		// cout << "\t\t\t[SUBP]: Found ALG Command\n";
		caseFound = true;
		globalOperation = ALG_CODE;
	}

	if (operationString == "ALN"){
		// cout << "\t\t\t[SUBP]: Found ALN Command\n";
		caseFound = true;
		globalOperation = ALN_CODE;
	}

	if (operationString == "LOG"){
		// cout << "\t\t\t[SUBP]: Found LOG Command\n";
		caseFound = true;
		globalOperation = LOG_CODE;
	}

	if (operationString == "SQR"){
		// cout << "\t\t\t[SUBP]: Found SQR Command\n";
		caseFound = true;
		globalOperation = SQR_CODE;
	}

	if (!caseFound){
		cout << "\t\t\t[SUBP]: Invalid Syntax: Unknown Operation: " << operationString << endl;
		globalNumErrors++;
	}

	(*currentCharIterator) += 3;

	return;
}

/* ==============================================================================
	Private Accessor Methods
============================================================================== */