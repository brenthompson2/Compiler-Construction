/*
  ==============================================================================

	File: tDIM.cpp
	Author: Brendan Thompson
	Updated: 10/13/17

	Description: Implementation of Functions for processing DIM command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tDIM.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tDIM::tDIM(){
	return;
}

tDIM::~tDIM(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void tDIM::prepareDIM(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
int tDIM::handleDIM(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	// cout << "\t\t[DIM]: Compiling Line: " << globalCurrentLine << endl;

	numVariablesInArray = 0;
	globalNumErrors = 0;

	parseParameters();

	// printVariableArray();
	syncVariableArrayToSymbolTable();

	if (globalNumErrors == 0){
		outpuDIMCommand();
		// cout << "\t\t[DIM]: Successfully completed DIM command\n";
	}
	else {
		cout << "\t\t[DIM]: Failed to complete DIM command with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the dimensions
void tDIM::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_DIM_COMMAND;

	string currentArrayName;
	int currentArraySize;
	int numErrorsBefore;

	while (continueParsingParameters){
		numErrorsBefore = globalNumErrors;

		// Get Array Name
		continueParsingParameters = parseVariable(&currentCharIterator, &currentArrayName);

		// Get Array Size
		if (continueParsingParameters){
			continueParsingParameters = parseSize(&currentCharIterator, &currentArraySize);
		}
		else {
			cout << "\t\t\t[DIM]: Error: Expected array size declaration: " << globalCurrentLine << endl;
			globalNumErrors++;
		}

		// Add to Variable Array
		if (globalNumErrors == numErrorsBefore){
			addToVariableArray(currentArrayName, currentArraySize);
		}
	}

	return;
}

// parses through a line one character at a time, manages arrayName pointer, and returns whether or not there are any more parameters to parse
bool tDIM::parseVariable(int *currentCharIterator, string *arrayName){
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
		// cout << "\t\t\t[DIM]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[DIM]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[DIM]: Current Variable Name: " << currentVariableName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// Bracket
		if (currentChar == '['){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting an array name before the size: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			isNotLastParameter = true;
			caseFound = true;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting an array name and size before ,: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			else {
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting a size before ,: " << globalCurrentLine << endl;
			}
			continueParsingVariable = false;
			(*currentCharIterator)++;
			isNotLastParameter = true;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting an array name and size before before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidVariableName = false;
			}
			else {
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting a size before end of line : " << globalCurrentLine << endl;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[DIM]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	if (isValidVariableName){
		(*arrayName) = currentVariableName;
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, manages the arraySize pointer, and returns whether or not there are any more parameters to parse
bool tDIM::parseSize(int *currentCharIterator, int *arraySize){
	char currentChar;
	string currentSizeString = "";
	int numCharactersInSize = 0;

	bool continueParsingSize = true;
	bool isNotLastParameter = false;
	bool isValidSize = false;
	bool caseFound;

	while (continueParsingSize){
		currentChar = globalCurrentLine[(*currentCharIterator)];
		caseFound = false;
		// cout << "\t\t[DIM]: Current Character: " << currentChar << endl;

		// Alphabetic
		// if (isalpha(currentChar)){
		// 	currentVariableName += currentChar;
		// 	numCharactersInSize++;
		// 	(*currentCharIterator)++;
		// 	// cout << "\t\t[tREAD]: Current Variable Name: " << currentVariableName << endl;
		// }

		// Digit
		if (isdigit(currentChar)){
			isValidSize = true;
			currentSizeString += currentChar;
			numCharactersInSize++;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// Close Bracket ]
		if (currentChar == ']'){
			if (numCharactersInSize == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting a size before ] : " << globalCurrentLine << endl;
				isValidSize = false;
				globalNumErrors++;
			}
			// If Next Char is ,
			if (globalCurrentLine[(*currentCharIterator) + 1] == ','){
				isNotLastParameter = true;
				(*currentCharIterator)++; // eat , also
			}
			else {
				// If Next Char is end of line
				if (globalCurrentLine[(*currentCharIterator) + 1] == '\0'){
					isNotLastParameter = false;
				}
				else {
					cout << "\t\t\t[DIM]: Invalid Syntax: Expecting a , after ] : " << globalCurrentLine << endl;
					isValidSize = false;
					globalNumErrors++;
					isNotLastParameter = false; // stops iterating through parameters
				}
			}
			continueParsingSize = false;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInSize == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting a size and a ] before , : " << globalCurrentLine << endl;
			}
			else {
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting a ] before , : " << globalCurrentLine << endl;
			}
			isValidSize = false;
			globalNumErrors++;
			continueParsingSize = false;
			(*currentCharIterator)++;
			isNotLastParameter = true;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInSize == 0){
				cout << "\t\t\t[DIM]: Invalid Syntax: Expecting at least one digit in index: " << globalCurrentLine << endl;
				globalNumErrors++;
			}
			continueParsingSize = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[DIM]: Invalid Syntax: Invalid Character ->" << currentChar << "<- in dimension in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	if (isValidSize){
		// string to int conversion method from https://stackoverflow.com/questions/6093414/convert-char-array-to-single-int
		std::stringstream str(currentSizeString);
		str >> (*arraySize);
	}

	return isNotLastParameter;
}

// adds the currentArrayName to the variableArray and increments numVariablesInArray
void tDIM::addToVariableArray(string currentArrayName, int currentArraySize){
	if (numVariablesInArray == (MAX_ARGUMENTS - 1)){
		cout << "\t\t[DIM]: Invalid Syntax: Number of Arguments in DIM Command Exceeds " << MAX_ARGUMENTS << ": " << globalCurrentLine << endl;
		return;
	}

	variableArray[numVariablesInArray].variableName = currentArrayName;
	variableArray[numVariablesInArray].isArray = true;
	variableArray[numVariablesInArray].size = currentArraySize;
	numVariablesInArray++;
	// cout << "\t\t[DIM]: Added Variable to Array: " << currentArrayName << endl;
	return;
}

// iterates through the variableArray and tells the memoryManager to conditionally add them to the symbol table
void tDIM::syncVariableArrayToSymbolTable(){
	// cout << "\t\t[DIM]: Attempting to Add Variable Array to Lookup Table...\n";

	for (int i = 0; i < numVariablesInArray; i++){
		if ((*currentMemoryManager).currentlyExists(variableArray[i].variableName)){
			cout << "\t\t[DIM]: Error: Array " << variableArray[i].variableName << " already exists in the symbol table\n";
			globalNumErrors++;
		}
		else {
			(*currentMemoryManager).manageMemoryTableObject(&variableArray[i]);
		}

	}

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tDIM::outpuDIMCommand(){
	unsigned int currentMemoryLocation;
	unsigned int size;
	// cout << "\t\t[DIM]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(DIM_OP_CODE);

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentFileManager).writeStringToObj(" ");
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		(*currentFileManager).writeNumToObj((double) currentMemoryLocation);
		(*currentFileManager).writeStringToObj(" ");
		size = (variableArray[i]).size;
		(*currentFileManager).writeNumToObj((double) size);
	}

	(*currentFileManager).writeStringToObj("\n");
	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// prints the variableArray to the console
void tDIM::printVariableArray(){
	string currentArrayName;
	unsigned int currentMemoryLocation;

	cout << "\t\t[DIM]: Variable Array: " << currentArrayName << endl;

	for (int i = 0; i < numVariablesInArray; i++){
		currentArrayName = (variableArray[i]).variableName;
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		cout << "\t\t\t" << currentArrayName << ": " << currentMemoryLocation << endl;
	}
	return;
}


