/* ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 10/30/17

	Description: 	Implementation for SymbolTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- manages IDs (variables or Constants) and their associated values and virtual memory locations
		- sets all initial varNames to _NA and sets the values to 0.123456789
		- coreMemoryArray[1000] = (bool) failedCompilation; (0 = success, 1 = failed)
		- calls on the FileManager to output .core file

============================================================================== */

#include "SymbolTable.h"

/* ==============================================================================
Constructor & Destructor
============================================================================== */

SymbolTable::SymbolTable(){
	numObjectsInArray = 0;
	for (int i = 0; i < MAX_NUM_VARIABLES; i++){
		symbolTableArray[i].variableName = UNDECLARED_VALUE;
		symbolTableArray[i].value = UNDEFINED_VALUE;
	}
	// cout << "\t\t[SymbolTable]: Initialized SymbolTable\n";
	return;
}

SymbolTable::~SymbolTable(){
	// cout << "\t\t[SymbolTable]: Shutdown SymbolTable\n";
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// if the variable doesn't already exist, calls insertInto(), and regardless returns the index for the currentMemoryObject
void SymbolTable::manageMemoryTableObject(memoryTableObject *currentMemoryObject){
	// cout << "\t\t\t[SymbolTable]: Managing Memory for " << (*currentMemoryObject).variableName <<endl;

	int locationInMemory = lookup((*currentMemoryObject).variableName);

	if (locationInMemory == NOT_FOUND_IN_ARRAY){
		(*currentMemoryObject).memoryLocation = insertInto(currentMemoryObject);
	}
	else {
		(*currentMemoryObject).memoryLocation = locationInMemory;
	}

	return;
}

// sets coreMemory boolean regarding the result of compilation
void SymbolTable::setCompilationResult(bool completedSuccessfully){
	symbolTableArray[INDEX_COMPILATION_RESULT].variableName = "CompilationFailedFlag";
	symbolTableArray[INDEX_COMPILATION_RESULT].value = completedSuccessfully;
	symbolTableArray[INDEX_COMPILATION_RESULT].memoryLocation = 1000;
	symbolTableArray[INDEX_COMPILATION_RESULT].isArray = false;
	symbolTableArray[INDEX_COMPILATION_RESULT].size = 1;
}

// sets the global currentFileManager to point to the Compiler's parentFileManager
void SymbolTable::linkWithParentFileManager(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// returns true if the variable already exists in the SymbolTable
bool SymbolTable::currentlyExists(string variableName){
	bool existsInTable;
	int memoryLocation = getSymbolTableIndex(variableName);
	if (memoryLocation == NOT_FOUND_IN_ARRAY){
		existsInTable = false;
	}
	else {
		existsInTable = true;
	}

	return existsInTable;
}

// returns the memoryLocation for the variable
int SymbolTable::lookup(string variableName){
	return getSymbolTableIndex(variableName);
}

// returns the lookup table index for the variable
int SymbolTable::getSymbolTableIndex(string variableNameToGet){
 	string currentVariableName;

 	for (int i = 0; i < numObjectsInArray; i++){
 		currentVariableName = symbolTableArray[i].variableName;

		if (variableNameToGet == currentVariableName){
			// cout << "\t\t\t[SymbolTable]: Found " << currentVariableName << " at location " << i << endl;
			return i;
		}
	}

	return NOT_FOUND_IN_ARRAY;
}

// iterates through the SymbolTable and prints the variableName & memoryLocation
void SymbolTable::printSymbolTable(){
	cout << "\t\t\t[SymbolTable]: Symbol Table currently has " << numObjectsInArray << " declared locations\n";

	for (int i = 0; i < numObjectsInArray; i++){
		cout << "\t\t\t\t" << i << ":\t" << symbolTableArray[i].variableName;
		if (symbolTableArray[i].isArray){
			cout << "\tSize: " << symbolTableArray[i].size;
		}
		cout << endl;
	}

	cout << "\t\t\t\t" << INDEX_COMPILATION_RESULT << ":\t" << symbolTableArray[INDEX_COMPILATION_RESULT].variableName << ": " << symbolTableArray[INDEX_COMPILATION_RESULT].value << endl;

	return;
}

// iterates through the SymbolTable and outputs the variableName & memoryLocation to .core file
void SymbolTable::outputCoreFile(){
	cout << "\t\t\t[SymbolTable]: Writing .core file...\n";
	for (int i = 0; i < MAX_NUM_VARIABLES; i++){
		// cout << "\t\t\t[SymbolTable]: Outputting data for " << symbolTableArray[i].variableName << endl;;
		(*currentFileManager).writeStringToCore(symbolTableArray[i].variableName);
		(*currentFileManager).writeStringToCore("\t");
		(*currentFileManager).writeNumToCore(symbolTableArray[i].value);
		(*currentFileManager).writeStringToCore("\n");
	}
	return;
}

// takes in currentString, sets the numberAsFloat, and returns if successful (from https://stackoverflow.com/questions/3825392/string-to-float-conversion)
bool SymbolTable::convertToFloat(string currentString, float& numberAsFloat){
    std::istringstream i(currentString);

    if (!(i >> numberAsFloat)) {
    	return false;
    }

    return true;
}

/* ==============================================================================
	Protected Manipulator Methods
============================================================================== */

// adds the variable to the table and returns the index
int SymbolTable::insertInto(memoryTableObject *currentMemoryObject){
	// cout << "\t\t\t[SymbolTable]: Adding " << (*currentMemoryObject).variableName << "  to Memory Table Object\n";
	int firstMemoryLocation = numObjectsInArray;

	if ((*currentMemoryObject).isArray) {
		for (int i = 0; i < (*currentMemoryObject).size; i++){
			symbolTableArray[numObjectsInArray].variableName = (*currentMemoryObject).variableName;
			numObjectsInArray++;
		}
	}
	else {
		if ((*currentMemoryObject).isConstant){
			symbolTableArray[numObjectsInArray].isConstant = true;

			string currentVariableName = (*currentMemoryObject).variableName;
			float numAsFloat;
			if (convertToFloat(currentVariableName, numAsFloat)){
				symbolTableArray[numObjectsInArray].value = numAsFloat;
			}
		}
		symbolTableArray[numObjectsInArray].variableName = (*currentMemoryObject).variableName;
		numObjectsInArray++;
	}

	// printSymbolTable();

	return firstMemoryLocation;
}