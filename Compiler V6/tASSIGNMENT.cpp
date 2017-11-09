/* ==============================================================================

	File: tASSIGNMENT.cpp
	Author: Brendan Thompson
	Updated: 11/05/17

	Description: Implementation of Functions for processing LOOP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "tASSIGNMENT.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tASSIGNMENT::tASSIGNMENT(){
	return;
}

tASSIGNMENT::~tASSIGNMENT(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tASSIGNMENT::prepareASSIGNMENT(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
// 	currentFileManager = parentFileManager;
// 	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
int tASSIGNMENT::handleASSIGNMENT(string currentLine, int correspondingLineNumber){
// 	globalCurrentLine = currentLine;
// 	cout << "\t\t[ASSIGNMENT]: Compiling Line: " << globalCurrentLine << endl;

// 	// prepareGlobals();
// 	globalNumErrors = 0;
// 	int globalNumIDs = 0;
// 	int globalNumOperators = 0;

// 	parseParameters();

// 	// printVariableArray();
// 	syncVariablesToSymbolTable();

// 	if (globalNumErrors == 0){
// 		outputASSIGNMENTCommand();
// 		cout << "\t\t[ASSIGNMENT]: Successfully completed ASSIGNMENT command\n";
// 	}
// 	else {
// 		cout << "\t\t[ASSIGNMENT]: Failed to complete ASSIGNMENT command with " << globalNumErrors << " errors\n";
// 	}

// 	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the ASSIGNMENTensions
void tASSIGNMENT::parseParameters(){
// 	bool continueParsingParameters = true;
// 	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_ASSIGNMENT_COMMAND;

// 	string currentArrayName;

// 	for (int i = 0; i < 4; i++){

// 		// If Starts With A Digit
// 		if ((isdigit(globalCurrentLine[currentCharIterator])) || (globalCurrentLine[currentCharIterator] == '.')){
// 			continueParsingParameters = parseConstant(&currentCharIterator, i);
// 		}
// 		else { // Doesn't Start With A Digit
// 			continueParsingParameters = parseVariable(&currentCharIterator, i);
// 		}
// 	}

// 	if (continueParsingParameters){
// 		cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
// 		globalNumErrors++;
// 	}

// 	return;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tASSIGNMENT::parseVariable(int *currentCharIterator, int parameterNumber){
// 	char currentChar;
// 	string currentVariableName = "";
// 	int numCharactersInVarName = 0;

// 	bool continueParsingVariable = true;
// 	bool isNotLastParameter = false;
// 	bool isValidVariableName = true;
// 	bool caseFound;

// 	while (continueParsingVariable){
// 		currentChar = globalCurrentLine[(*currentCharIterator)];
// 		caseFound = false;
// 		// cout << "\t\t\t[ASSIGNMENT]: Current Character: " << currentChar << endl;

// 		// Alphabetic
// 		if (isalpha(currentChar)){
// 			currentVariableName += currentChar;
// 			numCharactersInVarName++;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 			// cout << "\t\t\t[ASSIGNMENT]: Current Variable Name: " << currentVariableName << endl;
// 		}

// 		// Digit
// 		if (isdigit(currentChar)){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 			}
// 			currentVariableName += currentChar;
// 			numCharactersInVarName++;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 			// cout << "\t\t\t[ASSIGNMENT]: Current Variable Name: " << currentVariableName << endl;
// 		}

// 		// Underscore
// 		if (currentChar == '_'){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 			}
// 			currentVariableName += currentChar;
// 			numCharactersInVarName++;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 			// cout << "\t\t\t[ASSIGNMENT]: Current Variable Name: " << currentVariableName << endl;
// 		}

// 		// Equals =
// 		if (currentChar == '='){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting a Variable Name before = " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 				isNotLastParameter = true;
// 			}
// 			if (parameterNumber != 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Not Expecting Another Equals Sign " << globalCurrentLine << endl;
// 				globalNumErrors++;
// 				isNotLastParameter = false;
// 			}
// 			continueParsingVariable = false;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 		}

// 		// Comma ,
// 		if (currentChar == ','){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting a Variable Name before , " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 				isNotLastParameter = true;
// 			}
// 			if (parameterNumber == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting Equals Sign: " << globalCurrentLine << endl;
// 				globalNumErrors++;
// 				isNotLastParameter = false;
// 			}
// 			if (parameterNumber == 3){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
// 				globalNumErrors++;
// 				isNotLastParameter = false;
// 			}
// 			continueParsingVariable = false;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 		}

// 		// End Of Line
// 		if (currentChar == '\0'){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting a Variable Name before End of Line: " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 			}
// 			if (parameterNumber < 3){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting More Variables before End of Line: " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 			}
// 			continueParsingVariable = false;
// 			isNotLastParameter = false;
// 			caseFound = true;
// 		}

// 		if (!caseFound){
// 			cout << "\t\t\t[GOTO]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
// 			(*currentCharIterator)++;
// 			globalNumErrors++;
// 		}
//	}

// 	// Assign to Global Parameter Name
// 	if (isValidVariableName){
// 		switch (parameterNumber){
// 			case 0:
// 				indexVariable.variableName = currentVariableName;
// 				break;
// 			case 1:
// 				startIndex.variableName = currentVariableName;
// 				break;
// 			case 2:
// 				endIndex.variableName = currentVariableName;
// 				break;
// 			case 3:
// 				incrementAmount.variableName = currentVariableName;
// 				break;
// 		}
// 	}

// 	return isNotLastParameter;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tASSIGNMENT::parseConstant(int *currentCharIterator, int parameterNumber){
// 	char currentChar;
// 	string currentVariableName = "";
// 	int numCharactersInVarName = 0;

// 	bool continueParsingVariable = true;
// 	bool isNotLastParameter = false;
// 	bool isValidVariableName = true;
// 	bool readingDecimal = false;
// 	bool caseFound;

// 	while (continueParsingVariable){
// 		currentChar = globalCurrentLine[(*currentCharIterator)];
// 		caseFound = false;
// 		// cout << "\t\t\t[ASSIGNMENT]: Current Character: " << currentChar << endl;

// 		// Alphabetic
// 		if (isalpha(currentChar)){
// 			currentVariableName += currentChar;
// 			numCharactersInVarName++;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 			// cout << "\t\t\t[ASSIGNMENT]: Current Variable Name: " << currentVariableName << endl;
// 		}

// 		// Digit
// 		if (isdigit(currentChar)){
// 			currentVariableName += currentChar;
// 			numCharactersInVarName++;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 			// cout << "\t\t\t[ASSIGNMENT]: Current Variable Name: " << currentVariableName << endl;
// 		}

// 		// Decimal Point
// 		if (currentChar == '.'){
// 			if (readingDecimal){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Multiple Decimal Points in One Constant: " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 				isNotLastParameter = true;
// 			}
// 			else {
// 				readingDecimal = true;
// 				currentVariableName += currentChar;
// 				numCharactersInVarName++;
// 				(*currentCharIterator)++;
// 			}
// 			caseFound = true;
// 			// cout << "\t\t\t[ASSIGNMENT]: Current Variable Name: " << currentVariableName << endl;
// 		}

// 		// Equals =
// 		if (currentChar == '='){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting a Variable Name before = " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 				isNotLastParameter = true;
// 			}
// 			if (parameterNumber != 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Not Expecting Another Equals Sign " << globalCurrentLine << endl;
// 				globalNumErrors++;
// 				isNotLastParameter = false;
// 			}
// 			continueParsingVariable = false;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 		}

// 		// Comma ,
// 		if (currentChar == ','){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting a Variable Name before , " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 				isNotLastParameter = true;
// 			}
// 			if (parameterNumber == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting Equals Sign: " << globalCurrentLine << endl;
// 				globalNumErrors++;
// 				isNotLastParameter = false;
// 			}
// 			if (parameterNumber == 3){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
// 				globalNumErrors++;
// 				isNotLastParameter = false;
// 			}
// 			continueParsingVariable = false;
// 			(*currentCharIterator)++;
// 			caseFound = true;
// 		}

// 		// End Of Line
// 		if (currentChar == '\0'){
// 			if (numCharactersInVarName == 0){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting a Variable Name before End of Line: " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 			}
// 			if (parameterNumber < 3){
// 				cout << "\t\t\t[ASSIGNMENT]: Invalid Syntax: Expecting More Variables before End of Line: " << globalCurrentLine << endl;
// 				isValidVariableName = false;
// 				globalNumErrors++;
// 			}
// 			continueParsingVariable = false;
// 			isNotLastParameter = false;
// 			caseFound = true;
// 		}

// 		if (!caseFound){
// 			cout << "\t\t\t[GOTO]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
// 			(*currentCharIterator)++;
// 			globalNumErrors++;
// 		}
//	}

// 	// Assign to Global Parameter Name
// 	if (isValidVariableName){
// 		switch (parameterNumber){
// 			case 0:
// 				indexVariable.variableName = currentVariableName;
// 				break;
// 			case 1:
// 				startIndex.variableName = currentVariableName;
// 				break;
// 			case 2:
// 				endIndex.variableName = currentVariableName;
// 				break;
// 			case 3:
// 				incrementAmount.variableName = currentVariableName;
// 				break;
// 		}
// 	}

// 	return isNotLastParameter;
// }

// void prepareGlobals(){
// 	globalNumErrors = 0;

// 	for (int i = 0; i < MAX_NUM_OPERATORS){

// 	}
}

// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
void tASSIGNMENT::syncVariablesToSymbolTable(){
// 	// cout << "\t\t[ASSIGNMENT]: Attempting to Add Arguments to Lookup Table...\n";
// 	indexVariable.isArray = false;
// 	indexVariable.size = 1;
// 	startIndex.isArray = false;
// 	startIndex.size = 1;
// 	endIndex.isArray = false;
// 	endIndex.size = 1;
// 	incrementAmount.isArray = false;
// 	incrementAmount.size = 1;

// 	(*currentMemoryManager).manageMemoryTableObject(&indexVariable);
// 	(*currentMemoryManager).manageMemoryTableObject(&startIndex);
// 	(*currentMemoryManager).manageMemoryTableObject(&endIndex);
// 	(*currentMemoryManager).manageMemoryTableObject(&incrementAmount);

// 	// (*currentMemoryManager).printSymbolTable();
// 	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tASSIGNMENT::outputASSIGNMENTCommand(){
// 	unsigned int currentMemoryLocation;
// 	unsigned int size;
// 	// cout << "\t\t[ASSIGNMENT]: Attempting to Print Object code to .obj...\n";

// 	(*currentFileManager).writeStringToObj(ASSIGNMENT_OP_CODE);
// 	(*currentFileManager).writeStringToObj(" ");

// 	(*currentFileManager).writeNumToObj((float) indexVariable.memoryLocation);
// 	(*currentFileManager).writeStringToObj(" ");

// 	(*currentFileManager).writeNumToObj((float) startIndex.memoryLocation);
// 	(*currentFileManager).writeStringToObj(" ");

// 	(*currentFileManager).writeNumToObj((float) endIndex.memoryLocation);
// 	(*currentFileManager).writeStringToObj(" ");

// 	(*currentFileManager).writeNumToObj((float) incrementAmount.memoryLocation);
// 	(*currentFileManager).writeStringToObj("\n");

// 	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */