/* ==============================================================================

	File: ExpressionParsingMatrix.cpp
	Author: Brendan Thompson
	Updated: 11/08/17

	Description: Implementation of Functions for processing ExpressionParsingMatrix command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "ExpressionParsingMatrix.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

ExpressionParsingMatrix::ExpressionParsingMatrix(){
	createMatrix();
	return;
}

ExpressionParsingMatrix::~ExpressionParsingMatrix(){
	return;
}

// Populates every INDEX of each array with the correct TOKEN
void ExpressionParsingMatrix::createMatrix(){

	// Input ID
	InputObject[INDEX_ID].topSTWOArray[INDEX_NULL] = TOKEN_S_ONE;
	InputObject[INDEX_ID].topSTWOArray[INDEX_EQUALS] = TOKEN_S_ONE;
	InputObject[INDEX_ID].topSTWOArray[INDEX_PLUS] = TOKEN_S_ONE;
	InputObject[INDEX_ID].topSTWOArray[INDEX_MINUS] = TOKEN_S_ONE;
	InputObject[INDEX_ID].topSTWOArray[INDEX_TIMES] = TOKEN_S_ONE;
	InputObject[INDEX_ID].topSTWOArray[INDEX_DIVIDE] = TOKEN_S_ONE;
	InputObject[INDEX_ID].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_S_ONE;
	InputObject[INDEX_ID].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_S_ONE;
	// InputObject[INDEX_ID].topSTWOArray[INDEX_EXPONENT] = TOKEN_S_ONE;

	// Input =
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_NULL] = TOKEN_S_TWO;
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_EQUALS] = TOKEN_ERROR;
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_PLUS] = TOKEN_ERROR;
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_MINUS] = TOKEN_ERROR;
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_TIMES] = TOKEN_ERROR;
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_DIVIDE] = TOKEN_ERROR;
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_ERROR;
	InputObject[INDEX_EQUALS].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_ERROR;
	// InputObject[INDEX_EQUALS].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input +
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_EQUALS] = TOKEN_S_TWO;
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_PLUS] = TOKEN_U_ONE;
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_MINUS] = TOKEN_U_ONE;
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_TIMES] = TOKEN_U_ONE;
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_ONE;
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_S_TWO;
	InputObject[INDEX_PLUS].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_S_TWO;
	// InputObject[INDEX_PLUS].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input -
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_EQUALS] = TOKEN_S_TWO;
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_PLUS] = TOKEN_U_ONE;
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_MINUS] = TOKEN_U_ONE;
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_TIMES] = TOKEN_U_ONE;
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_ONE;
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_S_TWO;
	InputObject[INDEX_MINUS].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_S_TWO;
	// InputObject[INDEX_MINUS].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input *
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_EQUALS] = TOKEN_S_TWO;
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_PLUS] = TOKEN_S_TWO;
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_MINUS] = TOKEN_S_TWO;
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_TIMES] = TOKEN_U_ONE;
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_ONE;
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_S_TWO;
	InputObject[INDEX_TIMES].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_S_TWO;
	// InputObject[INDEX_TIMES].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input /
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_EQUALS] = TOKEN_S_TWO;
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_PLUS] = TOKEN_S_TWO;
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_MINUS] = TOKEN_S_TWO;
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_TIMES] = TOKEN_U_ONE;
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_ONE;
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_S_TWO;
	InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_S_TWO;
	// InputObject[INDEX_DIVIDE].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input (
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_EQUALS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_PLUS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_MINUS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_TIMES] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_DIVIDE] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_S_TWO;
	// InputObject[INDEX_LEFT_PARENTHESIS].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input )
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_EQUALS] = TOKEN_ERROR;
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_PLUS] = TOKEN_U_TWO;
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_MINUS] = TOKEN_U_TWO;
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_TIMES] = TOKEN_U_TWO;
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_TWO;
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_U_TWO;
	InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_ERROR;
	// InputObject[INDEX_RIGHT_PARENTHESIS].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input ^
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_EQUALS] = TOKEN_ERROR;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_PLUS] = TOKEN_U_TWO;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_MINUS] = TOKEN_U_TWO;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_TIMES] = TOKEN_U_TWO;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_TWO;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_U_TWO;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_ERROR;
	// InputObject[INDEX_EXPONENT].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input [
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_NULL] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_EQUALS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_PLUS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_MINUS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_TIMES] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_DIVIDE] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_S_TWO;
	InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_S_TWO;
	// InputObject[INDEX_LEFT_BRACKET].topSTWOArray[INDEX_EXPONENT] = TOKEN_S_TWO;

	// Input ]
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_EQUALS] = TOKEN_ERROR;
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_PLUS] = TOKEN_U_FOUR;
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_MINUS] = TOKEN_U_FOUR;
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_TIMES] = TOKEN_U_FOUR;
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_FOUR;
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_ERROR;
	InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_U_FOUR;
	// InputObject[INDEX_RIGHT_BRACKET].topSTWOArray[INDEX_EXPONENT] = TOKEN_ERROR;

	// Input EOL
	InputObject[INDEX_EOL].topSTWOArray[INDEX_NULL] = TOKEN_ERROR;
	InputObject[INDEX_EOL].topSTWOArray[INDEX_EQUALS] = TOKEN_U_THREE;
	InputObject[INDEX_EOL].topSTWOArray[INDEX_PLUS] = TOKEN_U_THREE;
	InputObject[INDEX_EOL].topSTWOArray[INDEX_MINUS] = TOKEN_U_THREE;
	InputObject[INDEX_EOL].topSTWOArray[INDEX_TIMES] = TOKEN_U_THREE;
	InputObject[INDEX_EOL].topSTWOArray[INDEX_DIVIDE] = TOKEN_U_THREE;
	InputObject[INDEX_EOL].topSTWOArray[INDEX_LEFT_PARENTHESIS] = TOKEN_ERROR;
	InputObject[INDEX_EOL].topSTWOArray[INDEX_LEFT_BRACKET] = TOKEN_ERROR;
	// InputObject[INDEX_EOL].topSTWOArray[INDEX_EXPONENT] = TOKEN_U_THREE;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */


// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
// void ExpressionParsingMatrix::prepareASSIGNMENT(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
// }


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
// int ExpressionParsingMatrix::handleASSIGNMENT(string currentLine, int correspondingLineNumber){
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
// 		outpuExpressionParsingMatrixCommand();
// 		cout << "\t\t[ASSIGNMENT]: Successfully completed ASSIGNMENT command\n";
// 	}
// 	else {
// 		cout << "\t\t[ASSIGNMENT]: Failed to complete ASSIGNMENT command with " << globalNumErrors << " errors\n";
// 	}

// 	return globalNumErrors;
// }

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the ASSIGNMENTensions
// void ExpressionParsingMatrix::parseParameters(){
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
// }

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
// bool ExpressionParsingMatrix::parseVariable(int *currentCharIterator, int parameterNumber){
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
// }

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
// bool ExpressionParsingMatrix::parseConstant(int *currentCharIterator, int parameterNumber){
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
// }

// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
// void ExpressionParsingMatrix::syncVariablesToSymbolTable(){
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
// }

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
// void ExpressionParsingMatrix::outpuExpressionParsingMatrixCommand(){
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
// }


/* ==============================================================================
	Private Accessor Methods
==============================================================================