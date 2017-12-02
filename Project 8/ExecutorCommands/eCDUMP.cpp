/* ==============================================================================

	File: eCDUMP.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Implementation of Functions for processing CDUMP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- NOT BEING USED: EXECUTOR IS HANDLING THIS COMMAND

============================================================================== */

#include "eCDUMP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eCDUMP::eCDUMP(){
	return;
}

eCDUMP::~eCDUMP(){
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Connects local pointer to SymbolTable with the parent's (compiler's) versions
void eCDUMP::prepareCDUMP(SymbolTable *parentMemoryManager){
	currentMemoryManager = parentMemoryManager;
}


// calls the functions necessary to parse the line, sync the variables with the SymbolTable, and print the object code to the file while counting errors
void eCDUMP::handleCDUMP(ProgramLineObject *currentLine){
	globalCurrentLine = currentLine;
	string startIndexValue_string, endIndexValue_string, startIndexMemLocation_string, endIndexMemLocation_string;
	int startIndexValue_int, endIndexValue_int, startIndexMemLocation_int, endIndexMemLocation_int;

	startIndexMemLocation_int = ((*globalCurrentLine).lineOfCodeArray)[1];
	endIndexMemLocation_int = ((*globalCurrentLine).lineOfCodeArray)[2];
	// cout << "\t\t[CDUMP]: Executing CDUMP command from values at mem locations " << startIndexMemLocation_int << " to " << endIndexMemLocation_int << endl;

	startIndexValue_string = (*currentMemoryManager).getValue(startIndexMemLocation_int);
	endIndexValue_string = (*currentMemoryManager).getValue(endIndexMemLocation_int);

	// cout << "\t\t[CDUMP]: Executing CDUMP command from " << startIndexValue_string << " to " << endIndexValue_string << endl;

	std::stringstream str0(startIndexValue_string);
	str0 >> startIndexValue_int;
	std::stringstream str1(endIndexValue_string);
	str1 >> endIndexValue_int;

	// cout << "\t\t[CDUMP]: Executing CDUMP command from " << startIndexValue_int << " to " << endIndexValue_int << endl;
	coreDump(startIndexValue_int, endIndexValue_int);
	// cout << "\t\t[CDUMP]: Executed CDUMP command\n";
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// Outputs All Literals between the start and the end indexes
 void eCDUMP::coreDump(int startIndex, int endIndex){
 	string currentLiteral;
 	if ((startIndex >= 0) && (endIndex <= MAX_NUM_VARIABLES)){
	 	for (int i = startIndex; i <= endIndex; i++){
	 		currentLiteral = (*currentMemoryManager).getValue(i);
	 		cout << i << ": " << currentLiteral << endl;
	 	}
 	}
 	else {
 		if (startIndex >= 0){
			cout << "\t\t\t[LiteralTable]: Warning: Start Index Must Exceed 0: \"" << startIndex << "\"\n";
 		}
		if (endIndex <= MAX_NUM_VARIABLES){
			cout << "\t\t\t[LiteralTable]: Warning: End Index Exceeds " << MAX_NUM_VARIABLES << ": \"" << endIndex << "\"\n";
		}
 	}
 	return;
 }