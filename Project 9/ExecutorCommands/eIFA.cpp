/* ==============================================================================

	File: eIFA.cpp
	Author: Brendan Thompson
	Updated: 11/30/17

	Description: Implementation of Functions for processing IFA command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eIFA.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eIFA::eIFA(){
	return;
}

eIFA::~eIFA(){
	return;
}

// Connects global pointer to ParentMemoryManager
void eIFA::prepareIFA(CoreMemory *currentMemoryManager){
	parentMemoryManager = currentMemoryManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to test the IFA and sets the currentProgramLine accordingly
void eIFA::handleIFA(ProgramLineObject *currentLine, int *currentProgramLine){
	// cout << "\t\t[IFA]: Attempting to handle IFA Command\n";
	globalCurrentLine = currentLine;

	float valueToTest;
	int lineIfNegative, lineIfZero, lineIfPositive;

	getValueForConditional(&valueToTest, &lineIfNegative, &lineIfZero, &lineIfPositive);

	if (valueToTest == 0) {
		(*currentProgramLine) = lineIfZero;
	}
	else {
		if (valueToTest < 0){
			(*currentProgramLine) = lineIfNegative;
		}
		else {
			(*currentProgramLine) = lineIfPositive;
		}
	}

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// Sets the values by looking up the memoryLocations and values provided by globalCurrentLine
void eIFA::getValueForConditional(float *valueOfID, int *negativeLine, int *zeroLine, int *positiveLine){
	int idMemoryLocation;
	string idValue_string;

	// Get Addresses & Values
	idMemoryLocation = (*globalCurrentLine).lineOfCodeArray[1];
	(*negativeLine) = (*globalCurrentLine).lineOfCodeArray[2];
	(*zeroLine) = (*globalCurrentLine).lineOfCodeArray[3];
	(*positiveLine) = (*globalCurrentLine).lineOfCodeArray[4];

	// Get Value as String
	idValue_string = (*parentMemoryManager).getValue(idMemoryLocation);

	// Convert Values to floats
	std::stringstream str0(idValue_string);
	str0 >> (*valueOfID);

	return;
}