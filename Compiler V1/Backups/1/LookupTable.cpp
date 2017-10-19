/*
  ==============================================================================

	File: LookupTable.cpp
	Author: Brendan Thompson
	Updated: 09/25/17

	Description: 	Implementation for LookupTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
					Implemented as an alphabetically sorted array according to character ASCII value

  ==============================================================================
*/

#include "LookupTable.h"


/* ==============================================================================
Constructor & Destructor
============================================================================== */

LookupTable::LookupTable(){
	numObjectsInArray = 0;
}

void LookupTable::LookupTable_shutdown(){
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// if the variable doesn't already exist, the function adds the variable to the table in the appropriately sorted spot and assigns it a memory location
void LookupTable::manageMemoryTableObject(memoryTableObject *currentMemoryObject){
	cout << "\t\t\t[LookupTable]: Adding Memory Table Object\n";

	if (numObjectsInArray == 0){ // first variable to be added to array
		(*currentMemoryObject).memoryLocation = addVariable((*currentMemoryObject).variableName);
	}

	else {
		for (int i = 0; i < numObjectsInArray; i++){
			if (!currentlyExists((*currentMemoryObject).variableName)){
				(*currentMemoryObject).memoryLocation = addVariable((*currentMemoryObject).variableName);
			}
		}
	}
	return;
}

// if the variable exists, removes it from the table
void LookupTable::removeVariable(string variableName){

}



/* ==============================================================================
	Public Accessor Methods
============================================================================== */

void LookupTable::printLookupTable(){
	cout << "\t\t\t[LookupTable]: Lookup Table: \n";

	for (int i = 0; i < numObjectsInArray; i++){
		cout << "\t\t\t\tName: " << sortedTableArray[i].variableName << "\tLocation: " << sortedTableArray[i].memoryLocation << endl;
	}

	return;
}

// returns true if the variable already exists in the table
bool LookupTable::currentlyExists(string variableName){
	bool existsInTable;
	int memoryLocation = getLookupTableIndex(variableName);
	if (memoryLocation == NOT_FOUND_IN_ARRAY){
		existsInTable = false;
	}
	else {
		existsInTable = true;
	}

	return existsInTable;
}

// returns the memoryLocation for the variable
int LookupTable::getMemoryLocation(string variableName){

}

// returns the lookup table index for the variable
int LookupTable::getLookupTableIndex(string variableName){
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

// adds the variable to the table in the appropriately sorted spot and returns the memoryLocation
int LookupTable::addVariable(string variableName){
	int newMemoryLocation;
	newMemoryLocation = numObjectsInArray;

	sortedTableArray[numObjectsInArray].variableName = variableName;
	sortedTableArray[numObjectsInArray].memoryLocation = newMemoryLocation;

	numObjectsInArray++;

	return newMemoryLocation;
}