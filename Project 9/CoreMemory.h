/* ==============================================================================

	File: CoreMemory.cpp
	Author: Brendan Thompson
	Updated: 12/07/17

	Description: Interface for CoreMemory for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- manages IDs (variables or Constants) and their associated values and virtual memory locations
		- Manages array dimensions for range checking

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include "FileManager.h"

#include <iostream>	// Console IO
#include <sstream> // used in convertToDouble()
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_NUM_VARIABLES 1001
#define NOT_FOUND_IN_ARRAY -1

#define UNDEFINED_VALUE 0.123456789

/* ==============================================================================
	Type Definitions
============================================================================== */

struct arrayTableObject {
	unsigned int memoryLocation;
	unsigned int size;
	bool isArray;
};

/* ==============================================================================
	symbol Table Class Interface
============================================================================== */

class CoreMemory {
public:
	/* ==============================================================================
	Constructor & Destructor
	============================================================================== */
	CoreMemory();
	~CoreMemory();

	/* ==============================================================================
		Public Manipulator Methods
	============================================================================== */
	// loads the new line of core into the CoreMemory
	void loadLine(string newLine);

	// Sets the RValue at memoryLocation to newValue
	void setValue(int memoryLocation, string newValue);

	// Sets the RValue at memoryLocation to newValue
	void setValue(int memoryLocation, double newValue);

	// Sets the RValue of the destinationAddress to the RValue of the sourceAddress
	void deepCopy(int destinationAddress, int sourceAddress);

	// Adds a new array to the globalArrayofArrayDimensions
	void addNewArray(int memoryLocationOfNewArray, int sizeOfNewArray);

	// sets the flag to true
	void turnOnRangeCheckingFlag();

	// sets the flag to true
	void turnOnZeroForUndefinedFlag();

	/* ==============================================================================
		Public Accessor Methods
	============================================================================== */

	// returns the value at the specified memoryLocation
	string getValue(int memoryLocation);

	// returns the value at the specified memoryLocation
	double getValueAsDouble(int memoryLocation);

	// Returns true if the start & end indexes are within the range of the array
	bool rangeChecksOut(int arrayMemoryLocation, int startIndex, int endIndex);

	// prints out the value for every value in CoreMemory - For Executor
	void printCoreMemory();

	// prints out the Rvalue for every memoryLocation in CoreMemory from startIndex to endIndex - For Executor
	void printCoreMemory(int startIndex, int endIndex);

	// prints out the globalArrayofArrayDimensions
	// void printArrayDimension();

	// takes in currentString, sets the numberAsDouble, and returns if successful
	// bool convertToDouble(string currentString, double &numberAsDouble);

protected:

	/* ==============================================================================
		Private Members
	============================================================================== */

	// Execution Flags
	bool checkRangesFlag;
	bool useZeroFlag;

	// Core memory Array of Variables for Execution
	string globalCoreMemoryArray[MAX_NUM_VARIABLES];
	int globalSizeCoreMemory; // - For Executor

	// Array Of Arrays for Execution
	arrayTableObject globalArrayofArrayDimensions[MAX_NUM_VARIABLES];
	int globalNumArrayDimension;
};