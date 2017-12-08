/* ==============================================================================

	File: CoreMemory.cpp
	Author: Brendan Thompson
	Updated: 12/07/17

	Description: 	Implementation for CoreMemory for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- manages IDs (variables or Constants) and their associated values and virtual memory locations
		- Manages array dimensions for range checking

============================================================================== */

#include "CoreMemory.h"

/* ==============================================================================
Constructor & Destructor
============================================================================== */

CoreMemory::CoreMemory(){
	globalSizeCoreMemory = 0;
	globalNumArrayDimension = 0;
	checkRangesFlag = false;
	useZeroFlag = false;
	// cout << "\t\t[CoreMemory]: Initialized CoreMemory\n";
	return;
}

CoreMemory::~CoreMemory(){
	// cout << "\t\t[CoreMemory]: Shutdown CoreMemory\n";
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// adds a new line of core to the CoreMemory
void CoreMemory::loadLine(string newLine){
	// cout << "\t\t\t[Core Memory]: Adding " << newLine << " to Core Memory Manager\n";
	if (newLine[0] != '\0'){
		globalCoreMemoryArray[globalSizeCoreMemory] = newLine;
		globalSizeCoreMemory++;
	}
	return;
}

// Sets the RValue at memoryLocation to newValue
void CoreMemory::setValue(int memoryLocation, string newValue){
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_VARIABLES)){
		globalCoreMemoryArray[memoryLocation] = newValue;
		// cout << "\t\t[Core Memory]: Set RValue of location " << memoryLocation << " to \""  << globalCoreMemoryArray[memoryLocation] << "\"\n";
	}
	return;
}

// Sets the RValue at memoryLocation to newValue
void CoreMemory::setValue(int memoryLocation, double newValue){
	string newValue_string;
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_VARIABLES)){
		newValue_string = std::to_string(newValue);
		globalCoreMemoryArray[memoryLocation] = newValue_string;
		// cout << "\t\t[Core Memory]: Set RValue of location " << memoryLocation << " to \""  << globalCoreMemoryArray[memoryLocation] << "\"\n";
	}
	return;
}

// Sets the RValue of the destinationAddress to the RValue of the sourceAddress
void CoreMemory::deepCopy(int destinationAddress, int sourceAddress){
	globalCoreMemoryArray[destinationAddress] = globalCoreMemoryArray[sourceAddress];
	return;
}

// Adds a new array to the globalArrayofArrayDimensions
void CoreMemory::addNewArray(int memoryLocationOfNewArray, int sizeOfNewArray){
	if (globalNumArrayDimension < MAX_NUM_VARIABLES){
		globalArrayofArrayDimensions[globalNumArrayDimension].memoryLocation = memoryLocationOfNewArray;
		globalArrayofArrayDimensions[globalNumArrayDimension].isArray = true;
		globalArrayofArrayDimensions[globalNumArrayDimension].size = sizeOfNewArray;
		globalNumArrayDimension++;
	}
	return;
}

// sets the flag to true
void CoreMemory::turnOnRangeCheckingFlag(){
	checkRangesFlag = true;
	return;
}

// sets the flag to true
void CoreMemory::turnOnZeroForUndefinedFlag(){
	useZeroFlag = true;
	return;
}

/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// returns the value at the specified memoryLocation
string CoreMemory::getValue(int memoryLocation){
	string currentValue;
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_VARIABLES)){
		currentValue = globalCoreMemoryArray[memoryLocation];
	}
	else {
		currentValue = "failed to get value: invalid memory location";
	}

	if (useZeroFlag){
		// cout << "\t\t\t[Core Memory]: Current value is " << currentValue << endl;
		if (currentValue == "0.12345679"){
			currentValue = "0";
		}
	}
	return currentValue;
}

// returns the value at the specified memoryLocation - For Executor
double CoreMemory::getValueAsDouble(int memoryLocation){
	string currentValue_string;
	double currentValue_double;
	if ((memoryLocation >= 0) && (memoryLocation < MAX_NUM_VARIABLES)){
		currentValue_string = globalCoreMemoryArray[memoryLocation];
	}
	else {
		currentValue_string = "failed to get value: invalid memory location";
	}

	std::stringstream str0(currentValue_string);
	str0 >> currentValue_double;

	if (useZeroFlag){
		// cout << "\t\t\t[Core Memory]: Current value is " << currentValue_double << endl;
		if (currentValue_double == UNDEFINED_VALUE){
			currentValue_double = 0;
		}
	}

	return currentValue_double;
}

// Returns true if the start & end indexes are within the range of the array
bool CoreMemory::rangeChecksOut(int arrayMemoryLocation, int startIndex, int endIndex){
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

	if (checkRangesFlag){
		if ((startIndex < 0) || (endIndex >= sizeOfArray)){
			withinRange = false;
		}
		else {
			withinRange = true;
		}
	}
	else {
		withinRange = true;
	}

	return withinRange;
}

// prints out the Rvalue for every value in CoreMemory
void CoreMemory::printCoreMemory(){
	cout << "\t\t\t[Core Memory]: Core Memory currently has " << globalSizeCoreMemory << " declared locations\n";
	for (int i = 0; i < globalSizeCoreMemory; i++){
		cout << "\t\t\t\t" << i << ": " << globalCoreMemoryArray[i] << endl;
	}
	return;
}

// prints out the Rvalue for every memoryLocation in CoreMemory from startIndex to endIndex
void CoreMemory::printCoreMemory(int startIndex, int endIndex){
	if ((startIndex < endIndex) && (startIndex >= 0) && (endIndex <= MAX_NUM_VARIABLES)){
		for (int i = startIndex; i <= endIndex; i++){
			cout << "\t\t\t\t" << i << ": " << globalCoreMemoryArray[i] << endl;
		}
	}
	return;
}

// prints out the globalArrayofArrayDimensions
// void CoreMemory::printArrayDimension(){
	// return;
// }

// takes in currentString, sets the numberAsDouble, and returns if successful (from https://stackoverflow.com/questions/3825392/string-to-Double-conversion)
// bool CoreMemory::convertToDouble(string currentString, double& numberAsDouble){
//     std::istringstream i(currentString);
//     if (!(i >> numberAsDouble)) {
//     	return false;
//     }
//     return true;
// }