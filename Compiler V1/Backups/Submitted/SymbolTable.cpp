/*
  ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 09/26/17

	Description: 	Implementation for SymbolTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
					NOT YET Implemented as an alphabetically sorted array according to character ASCII value

  ==============================================================================
*/

#include "SymbolTable.h"


/* ==============================================================================
Constructor & Destructor
============================================================================== */

SymbolTable::SymbolTable(){
	numObjectsInArray = 0;
	totalMemorySpacesUsed = 0;
}

void SymbolTable::SymbolTable_shutdown(){
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
		(*currentMemoryObject).memoryLocation = insertInto((*currentMemoryObject).variableName);
	}


	return;
}

// if the variable exists, removes it from the table (NOT YET IMPLEMENTED)
void SymbolTable::removeVariable(string variableName){

}



/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// iterates through the SymbolTable and prints the variableName & memoryLocation
void SymbolTable::printSymbolTable(){
	cout << "\t\t\t[SymbolTable]: Lookup Table currently using " << totalMemorySpacesUsed << " memory spaces\n";

	for (int i = 0; i < numObjectsInArray; i++){
		cout << "\t\t\t\tName: " << sortedTableArray[i].variableName << "\tLocation: " << sortedTableArray[i].memoryLocation << endl;
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
	return sortedTableArray[index].memoryLocation;
}

// returns the lookup table index for the variable
int SymbolTable::getSymbolTableIndex(string variableName){
 	string currentVariableName;

 	for (int i = 0; i < numObjectsInArray; i++){
 		currentVariableName = sortedTableArray[i].variableName;

		if (variableName == currentVariableName){
			return i;
		}
	}

	return NOT_FOUND_IN_ARRAY;
 }



/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// adds the variable to the table (HAVE NOT YET IMPLEMENTED SORT)
int SymbolTable::insertInto(string variableName){
	// cout << "\t\t\t[SymbolTable]: Adding " << variableName << "  to Memory Table Object\n";
	int newMemoryLocation;
	newMemoryLocation = numObjectsInArray;

	sortedTableArray[numObjectsInArray].variableName = variableName;
	sortedTableArray[numObjectsInArray].memoryLocation = newMemoryLocation;

	numObjectsInArray++;
	totalMemorySpacesUsed++;

	return newMemoryLocation;
}