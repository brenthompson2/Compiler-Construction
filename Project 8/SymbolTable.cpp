/* ==============================================================================

	File: SymbolTable.cpp
	Author: Brendan Thompson
	Updated: 11/29/17

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
	globalSizeCoreMemory = 0;
	globalNumArrayDimension = 0;
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

// sets the global currentFileManager to point to the Compiler's parentFileManager
void SymbolTable::linkWithParentFileManager(FileManager *parentFileManager){
	currentFileManager = parentFileManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// adds a new line of core to the SymbolTable
void SymbolTable::loadLine(string newLine){
	// cout << "\t\t\t[Core Memory]: Adding " << newLine << " to Core Memory Manager\n";

	if (newLine[0] != '\0'){
		globalCoreMemoryArray[globalSizeCoreMemory] = newLine;
		globalSizeCoreMemory++;
	}

	return;
}

// Sets the RValue at memoryLocation to newValue
void SymbolTable::setValue(int memoryLocation, string newValue){
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_VARIABLES)){
		globalCoreMemoryArray[memoryLocation] = newValue;
		// cout << "\t\t[Core Memory]: Set RValue of location " << memoryLocation << " to \""  << globalCoreMemoryArray[memoryLocation] << "\"\n";
	}
	return;
}

// Sets the RValue of the destinationAddress to the RValue of the sourceAddress
void SymbolTable::deepCopy(int destinationAddress, int sourceAddress){
	globalCoreMemoryArray[destinationAddress] = globalCoreMemoryArray[sourceAddress];
	return;
}

// returns the value at the specified memoryLocation
string SymbolTable::getValue(int memoryLocation){
	string currentValue;
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_VARIABLES)){
		currentValue = globalCoreMemoryArray[memoryLocation];
	}
	else {
		currentValue = "failed to get value: invalid memory location";
	}
	return currentValue;
}

// Adds a new array to the globalArrayofArrayDimensions
void SymbolTable::addNewArray(int memoryLocationOfNewArray, int sizeOfNewArray){
	if (globalNumArrayDimension < MAX_NUM_VARIABLES){
		globalArrayofArrayDimensions[globalNumArrayDimension].memoryLocation = memoryLocationOfNewArray;
		globalArrayofArrayDimensions[globalNumArrayDimension].isArray = true;
		globalArrayofArrayDimensions[globalNumArrayDimension].size = sizeOfNewArray;
		globalNumArrayDimension++;
	}
}

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

// Returns true if the start & end indexes are within the range of the array
bool SymbolTable::rangeChecksOut(int arrayMemoryLocation, int startIndex, int endIndex){
	int sizeOfArray;
	bool foundArray = false;
	bool withinRange;

	// Find The Correct Array
	for (int i = 0; ((i < globalNumArrayDimension) && !(foundArray)); i++){
		if (arrayMemoryLocation == globalArrayofArrayDimensions[i].memoryLocation){
			foundArray = true;
			sizeOfArray = globalArrayofArrayDimensions[i].size;
			if (!(globalArrayofArrayDimensions[i].isArray)){
				cout << "\t\t\t[Core Memory]: Warning: Attempting to access a memory location by index that isn't an array\n";
				sizeOfArray = 0;
			}
		}
	}

	if ((startIndex >= sizeOfArray) || (endIndex >= sizeOfArray)){
		withinRange = false;
	}
	else {
		withinRange = true;
	}

	return withinRange;
}

// prints out the value for every value in CoreMemory
void SymbolTable::printCoreMemory(){
	cout << "\t\t\t[Core Memory]: Core Memory currently has " << globalSizeCoreMemory << " declared locations\n";
	for (int i = 0; i < globalSizeCoreMemory; i++){
		cout << "\t\t\t\t" << i << ": " << globalCoreMemoryArray[i] << endl;
	}
}

// prints out the Rvalue for every memoryLocation in CoreMemory from startIndex to endIndex
void SymbolTable::printCoreMemory(int startIndex, int endIndex){
	if ((startIndex < endIndex) && (startIndex >= 0) && (endIndex <= MAX_NUM_VARIABLES)){
		for (int i = startIndex; i <= endIndex; i++){
			cout << "\t\t\t\t" << i << ": " << globalCoreMemoryArray[i] << endl;
		}
	}
}

// prints out the globalArrayofArrayDimensions
void SymbolTable::printArrayDimension(){

}

// iterates through the SymbolTable and prints the variableName & memoryLocation
void SymbolTable::printSymbolTable(){
	cout << "\t\t\t[SymbolTable]: Symbol Table currently has " << numObjectsInArray << " declared locations\n";

	for (int i = 0; i < numObjectsInArray; i++){
		cout << "\t\t\t\t" << i << ":\t" << symbolTableArray[i].value;
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
	printSymbolTable();

	cout << "\t\t\t[SymbolTable]: Writing .core file...\n";
	for (int i = 0; i < MAX_NUM_VARIABLES; i++){
		// cout << "\t\t\t" << i << ": " << symbolTableArray[i].value << endl;;
		// (*currentFileManager).writeStringToCore(symbolTableArray[i].variableName);
		// (*currentFileManager).writeStringToCore("\t");
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