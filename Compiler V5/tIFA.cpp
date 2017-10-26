/*
  ==============================================================================

	File: tIFA.cpp
	Author: Brendan Thompson
	Updated: 10/12/17

	Description: Implementation of Functions for processing IFA command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "tIFA.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

tIFA::tIFA(){
	return;
}

tIFA::~tIFA(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager, SymbolTable, and LineLabelTable with the parent's (compiler's) versions
void tIFA::prepareIFA(FileManager *parentFileManager, SymbolTable *parentMemoryManager, LineLabelTable *parentLineManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
	currentLineManager = parentLineManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
// returns num errors
int tIFA::handleIFA(string currentLine, int correspondingLineNumber){
	globalCurrentLine = currentLine;
	cout << "\t\t[IFA]: Compiling Line: " << globalCurrentLine << endl;

	globalNumErrors = 0;

	parseParameters();

	// printVariableArray();
	syncVariablesToSymbolTable();

	if (globalNumErrors == 0){
		outputIFACommand();
		cout << "\t\t[IFA]: Successfully completed IFA command\n";
	}
	else {
		cout << "\t\t[IFA]: Failed to complete IFA command with " << globalNumErrors << " errors\n";
	}

	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iteratively calls parseVariable() to get arrayName, and then parseSize() to get the IFAensions
void tIFA::parseParameters(){
	bool continueParsingParameters = true;
	int currentCharIterator = INDEX_FIRST_CHAR_AFTER_IFA_COMMAND;

	string currentArrayName;

	// Handle First "("
	if (globalCurrentLine[currentCharIterator] != '('){
		cout << "\t\t\t[IFA]: Invalid Syntax: Expecting ( After Command: " << globalCurrentLine << endl;
		globalNumErrors++;
	}
	currentCharIterator++;

	for (int i = 0; i < 4; i++){

		if (i == 0){
			continueParsingParameters = parseVariable(&currentCharIterator, i);
		}
		else {
			continueParsingParameters = parseLineLabelName(&currentCharIterator, i);
		}
	}

	if (continueParsingParameters){
		cout << "\t\t\t[IFA]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
		globalNumErrors++;
	}

	return;
}

// parses through a line one character at a time, manages the global member variable associated with the parameterNumber, and returns whether or not there are any more parameters to parse
bool tIFA::parseVariable(int *currentCharIterator, int parameterNumber){
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
		// cout << "\t\t\t[IFA]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[IFA]: Current Variable Name: " << currentVariableName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IFA]: Invalid Syntax: Variable names can not start with a digit: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[IFA]: Current Variable Name: " << currentVariableName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IFA]: Invalid Syntax: Variables can not start with an underscore: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			currentVariableName += currentChar;
			numCharactersInVarName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t\t[IFA]: Current Variable Name: " << currentVariableName << endl;
		}

		// End Parenthesis
		if (currentChar == ')'){
			if (numCharactersInVarName == 0){
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting a Variable Name before ) " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			if (parameterNumber != 0){
				cout << "\t\t\t[IFA]: Invalid Syntax: Not Expecting Another ) " << globalCurrentLine << endl;
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
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting a Variable Name before , " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
				isNotLastParameter = true;
			}
			if (parameterNumber == 0){
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting End Parenthesis: " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			if (parameterNumber == 3){
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
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
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting a Variable Name before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			if (parameterNumber < 3){
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting More Variables before End of Line: " << globalCurrentLine << endl;
				isValidVariableName = false;
				globalNumErrors++;
			}
			continueParsingVariable = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[IFA]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidVariableName){
		switch (parameterNumber){
			case 0:
				conditionVariable.variableName = currentVariableName;
				break;
			case 1:
				LineLabel1.variableName = currentVariableName;
				break;
			case 2:
				LineLabel2.variableName = currentVariableName;
				break;
			case 3:
				LineLabel3.variableName = currentVariableName;
				break;
		}
	}

	return isNotLastParameter;
}

// parses through a line one character at a time, sets global Line Label Names, and returns whether or not there are any more variables to parse
bool tIFA::parseLineLabelName(int *currentCharIterator, int parameterNumber){
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
		// cout << "\t\t[IFA]: Current Character: " << currentChar << endl;

		// Alphabetic
		if (isalpha(currentChar)){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[IFA]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Digit
		if (isdigit(currentChar)){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[IFA]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Underscore
		if (currentChar == '_'){
			currentLineLabelName += currentChar;
			numCharactersInLabelName++;
			(*currentCharIterator)++;
			caseFound = true;
			// cout << "\t\t[IFA]: Current Line Label Name: " << currentLineLabelName << endl;
		}

		// Comma
		if (currentChar == ','){
			if (numCharactersInLabelName == 0){
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting at least one character before ,: " << globalCurrentLine << endl;
				isValidLineLabel = false;
				globalNumErrors++;
			}
			if (parameterNumber == 3){
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting End Of Line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isNotLastParameter = false;
			}
			continueParsingLabel = false;
			(*currentCharIterator)++;
			caseFound = true;
		}

		// End Of Line
		if (currentChar == '\0'){
			if (numCharactersInLabelName == 0){
				cout << "\t\t\t[IFA]: Invalid Syntax: Expecting line label before end of line: " << globalCurrentLine << endl;
				globalNumErrors++;
				isValidLineLabel = false;
			}
			continueParsingLabel = false;
			isNotLastParameter = false;
			caseFound = true;
		}

		if (!caseFound){
			cout << "\t\t\t[IFA]: Invalid Syntax: Unknown Character in line: " << globalCurrentLine << endl;
			(*currentCharIterator)++;
			globalNumErrors++;
		}
	}

	// Assign to Global Parameter Name
	if (isValidLineLabel){
		switch (parameterNumber){
			case 0:
				conditionVariable.variableName = currentLineLabelName;
				break;
			case 1:
				LineLabel1.variableName = currentLineLabelName;
				break;
			case 2:
				LineLabel2.variableName = currentLineLabelName;
				break;
			case 3:
				LineLabel3.variableName = currentLineLabelName;
				break;
		}
	}

	return isNotLastParameter;
}

// tells the memoryManager to conditionally add the global memoryTableObject arguments to the symbol table
void tIFA::syncVariablesToSymbolTable(){
	// cout << "\t\t[IFA]: Attempting to Add Arguments to Lookup Table...\n";

	conditionVariable.isArray = false;
	conditionVariable.size = 1;
	(*currentMemoryManager).manageMemoryTableObject(&conditionVariable);

	// Line Label 1
	LineLabel1.memoryLocation = (*currentLineManager).getObjLineNumber(LineLabel1.variableName);
	if (LineLabel1.memoryLocation == NOT_FOUND_IN_ARRAY){
		cout << "\t\t\t[IFA]: Syntax Error: Undeclared Line Label: " << globalCurrentLine << endl;
	}

	// Line Label 2
	LineLabel2.memoryLocation = (*currentLineManager).getObjLineNumber(LineLabel2.variableName);
	if (LineLabel2.memoryLocation == NOT_FOUND_IN_ARRAY){
		cout << "\t\t\t[IFA]: Syntax Error: Undeclared Line Label: " << globalCurrentLine << endl;
	}

	// Line Label 3
	LineLabel3.memoryLocation = (*currentLineManager).getObjLineNumber(LineLabel3.variableName);
	if (LineLabel3.memoryLocation == NOT_FOUND_IN_ARRAY){
		cout << "\t\t\t[IFA]: Syntax Error: Undeclared Line Label: " << globalCurrentLine << endl;
	}



	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void tIFA::outputIFACommand(){
	unsigned int currentMemoryLocation;
	unsigned int size;
	// cout << "\t\t[IFA]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeStringToObj(IFA_OP_CODE);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(conditionVariable.memoryLocation);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(LineLabel1.memoryLocation);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(LineLabel2.memoryLocation);
	(*currentFileManager).writeCharToObj(' ');

	(*currentFileManager).writeNumToObj(LineLabel3.memoryLocation);
	(*currentFileManager).writeCharToObj('\n');

	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */