/*
  ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 10/29/17

	Description: 	Implementation for SymbolTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class


  ==============================================================================
*/

#include "SymbolTable.h"


/* ==============================================================================
Constructor & Destructor
============================================================================== */

SymbolTable::SymbolTable(){
	numObjectsInArray = 0;
	numUsedMemory = 0;
	cout << "\t\t[SymbolTable]: Initialized SymbolTable\n";
	return;
}

SymbolTable::~SymbolTable(){
	cout << "\t\t[SymbolTable]: Shutdown SymbolTable\n";
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// if the variable doesn't already exist, calls insertInto(), and regardless sets the memoryLocation for the currentMemoryObject
void SymbolTable::manageMemoryTableObject(memoryTableObject *currentMemoryObject){
	// cout << "\t\t\t[SymbolTable]: Managing Memory for " << (*currentMemoryObject).variableName <<endl;

	if (currentlyExists((*currentMemoryObject).variableName)){
		(*currentMemoryObject).memoryLocation = lookup((*currentMemoryObject).variableName);
	}
	else {
		(*currentMemoryObject).memoryLocation = insertInto(currentMemoryObject);
	}


	return;
}

// sets coreMemory boolean regarding the result of compilation
void SymbolTable::setCompilationResult(bool completedSuccessfully){
	symbolTableArray[INDEX_COMPILATION_RESULT].variableName = "CompilationSuccessFlag";
	symbolTableArray[INDEX_COMPILATION_RESULT].booleanValue = completedSuccessfully;
	symbolTableArray[INDEX_COMPILATION_RESULT].memoryLocation = 1000;
	symbolTableArray[INDEX_COMPILATION_RESULT].isArray = false;
	symbolTableArray[INDEX_COMPILATION_RESULT].size = 1;
}

/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// iterates through the SymbolTable and prints the variableName & memoryLocation
void SymbolTable::printSymbolTable(){
	cout << "\t\t\t[SymbolTable]: Symbol Table currently has " << numObjectsInArray << " variables, which take up " << numUsedMemory << " spots in memory\n";

	for (int i = 0; i < numObjectsInArray; i++){
		cout << "\t\t\t\t" << i << ":\tName: " << symbolTableArray[i].variableName << "\tLocation: " << symbolTableArray[i].memoryLocation;
		if (symbolTableArray[i].isArray){
			cout << "\tSize: " << symbolTableArray[i].size;
		}
		cout << endl;
	}

	return;
}

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
	int index = getSymbolTableIndex(variableName);
	return symbolTableArray[index].memoryLocation;
}

// returns the lookup table index for the variable
int SymbolTable::getSymbolTableIndex(string variableName){
 	string currentVariableName;

 	for (int i = 0; i < numObjectsInArray; i++){
 		currentVariableName = symbolTableArray[i].variableName;

		if (variableName == currentVariableName){
			return i;
		}
	}

	return NOT_FOUND_IN_ARRAY;
 }



/* ==============================================================================
	Protected Accessor Methods
============================================================================== */

// adds the variable to the table (HAVE NOT YET IMPLEMENTED SORT)
int SymbolTable::insertInto(memoryTableObject *currentMemoryObject){
	// cout << "\t\t\t[SymbolTable]: Adding " << (*currentMemoryObject).variableName << "  to Memory Table Object\n";
	int newMemoryLocation = numUsedMemory;

	symbolTableArray[numObjectsInArray].variableName = (*currentMemoryObject).variableName;
	symbolTableArray[numObjectsInArray].memoryLocation = newMemoryLocation;
	symbolTableArray[numObjectsInArray].isArray = (*currentMemoryObject).isArray;
	symbolTableArray[numObjectsInArray].size = (*currentMemoryObject).size;

	numObjectsInArray++;
	numUsedMemory += (*currentMemoryObject).size;

	// printSymbolTable();

	return newMemoryLocation;
}