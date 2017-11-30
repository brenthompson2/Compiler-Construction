/* =============================================================================

	File: ProgramLineTable.cpp
	Author: Brendan Thompson
	Updated: 11/16/17

	Description: Implementation for ProgramLineTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- Manages Program Counter & Lines of Obj Code
		- MAX_NUM_LINES = 1000 lines in the program

==============================================================================*/

#include "ProgramLineTable.h"

/* ==============================================================================
Constructor & Destructor
============================================================================== */

ProgramLineTable::ProgramLineTable(){
	globalNumLinesOfCode = 0;
	// cout << "\t\t[ProgramLineTable]: Initialized ProgramLineTable\n";
	return;
}

ProgramLineTable::~ProgramLineTable(){
	// cout << "\t\t[ProgramLineTable]: Shutdown ProgramLineTable\n";
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// adds a new line of obj code to the ProgramLineTable
void ProgramLineTable::addLine(string newLine){
	if (newLine[0] != '\0'){
		// cout << "\t\t\t[ProgramLineTable]: Adding line " << globalNumLinesOfCode << ": \""<< newLine << "\" to ProgramLineTable\n";
		tokenizeLine(newLine, &programLineArray[globalNumLinesOfCode]);
		// cout << "\t\t[ProgramLineTable]: Total Num Elements In Line \"" << (programLineArray[globalNumLinesOfCode]).numElementsInLine << "\"\n";
		globalNumLinesOfCode++;
		// printProgramLineTable();
	}
	return;
}

/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// Turns the currentLine into a ProgramLineObject
void ProgramLineTable::tokenizeLine(string currentLine, ProgramLineObject *currentProgramLine){
	string currentOpCode;
	int currentOpCodeAsInt;
	// cout << "\t\t[ProgramLineTable]: Tokenizing Line \"" << currentLine << "\"\n";

	char currentChar;
	int currentCharIterator = 0;

	bool continueParsingLine = true;
	bool continueParsingCurrentObjectCode = true;

	while (continueParsingLine){
		currentOpCode = "";
		continueParsingCurrentObjectCode = true;
		while (continueParsingCurrentObjectCode){
			currentChar = currentLine[currentCharIterator];

			if (currentChar == ' '){
				continueParsingCurrentObjectCode = false;
			}
			else{
				if (currentChar == '\0'){
					continueParsingCurrentObjectCode = false;
					continueParsingLine = false;
				}
				else {
					currentOpCode += currentChar;
				}
			}

			currentCharIterator++;
		}

		std::stringstream str(currentOpCode);
		str >> (currentOpCodeAsInt);
		// cout << "\t\t[ProgramLineTable]: Found Object Code \"" << currentOpCodeAsInt << "\"\n";

		int nextSlot = (*currentProgramLine).numElementsInLine;
		if (nextSlot == 0){
			(*currentProgramLine).opCode = currentOpCodeAsInt;
		}
		(*currentProgramLine).lineOfCodeArray[nextSlot] = currentOpCodeAsInt;
		((*currentProgramLine).numElementsInLine)++;
		// cout << "\t\t[ProgramLineTable]:  Num Elements In Line \"" << (*currentProgramLine).numElementsInLine << "\"\n";
	}

	return;
}

// Returns the index of the line after the next loopend given the currentProgramLine,
int ProgramLineTable::getIndexNextLoopend(int currentProgramLine){
	bool continueSearching = true;
	bool foundLoopEnd = false;
	int currentOpCode;

	while (continueSearching){
		currentProgramLine++;
		if (currentProgramLine <= globalNumLinesOfCode){
			currentOpCode = programLineArray[currentProgramLine].opCode;
			if (currentOpCode == LOOPEND_OP_CODE){
				continueSearching = false;
				foundLoopEnd = true;
			}
			else {
				continueSearching = true;
			}
		}
		else {
			continueSearching = false;
		}

	}

	return currentProgramLine;

}

// Returns a pointer to a copy of the ProgramLineObject for the next line indexed at nextProgramCounter
ProgramLineObject* ProgramLineTable::getCopyOfNextProgramObject(int nextProgramCounter){
	ProgramLineObject *nextProgramLine;

	// cout << "\n\n\t\t[ProgramLineTable]: Next program: " << nextProgramCounter << "\tLines: " << globalNumLinesOfCode << endl;

	if (nextProgramCounter < globalNumLinesOfCode){
		nextProgramLine = getCopyOfProgramObject(programLineArray[nextProgramCounter]);
	}
	else {
		nextProgramLine = new ProgramLineObject();
		(*nextProgramLine).numElementsInLine = END_OF_PROGRAM;
		(*nextProgramLine).opCode = END_OF_PROGRAM;
		// cout << "\t\t[ProgramLineTable]: Reached End Of Program " << (*nextProgramLine).numElementsInLine << "\n";
	}

	return nextProgramLine;
}

// Returns a pointer to a copy of the programObjectToCopy
ProgramLineObject* ProgramLineTable::getCopyOfProgramObject(ProgramLineObject programObjectToCopy){
	ProgramLineObject *newCopyOfProgramObject = new ProgramLineObject;

	(*newCopyOfProgramObject).numElementsInLine = programObjectToCopy.numElementsInLine;
	(*newCopyOfProgramObject).opCode = programObjectToCopy.opCode;
	for (int i = 0; i < (*newCopyOfProgramObject).numElementsInLine; i++){
		(*newCopyOfProgramObject).lineOfCodeArray[i] = programObjectToCopy.lineOfCodeArray[i];
	}

	return newCopyOfProgramObject;
}

// returns the op code for the line at objLineNumber
// int ProgramLineTable::getOpCode(int objLineNumber){
	// string currentLine = programLineArray[objLineNumber];
	// string currentOpCode = "";
	// int opCodeAsInt;

	// currentOpCode += currentLine[0];
	// if ((currentLine[1] != ' ') && (currentLine[1] != '\0')){
	// 	currentOpCode += currentLine[1];
	// }

	// std::stringstream str(currentOpCode);
	// str >> (opCodeAsInt);
	// // cout << "\t\t[ProgramLineTable]: Found Op Code \"" << opCodeAsInt << "\"\n";
	// return opCodeAsInt;
// }

// iterates through the ProgramLineTable and prints the labelName & transyLineNumber
void ProgramLineTable::printProgramLineTable(){
	cout << "\t\t\t[ProgramLineTable]: There are currently " << globalNumLinesOfCode << " lines of code\n";
	ProgramLineObject *currentProgramLine;

	for (int i = 0; i < globalNumLinesOfCode; i++){
		cout << "\t\t\t" << i << ": ";
		currentProgramLine = &(programLineArray[i]);
		// cout << (*currentProgramLine).numElementsInLine;
		for (int j = 0; j < (*currentProgramLine).numElementsInLine; j++){
			 cout << (*currentProgramLine).lineOfCodeArray[j] << " ";
		}
		cout << endl;
	}

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

/* ==============================================================================
	Private Accessor Methods
============================================================================== */