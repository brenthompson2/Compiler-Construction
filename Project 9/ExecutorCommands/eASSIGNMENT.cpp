/* ==============================================================================

	File: eASSIGNMENT.cpp
	Author: Brendan Thompson
	Updated: 12/10/17

	Description: Implementation of Functions for handling ASSIGNMENT command for Executor object made for Transylvania University University Fall Term 2017 Compiler Construction class

============================================================================== */

#include "eASSIGNMENT.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

eASSIGNMENT::eASSIGNMENT(){
	return;
}

eASSIGNMENT::~eASSIGNMENT(){
	return;
}

// Connects local pointer to CoreMemory with the parent's (executor's) versions
void eASSIGNMENT::prepareASSIGNMENT(CoreMemory *parentMemoryManager){
	currentMemoryManager = parentMemoryManager;
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// calls the functions necessary to parse the line, sync the variables with the CoreMemory, and print the object code to the file while counting errors
// returns num errors
int eASSIGNMENT::handleASSIGNMENT(ProgramLineObject *currentLine){
	// cout << "\t\t[ASSIGNMENT]: Executing Assignment\n";
	setGlobals(currentLine);
	// printCurrentExpression();

	int indexOperator;

	while (globalNumElements > 2){
		indexOperator = getIndexFirstOperator();

		if (indexOperator > 1){
			handleOperation(indexOperator);
			// printCurrentExpression();
		}
	}

	if (globalNumErrors == 0){
		// cout << "\t\t[ASSIGNMENT]: Successfully completed ASSIGNMENT command\n";
	}
	else {
		cout << "\t\t[ASSIGNMENT]: Failed to complete ASSIGNMENT command with " << globalNumErrors << " errors\n";
	}

	(*currentMemoryManager).clearTempMem();
	return globalNumErrors;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

void eASSIGNMENT::setGlobals(ProgramLineObject *currentLine){
	int currentElement;
	globalNumElements = (*currentLine).numElementsInLine - 2;
	// cout << "\t\t[ASSIGNMENT]: Statement has " << globalNumElements << " elements\n";
	for (int i = 0; i < globalNumElements; i++){
		currentElement = ((*currentLine).lineOfCodeArray)[i + 1];
		// cout << "\t\t[ASSIGNMENT]: Setting Element \"" << currentElement << "\" to index " << i << endl;
		globalArrayOfElements[i] = currentElement;
		// cout << "\t\t[ASSIGNMENT]: Index " << i << " = \"" << globalArrayOfElements[i] << endl;
	}
	globalNumErrors = 0;
	return;
}

void eASSIGNMENT::handleOperation(int indexOfOperator){
	int currentValueToken;
	int firstValue_L, secondValue_L, returnValue_L;
	double firstValue_R, secondValue_R, returnValue_R;

	currentValueToken = globalArrayOfElements[indexOfOperator];
	firstValue_L = globalArrayOfElements[indexOfOperator - 2];
	secondValue_L = globalArrayOfElements[indexOfOperator - 1];
	firstValue_R = (*currentMemoryManager).getValueAsDouble(firstValue_L);
	secondValue_R = (*currentMemoryManager).getValueAsDouble(secondValue_L);

	switch (currentValueToken){
		case OBJ_VALUE_EQUALS:
			// cout << "\t\t[ASSIGNMENT]: RValue at location " << firstValue_L << " now equal to that of " << secondValue_L << endl;
			(*currentMemoryManager).deepCopy(firstValue_L, secondValue_L);
			break;
		case OBJ_VALUE_LEFT_BRACKET:
			returnValue_R = firstValue_L + secondValue_R;
			// cout << "\t\t[ASSIGNMENT]: Accessing the array starting at location" << firstValue_L << " at the index " << secondValue_R << ", which is " << returnValue_R << endl;
			globalArrayOfElements[indexOfOperator - 2] = returnValue_R;
			break;
		case OBJ_VALUE_EXPONENT:
			returnValue_R =	pow(firstValue_R, secondValue_R);
			// cout << "\t\t[ASSIGNMENT]: " << firstValue_R << " ^ " << secondValue_R << " = " << returnValue_R << endl;
			returnValue_L = (*currentMemoryManager).addNewTempMemValue(returnValue_R);
			globalArrayOfElements[indexOfOperator - 2] = returnValue_L;
			break;
		case OBJ_VALUE_TIMES:
			returnValue_R =	firstValue_R * secondValue_R;
			returnValue_L = (*currentMemoryManager).addNewTempMemValue(returnValue_R);
			globalArrayOfElements[indexOfOperator - 2] = returnValue_L;
			break;
		case OBJ_VALUE_DIVIDE:
			returnValue_R =	firstValue_R / secondValue_R;
			// cout << "\t\t[ASSIGNMENT]: " << firstValue_R << " / " << secondValue_R << " = " << returnValue_R << endl;
			returnValue_L = (*currentMemoryManager).addNewTempMemValue(returnValue_R);
			globalArrayOfElements[indexOfOperator - 2] = returnValue_L;
			break;
		case OBJ_VALUE_PLUS:
			returnValue_R =	firstValue_R + secondValue_R;
			// cout << "\t\t[ASSIGNMENT]: " << firstValue_R << " + " << secondValue_R << " = " << returnValue_R << endl;
			returnValue_L = (*currentMemoryManager).addNewTempMemValue(returnValue_R);
			globalArrayOfElements[indexOfOperator - 2] = returnValue_L;
			break;
		case OBJ_VALUE_MINUS:
			returnValue_R =	firstValue_R - secondValue_R;
			// cout << "\t\t[ASSIGNMENT]: " << firstValue_R << " - " << secondValue_R << " = " << returnValue_R << endl;
			returnValue_L = (*currentMemoryManager).addNewTempMemValue(returnValue_R);
			globalArrayOfElements[indexOfOperator - 2] = returnValue_L;
			break;
	}

	// Shift rest of expression
	for (int i = indexOfOperator - 1; ((i + 2) < globalNumElements); i++){
		globalArrayOfElements[i] = globalArrayOfElements[i + 2];
	}
	globalNumElements += -2;

	return;
}

/* ==============================================================================
	Private Accessor Methods
============================================================================== */

int eASSIGNMENT::getIndexFirstOperator(){
	int indexNextOperator = OPERATOR_NOT_FOUND;
	int indexOperator;
	int currentElement;
	bool continueParsing = true;

	for (int i = 0; ((i < globalNumElements) && continueParsing); i++){
		currentElement = globalArrayOfElements[i];
		// cout << "\t\t[ASSIGNMENT]: Checking Element \"" << currentElement << "\"\n";
		if (currentElement < 0){
			indexNextOperator = i;
			// cout << "\t\t[ASSIGNMENT]: Found operator \"" << currentElement << "\" at index " << indexNextOperator << endl;
			continueParsing = false;
		}
	}

	if (indexNextOperator == OPERATOR_NOT_FOUND){
		cout << "\t\t[ASSIGNMENT]: Error! Unable to find operator\n";
		globalNumErrors++;
	}

	return indexNextOperator;
}

// Prints out the postfix expression array
void eASSIGNMENT::printCurrentExpression(){
	cout << "\t\t[ASSIGNMENT]: Current Expression has " << globalNumElements << " elements:\t";
	int currentElement;
	for (int i = 0; i < globalNumElements; i++){
		currentElement = globalArrayOfElements[i];
		cout << currentElement << " ";
	}
	cout << endl;
	return;
}