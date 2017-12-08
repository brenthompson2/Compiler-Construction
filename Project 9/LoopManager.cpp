/* ==============================================================================

	File: LoopManager.cpp
	Author: Brendan Thompson
	Updated: 11/30/17

	Description: Implementation for LoopManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- Handles loop & loopend commands
		- Manages the current loop
		- Handles nesting

============================================================================== */

#include "LoopManager.h"

/* ==============================================================================
Constructor & Destructor
============================================================================== */

LoopManager::LoopManager(){
	globalIndexTopLoopObject = -1;
	// cout << "\t\t[LoopManager]: Initialized LoopManager\n";
	return;
}

LoopManager::~LoopManager(){
	// cout << "\t\t[LoopManager]: Shutdown LoopManager\n";
	return;
}

// sets the global parentMemoryManager & parentProgramManager to point to the Compiler's
void LoopManager::prepareLoopManager(CoreMemory *currentMemoryManager, ProgramLineTable *currentProgramManager){
	parentMemoryManager = currentMemoryManager;
	parentProgramManager = currentProgramManager;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// Adds a new array to the globalLoopArray
void LoopManager::handleLOOP(ProgramLineObject *currentLine, int *currentProgramCounter){
	int runnerLValue, startLValue, endLValue, incrementLValue;

	// Parse the Loop Parameters
	runnerLValue = (*currentLine).lineOfCodeArray[1];
	startLValue = (*currentLine).lineOfCodeArray[2];
	endLValue = (*currentLine).lineOfCodeArray[3];
	incrementLValue = (*currentLine).lineOfCodeArray[4];

	// Add the New Loop
	if (!(currentlyExists(*currentProgramCounter))){
		addNewLoop(*currentProgramCounter, runnerLValue, startLValue, endLValue, incrementLValue);
	}
	else {
		cout << "\t\t\t[LoopManager]: Warning, a loop is attempting to nest inside itself\n";
	}

	// Check Condition & Set the Program Counter
	if (checkConditionTopLoop()){
		(*currentProgramCounter)++;
	}
	else {
		(*currentProgramCounter) = (*parentProgramManager).getIndexNextLoopend(*currentProgramCounter);
	}

	// printLoopManager();
	return;
}

// sets the currentProgramCounter appropriately given the conditional of the top loop and conditionally pops it off the globalLoopArray
void LoopManager::handleLOOPEND(int *currentProgramCounter){
	incrementTopRunner();
	if (checkConditionTopLoop()){
		(*currentProgramCounter) = globalLoopArray[globalIndexTopLoopObject].lineNumber + 1;
	}
	else {
		(*currentProgramCounter)++;
		popOffTopLoop();
	}
	return;
}

/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// iterates through the LoopManager and prints the variableName & memoryLocation
void LoopManager::printLoopManager(){
	cout << "\t\t\t[LoopManager]: currently has " << globalIndexTopLoopObject + 1 << " loops\n";

	cout << "\t\t\t\t\tLine\t&Run\t&Start\t&End\t&Increment\n";
	for (int i = 0; i <= globalIndexTopLoopObject; i++){
		cout << "\t\t\t\t" << i << ":\t" << globalLoopArray[i].lineNumber;
		cout << "\t" << globalLoopArray[i].runnerAddress;
		cout << "\t" << globalLoopArray[i].startIndexAddress;
		cout << "\t" << globalLoopArray[i].endIndexAddress;
		cout << "\t" << globalLoopArray[i].incrementAmountAddress;
		cout << endl;
	}
	return;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// adds the new loop to the top of the globalLoopArray & sets globalCurrentLoopIndex to point to it
void LoopManager::addNewLoop(int newLineNumber, int newRunnerAddress, int newStartIndexAddress, int newEndIndexAddress, int incrementAddress){
	globalIndexTopLoopObject++;
	globalLoopArray[globalIndexTopLoopObject].lineNumber = newLineNumber;
	globalLoopArray[globalIndexTopLoopObject].runnerAddress = newRunnerAddress;
	globalLoopArray[globalIndexTopLoopObject].startIndexAddress = newStartIndexAddress;
	globalLoopArray[globalIndexTopLoopObject].endIndexAddress = newEndIndexAddress;
	globalLoopArray[globalIndexTopLoopObject].incrementAmountAddress = incrementAddress;
	return;
}

// Decrements the pointer to the top loop
void LoopManager::popOffTopLoop(){
	globalIndexTopLoopObject--;
	return;
}

// Adds the topIncrementAmount to the topRunnerValue
void LoopManager::incrementTopRunner(){
	int topRunnerAddress, topIncrementAmountAddress;
	string topRunnerValue_string, topIncrementAmount_string, newRunnerValue;
	double topRunnerValue_double, topIncrementAmount_double;

	// Get Address
	topRunnerAddress = globalLoopArray[globalIndexTopLoopObject].runnerAddress;
	topIncrementAmountAddress = globalLoopArray[globalIndexTopLoopObject].incrementAmountAddress;

	// Get Value as String
	topRunnerValue_string = (*parentMemoryManager).getValue(topRunnerAddress);
	topIncrementAmount_string = (*parentMemoryManager).getValue(topIncrementAmountAddress);

	// Convert Values to doubles
	std::stringstream str0(topRunnerValue_string);
	str0 >> topRunnerValue_double;
	std::stringstream str1(topIncrementAmount_string);
	str1 >> topIncrementAmount_double;

	// Increment Runner, Convert it to a String, & Save it
	topRunnerValue_double += topIncrementAmount_double;
	(*parentMemoryManager).setValue(topRunnerAddress, topRunnerValue_double);

	return;
}

// Returns the result of the conditional of the top loop
bool LoopManager::checkConditionTopLoop(){
	double topRunnerValue, topStartValue, topEndValue, topIncrementAmount;
	int topRunnerAddress, topStartIndexAddress, topEndIndexAddress, topIncrementAmountAddress;
	bool topResultOfCondition = false;

	topRunnerAddress = globalLoopArray[globalIndexTopLoopObject].runnerAddress;
	topStartIndexAddress = globalLoopArray[globalIndexTopLoopObject].startIndexAddress;
	topEndIndexAddress = globalLoopArray[globalIndexTopLoopObject].endIndexAddress;
	topIncrementAmountAddress = globalLoopArray[globalIndexTopLoopObject].incrementAmountAddress;

	setConditionValues(topRunnerAddress, &topRunnerValue,
						topStartIndexAddress, &topStartValue,
						topEndIndexAddress, &topEndValue,
						topIncrementAmountAddress, &topIncrementAmount);

	topResultOfCondition = getConditionResults(topIncrementAmount, topRunnerValue, topEndValue);

	return topResultOfCondition;
}

// Sets the RValues given the LValues
void LoopManager::setConditionValues(int runnerLValue, double *runnerRValue,
										int startLValue, double *startRValue,
										int endLValue, double *endRValue,
										int incrementLValue, double *incrementRValue){

	// Get Values as Strings
	string runnerRValue_string, startRValue_string, endRValue_string, incrementRValue_string;
	runnerRValue_string = (*parentMemoryManager).getValue(runnerLValue);
	startRValue_string = (*parentMemoryManager).getValue(startLValue);
	endRValue_string = (*parentMemoryManager).getValue(endLValue);
	incrementRValue_string = (*parentMemoryManager).getValue(incrementLValue);

	// Convert from strings to doubles
	std::stringstream str0(runnerRValue_string);
	str0 >> (*runnerRValue);
	std::stringstream str1(startRValue_string);
	str1 >> (*startRValue);
	std::stringstream str2(endRValue_string);
	str2 >> (*endRValue);
	std::stringstream str3(incrementRValue_string);
	str3 >> (*incrementRValue);
	return;
}

// returns true if the condition succeeded given the direction represented by the increment amount
bool LoopManager::getConditionResults(double topIncrementAmount, double topRunnerValue, double topEndValue){
	bool resultOfCondition = false;
	// cout << "\t\t\t[LoopManager]: Increment: " << topIncrementAmount << "\tRunner: " << topRunnerValue << "\tEnd: " << topEndValue << endl;
	if (topIncrementAmount == 0){
		if (topRunnerValue != topEndValue){
			resultOfCondition = true;
		}
		else {
			resultOfCondition = false;
		}
	}
	else {
		if (topIncrementAmount > 0){
			if (topRunnerValue <= topEndValue){
				resultOfCondition = true;
			}
			else {
				resultOfCondition = false;
			}
		}
		else {
			if (topRunnerValue >= topEndValue){
				resultOfCondition = true;
			}
			else {
				resultOfCondition = false;
			}
		}
	}
	return resultOfCondition;
}

// returns true if the variable already exists in the LoopManager
bool LoopManager::currentlyExists(int lineNumberOfLoop){
	bool loopCurrentlyExists = false;
	if (!(globalIndexTopLoopObject == -1)){
		for (int i = 0; i <= globalIndexTopLoopObject; i++){
			if (globalLoopArray[i].lineNumber == lineNumberOfLoop){
				loopCurrentlyExists = true;
				break;
			}
		}
	}
	return loopCurrentlyExists;
}