/*
  ==============================================================================

	File: LiteralTable.cpp
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Implementation for LiteralTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- manages literal phrases and their associated virtual memory locations
		- calls on the FileManager to output .literal file

  ==============================================================================
*/

#include "LiteralTable.h"


/* ==============================================================================
Constructor & Destructor
============================================================================== */

LiteralTable::LiteralTable(){
	numObjectsInArray = 0;
	// cout << "\t\t[LiteralTable]: Initialized LiteralTable\n";
	return;
}

LiteralTable::~LiteralTable(){
	// cout << "\t\t[LiteralTable]: Shutdown LiteralTable\n";
	return;
}

// sets the global currentFileManager to point to the Compiler's parentFileManager
void LiteralTable::linkWithParentFileManager(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// adds a new line of core to the LiteralTable
void LiteralTable::loadLine(string newLine){
	// cout << "\t\t\t[LiteralTable]: Adding " << newLine << " to Core Memory Manager\n";

	if (newLine[0] != '\0'){
		globalLiteralArray[globalSizeLiteralArray] = newLine;
		globalSizeLiteralArray++;
	}

	return;
}

// Sets the RValue at memoryLocation to newValue - For Executor
void LiteralTable::setValue(int memoryLocation, string newValue){
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_LITERALS)){
		globalLiteralArray[memoryLocation] = newValue;
		// cout << "\t\t[LiteralTable]: Set RValue of location " << memoryLocation << " to \""  << globalLiteralArray[memoryLocation] << "\"\n";
	}
	return;
}

// if the Literal doesn't already exist, calls insertInto(), and regardless sets the memoryLocation for the currentLiteralObject
void LiteralTable::manageLiteralObject(literalTableObject *currentLiteralObject){

	// Managing a Literal String without a Variable Name
	if ((*currentLiteralObject).variableName == UNNAMED_LITERAL){
		// cout << "\t\t\t[LiteralTable]: Managing Memory for " << (*currentLiteralObject).literalString << endl;
		if (currentlyExists_Literal((*currentLiteralObject).literalString)){
			(*currentLiteralObject).memoryLocation = lookup_Literal((*currentLiteralObject).literalString);
		}
		else {
			(*currentLiteralObject).memoryLocation = insertInto(currentLiteralObject);
		}
	}
	// Managing a Variable Name without a Literal String
	else {
		// cout << "\t\t\t[LiteralTable]: Managing Memory for " << (*currentLiteralObject).variableName << endl;
		if (currentlyExists_Variable((*currentLiteralObject).variableName)){
			(*currentLiteralObject).memoryLocation = lookup((*currentLiteralObject).variableName);
		}
		else {
			(*currentLiteralObject).memoryLocation = insertInto(currentLiteralObject);
		}
	}

	return;
}

/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// returns true if the variable already exists in the LiteralTable
bool LiteralTable::currentlyExists_Variable(string currentVariableName){
	bool existsInTable;
	int memoryLocation = getLiteralTableIndex(currentVariableName);
	if (memoryLocation == NOT_FOUND_IN_ARRAY){
		existsInTable = false;
	}
	else {
		existsInTable = true;
	}

	return existsInTable;
}

// returns true if the literal already exists in the LiteralTable
bool LiteralTable::currentlyExists_Literal(string literalToFind){
	bool existsInTable = false;
 	string currentLiteral;

 	for (int i = 0; i < numObjectsInArray; i++){
 		currentLiteral = LiteralTableArray[i].literalString;

 		// cout << "\t\t\t[LiteralTable]: Comparing table item " << i <<": " << currentLiteral << " to literalToFind " << literalToFind << endl;
		if (currentLiteral == literalToFind){
			existsInTable = true;
		}
	}

	return existsInTable;
}

// returns the rvalue pointed to by the memoryLocation
string LiteralTable::getValue(int memoryLocation){
	string currentValue;
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_LITERALS)){
		currentValue = globalLiteralArray[memoryLocation];
	}
	else {
		currentValue = "Failed to get literal: invalid memory location";
	}
	return currentValue;
}

// returns the memoryLocation for the currentVariableName
int LiteralTable::lookup(string currentVariableName){
	int index = getLiteralTableIndex(currentVariableName);
	return LiteralTableArray[index].memoryLocation;
}

// returns the memoryLocation for the literalToFind
int LiteralTable::lookup_Literal(string literalToFind){
	int index = NOT_FOUND_IN_ARRAY;
 	string currentLiteral;

 	for (int i = 0; i < numObjectsInArray; i++){
 		currentLiteral = LiteralTableArray[i].literalString;

 		// cout << "\t\t\t[LiteralTable]: Comparing table item " << i <<": " << currentLiteral << " to literalToFind " << literalToFind << endl;
		if (currentLiteral == literalToFind){
			index = i;
		}
	}

	return index;
}

// returns the index for the literal
int LiteralTable::getLiteralTableIndex(string literalVariableToFind){
	int index = NOT_FOUND_IN_ARRAY;
 	string currentLiteral;

 	for (int i = 0; i < numObjectsInArray; i++){
 		currentLiteral = LiteralTableArray[i].variableName;

 		// cout << "\t\t\t[LiteralTable]: Comparing table item " << i <<": " << currentLiteral << " to " << literalVariableToFind << endl;
		if (currentLiteral == literalVariableToFind){
			index = i;
		}
	}

	return index;
 }

// iterates through the LiteralTable and prints the variableName & memoryLocation
void LiteralTable::ePrintLiteralTable(){
	cout << "\t\t\t[LiteralTable]: Literal Table currently has " << globalSizeLiteralArray << " literals\n";

	for (int i = 0; i < globalSizeLiteralArray; i++){
		cout << "\t\t\t\t" << i << ": " << globalLiteralArray[i] << endl;
	}

	return;
}

// iterates through the LiteralTable and prints the variableName & memoryLocation
void LiteralTable::printLiteralTable(){
	cout << "\t\t\t[LiteralTable]: Literal Table currently has " << numObjectsInArray << " literals\n";

	for (int i = 0; i < numObjectsInArray; i++){
		cout << "\t\t\t\t" << i << ": Name: " << LiteralTableArray[i].variableName << "\tLiteral: \"" << LiteralTableArray[i].literalString << "\"\n";
	}

	return;
}

// iterates through the LiteralTable and outputs the literalString & memoryLocation to .literal file
void LiteralTable::outputLiteralFile(){
	if (numObjectsInArray > 0) {
		// cout << "\t\t\t[LiteralTable]: Writing .literal file...\n";
		for (int i = 0; i < numObjectsInArray; i++){
			// (*currentFileManager).writeStringToLiteral(LiteralTableArray[i].variableName);
			// (*currentFileManager).writeStringToLiteral("\t");
			(*currentFileManager).writeStringToLiteral(LiteralTableArray[i].literalString);
			(*currentFileManager).writeStringToLiteral("\n");
		}
	}
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// adds the literal object to the table
int LiteralTable::insertInto(literalTableObject *currentMemoryObject){
	// cout << "\t\t\t[LiteralTable]: Adding Literal Object to LiteralTable\n";
	// cout << "\t\t\t\tName: " << (*currentMemoryObject).variableName << "\tLiteral: \"" << (*currentMemoryObject).literalString << "\"\n";
	int newMemoryLocation = numObjectsInArray;

	LiteralTableArray[numObjectsInArray].variableName = (*currentMemoryObject).variableName;
	LiteralTableArray[numObjectsInArray].literalString = (*currentMemoryObject).literalString;
	LiteralTableArray[numObjectsInArray].memoryLocation = newMemoryLocation;

	numObjectsInArray++;

	return newMemoryLocation;
}