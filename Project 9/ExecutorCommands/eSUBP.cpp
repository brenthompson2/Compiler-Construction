/* ==============================================================================

	File: eSUBP.cpp
	Author: Brendan Thompson
	Updated: 12/01/17

	Description: Implementation of Functions for processing SUBP command for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eSUBP.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eSUBP::eSUBP(){
	return;
}

eSUBP::~eSUBP(){
	return;
}

// Connects global pointer to ParentMemoryManager
void eSUBP::prepareSUBP(CoreMemory *currentMemoryManager){
	ParentMemoryManager = currentMemoryManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to execute the SUBP command
void eSUBP::handleSUBP(ProgramLineObject *currentLine){
	globalCurrentLine = currentLine;
	int operationCode;

	string variableValue_string, IdMemLocation_string, IdValue_string;
	int variableMemoryLocation_int, IdMemLocation_int;
	double variableValue_double, IdValue_double;

	operationCode = ((*globalCurrentLine).lineOfCodeArray)[1];
	variableMemoryLocation_int = ((*globalCurrentLine).lineOfCodeArray)[2];
	IdMemLocation_int = ((*globalCurrentLine).lineOfCodeArray)[3];
	// cout << "\t\t[SUBP]: Executing SUBP operation " << operationCode << " on variable at mem location " << variableMemoryLocation_int << " using the ID at mem location " << IdMemLocation_int << endl;

	variableValue_string = (*ParentMemoryManager).getValue(variableMemoryLocation_int);
	IdValue_string = (*ParentMemoryManager).getValue(IdMemLocation_int);

	// cout << "\t\t[SUBP]: Executing SUBP operation " << operationCode << " on " << variableValue_string << " using " << IdValue_string << endl;

	std::stringstream str0(variableValue_string);
	str0 >> variableValue_double;
	std::stringstream str1(IdValue_string);
	str1 >> IdValue_double;

	// cout << "\t\t[SUBP]: Executing SUBP operation " << operationCode << " on " << variableValue_double << " using " << IdValue_double << endl;

	executeSUBPCommand(operationCode, variableMemoryLocation_int, variableValue_double, IdValue_double);
	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

// executes the command
void eSUBP::executeSUBPCommand(int operationCode, int variableMemLocation, double variableValue, double IdValue){
	double newValue;
	string newValue_string;

	switch (operationCode){
		case SIN_CODE:
			newValue = sin(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = sin(" << IdValue << ")\n";
			break;
		case COS_CODE:
			newValue = cos(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = cos(" << IdValue << ")\n";
			break;
		case EXP_CODE:
			newValue = exp(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = exp(" << IdValue << ")\n";
			break;
		case ABS_CODE:
			newValue = abs(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = abs(" << IdValue << ")\n";
			break;
		case ALG_CODE:
			newValue = log2(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = alg(" << IdValue << ")\n";
			break;
		case ALN_CODE:
			newValue = log(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = aln(" << IdValue << ")\n";
			break;
		case LOG_CODE:
			newValue = log10(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = log(" << IdValue << ")\n";
			break;
		case SQR_CODE:
			newValue = sqrt(IdValue);
			cout << "\t\t[SUBP]: " << newValue << " = sqrt(" << IdValue << ")\n";
			break;
	}

	(*ParentMemoryManager).setValue(variableMemLocation, newValue);
	return;
}