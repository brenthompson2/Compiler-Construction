/* ==============================================================================

	File: eIF.cpp
	Author: Brendan Thompson
	Updated: 11/30/17

	Description: Implementation of Functions for processing IF command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eIF.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eIF::eIF(){
	return;
}

eIF::~eIF(){
	return;
}

// Connects global pointer to ParentMemoryManager
void eIF::prepareIF(SymbolTable *currentMemoryManager){
	parentMemoryManager = currentMemoryManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to test the IF and sets the currentProgramLine accordingly
void eIF::handleIF(ProgramLineObject *currentLine, int *currentProgramLine){
	globalCurrentLine = currentLine;

	float firstID, secondID;
	int currentTestCondition, conditionalDestinationLine;

	getValuesForConditional(&firstID, &secondID, &currentTestCondition, &conditionalDestinationLine);

	if (getResultOfCondition(firstID, secondID, currentTestCondition)) {
		(*currentProgramLine) = conditionalDestinationLine;
	}
	else {
		(*currentProgramLine)++;
	}

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// Sets the values by looking up the memoryLocations provided by globalCurrentLine
void eIF::getValuesForConditional(float *firstValue, float *secondValue, int *testCondition, int *destinationLine){
	int firstMemoryLocation, secondMemoryLocation;
	string firstValue_string, secondValue_string;

	// Get Address
	firstMemoryLocation = (*globalCurrentLine).lineOfCodeArray[1];
	secondMemoryLocation = (*globalCurrentLine).lineOfCodeArray[2];
	(*testCondition) = (*globalCurrentLine).lineOfCodeArray[3];
	(*destinationLine) = (*globalCurrentLine).lineOfCodeArray[4];

	// Get Value as String
	firstValue_string = (*parentMemoryManager).getValue(firstMemoryLocation);
	secondValue_string = (*parentMemoryManager).getValue(secondMemoryLocation);

	// Convert Values to floats
	std::stringstream str0(firstValue_string);
	str0 >> (*firstValue);
	std::stringstream str1(secondValue_string);
	str1 >> (*secondValue);

	return;
}

// Returns the value of the tested condition
bool eIF::getResultOfCondition(float firstOperand, float secondOperand, int testCondition){
	bool resultOfCondition = false;;

	switch (testCondition){
		case LESS_CODE:
			if (firstOperand < secondOperand){
				resultOfCondition = true;
			}
			break;
		case LESS_EQUAL_CODE:
			if (firstOperand <= secondOperand){
				resultOfCondition = true;
			}
			break;
		case EQUAL_CODE:
			if (firstOperand == secondOperand){
				resultOfCondition = true;
			}
			break;
		case GREATER_CODE:
			if (firstOperand > secondOperand){
				resultOfCondition = true;
			}
			break;
		case GREATER_EQUAL_CODE:
			if (firstOperand >= secondOperand){
				resultOfCondition = true;
			}
			break;
		case NOT_EQUAL_CODE:
			if (firstOperand != secondOperand){
				resultOfCondition = true;
			}
			break;
	}

	return resultOfCondition;
}