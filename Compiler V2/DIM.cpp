/*
  ==============================================================================

	File: DIM.cpp
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Implementation of Functions for processing DIM command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "DIM.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

DIM::DIM(){
	return;
}

DIM::~DIM(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to FileManager & SymbolTable with the parent's (compiler's) versions
void DIM::prepareDIM(FileManager *parentFileManager, SymbolTable *parentMemoryManager){
	currentFileManager = parentFileManager;
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
bool DIM::newDIM(string currentLine, int *numErrors){
	globalCurrentLine = currentLine;
	cout << "\t\t[DIM]: Compiling Line: " << globalCurrentLine << endl;

	numVariablesInArray = 0;
	globalNumErrors = 0;
	validSyntax = true;

	parseParameters();

	// printVariableArray();
	syncVariableArrayToSymbolTable();
	outpuDIMCommand();

	if (!validSyntax){
		cout << "\t\t[DIM]: Successfully completed DIM command with " << globalNumErrors << " errors\n";
	}

	*numErrors += globalNumErrors;
	return validSyntax;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// iterates through the variables passed to the command one character at a time and inserts them into variableArray
void DIM::parseParameters(){
	bool continueParsingParameters = true;
	bool continueParsingVariable = true;
	unsigned int currentLineIterator = 3;
	unsigned int numCharactersInVarName;

	while (continueParsingParameters){
		string currentArrayName = "";
		numCharactersInVarName = 0;
		continueParsingVariable = true;
		// cout << "\t\t[DIM]: Set Current Variable Name to: " << currentArrayName << endl;

		char currentChar = globalCurrentLine[currentLineIterator];
		// cout << "\t\t[DIM]: Current Character: " << currentChar << endl;

		while (continueParsingVariable){
			if (numVariablesInArray > 0){
				// cout << "\t\t[DIM]: numVariablesInArray: " << numVariablesInArray << endl;
				// cout << "\t\t[DIM]: Continue: " << continueParsingVariable << endl;
				// printVariableArray();
			}

			currentChar = globalCurrentLine[currentLineIterator];
			// cout << "\t\t[DIM]: Current Character: " << currentChar << endl;

			analyzeCharacter(currentChar, currentArrayName, numCharactersInVarName, &currentLineIterator, &continueParsingParameters, &continueParsingVariable);

			currentArrayName += currentChar;
			// cout << "\t\t[DIM]: Current Variable Name: " << currentArrayName << endl;
			currentLineIterator++;
			numCharactersInVarName++;
		}
	}

	return;
}

// analyzeCharacter =
	// changes the globalNumErrors
	// changes the index to the currentChar
	// manipulates the status of parsing given pointers to status information
void DIM::analyzeCharacter(char currentChar,
							string currentArrayName,
							unsigned int numCharactersInVarName, unsigned int *currentLineIterator,
							bool *continueParsingParameters, bool *continueParsingVariable){
	if(currentChar == '['){
		if (numCharactersInVarName == 0){
			// cout << "\t\t[DIM]: currentChar: " << currentChar << "numCharactersInVarName: " << numCharactersInVarName << endl;
			if (numVariablesInArray == 0){ // empty variable name and no variables in array
				cout << "\t\t[DIM]: Invalid Syntax: DIM Command requires at least one array name before [ : " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				globalNumErrors++;
			}
			else { // empty variable name but at least one variable in array
				cout << "\t\t[DIM]: Invalid Syntax: Expecting another array name before [ : " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				globalNumErrors++;
			}
		}
		else { // end of variable name
			// cout << "\t\t[DIM]: Found variable name: " << currentArrayName << endl;
			(*currentLineIterator)++;
			parseSize(currentArrayName, currentLineIterator, continueParsingParameters);

		}
		*continueParsingVariable = false;
	}

	if(currentChar == '\0'){
		if (numCharactersInVarName == 0){
			// cout << "\t\t[DIM]: currentChar: " << currentChar << "numCharactersInVarName: " << numCharactersInVarName << endl;
			if (numVariablesInArray == 0){ // empty variable name and no variables in array
				cout << "\t\t[DIM]: Invalid Syntax: DIM Command requires at least one variable before end of line: " << globalCurrentLine << endl;
				validSyntax = false;
				globalNumErrors++;
			}
			else { // empty variable name but at least one variable in array
				cout << "\t\t[DIM]: Invalid Syntax: Expecting another variable name before end of line: " << globalCurrentLine << endl;
				validSyntax = false;
				globalNumErrors++;
			}
		}
		else { // end of variable name
			// cout << "\t\t[DIM]: Found variable name: " << currentArrayName << endl;
			// cout << "\t\t[DIM]: Reached end of line\n";
			// printVariableArray();
		}
		*continueParsingParameters = false;
		*continueParsingVariable = false;
	}

	if(currentChar == ','){
		if (numCharactersInVarName == 0){
			// cout << "\t\t[DIM]: currentChar: " << currentChar << "numCharactersInVarName: " << numCharactersInVarName << endl;
			if (numVariablesInArray == 0){ // empty variable name and no variables in array
				cout << "\t\t[DIM]: Invalid Syntax: DIM Command requires at least one variable before ,: " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				globalNumErrors++;
			}
			else { // empty variable name but at least one variable in array
				cout << "\t\t[DIM]: Invalid Syntax: Expecting another variable name before ,: " << globalCurrentLine << endl;
				*continueParsingParameters = false;
				validSyntax = false;
				globalNumErrors++;
			}
		}
		else { // end of variable name
			// cout << "\t\t[DIM]: Found variable name: " << currentArrayName << endl;
			// printVariableArray();
			(*currentLineIterator)++;
		}
		*continueParsingVariable = false;
	}

	return;
}

// continues parsing down the line in order to get the size of the designated array
	// manipulates currentLineIterator and continueParsingParameters
	// calls addToVariableArray()
void DIM::parseSize(string currentArrayName, unsigned int *currentLineIterator, bool *continueParsingParameters){
	bool continueParsingSize = true;
	string currentSize = "";
	int numCharsInSize = 0;
	char currentChar;
	int finalSize = 0;

	// cout << "\t\t\t[DIM]: Parsing the size of Array " << currentArrayName << "...\n";


	while (continueParsingSize){

		currentChar = globalCurrentLine[*currentLineIterator];
		// cout << "\t\t\t[DIM]: Current Character: " << currentChar << endl;

		analyzeSize(currentChar, numCharsInSize, currentLineIterator, &continueParsingSize, continueParsingParameters);

		currentSize += currentChar;
		(*currentLineIterator)++;
		numCharsInSize++;
	}

	// string to int conversion method from https://stackoverflow.com/questions/6093414/convert-char-array-to-single-int
	std::stringstream str(currentSize);
	str >> finalSize;
	// cout << "\t\t[DIM]: Adding New Array to VariableArray: " << currentArrayName << "\t" << finalSize << endl;
	addToVariableArray(currentArrayName, finalSize);

	return;

}

// analyzeCharacter =
	// changes the globalNumErrors
	// changes currentLineIterator
	// manipulates the status of parsing given pointers to status information
void DIM::analyzeSize(char currentChar, unsigned int numCharsInSize, unsigned int *currentLineIterator, bool *continueParsingSize, bool *continueParsingParameters){

	// cout << "\t\t\t[DIM]: Analyzing the size character " << currentChar << "...\n";

	if(currentChar == ']'){
		if (numCharsInSize == 0){ // no size given
			// cout << "\t\t[DIM]: currentChar: " << currentChar << "numCharsInSize: " << numCharsInSize << endl;
			cout << "\t\t[DIM]: Invalid Syntax: DIM Command expects a size before ] : " << globalCurrentLine << endl;
			*continueParsingParameters = false;
			validSyntax = false;
			globalNumErrors++;
		}
		else { // end of size
			// cout << "\t\t[DIM]: Found variable size: " << currentArrayName << endl;
			// printVariableArray();
		}
		*continueParsingSize = false;
	}

	if(currentChar == '\0'){
		cout << "\t\t[DIM]: Invalid Syntax: DIM Command expected ] before end of line: " << globalCurrentLine << endl;
		validSyntax = false;
		globalNumErrors++;
		*continueParsingParameters = false;
		*continueParsingSize = false;
	}

	if(currentChar == ','){
		cout << "\t\t[DIM]: Invalid Syntax: DIM Command expected ] before , : " << globalCurrentLine << endl;
		validSyntax = false;
		globalNumErrors++;
		*continueParsingParameters = false;
		*continueParsingSize = false;
	}

	// cout << "\t\t\t[DIM]: Analyzed the size character " << currentChar << "\n";

	return;
}

// adds the currentArrayName to the variableArray and increments numVariablesInArray
void DIM::addToVariableArray(string currentArrayName, unsigned int currentArraySize){
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
void DIM::syncVariableArrayToSymbolTable(){
	// cout << "\t\t[DIM]: Attempting to Add Variable Array to Lookup Table...\n";

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentMemoryManager).manageMemoryTableObject(&variableArray[i]);
	}

	// (*currentMemoryManager).printSymbolTable();
	return;
}

// tells the FileManager to print the object code for the command, which includes the command op code and the variable memoryLocations
void DIM::outpuDIMCommand(){
	unsigned int currentMemoryLocation;
	unsigned int size;
	// cout << "\t\t[DIM]: Attempting to Print Object code to .obj...\n";

	(*currentFileManager).writeCharToObj(DIM_OP_CODE);

	for (int i = 0; i < numVariablesInArray; i++){
		(*currentFileManager).writeCharToObj(' ');
		currentMemoryLocation = (variableArray[i]).memoryLocation;
		(*currentFileManager).writeNumToObj(currentMemoryLocation);
		(*currentFileManager).writeCharToObj(' ');
		size = (variableArray[i]).size;
		(*currentFileManager).writeNumToObj(size);
	}

	(*currentFileManager).writeCharToObj('\n');
	return;
}


/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// prints the variableArray to the console
void DIM::printVariableArray(){
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


