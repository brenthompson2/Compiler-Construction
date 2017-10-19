/*
  ==============================================================================

	File: Compiler.cpp
	Author: Brendan Thompson
	Updated: 09/24/17

	Description: Interface for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class

	Status: Instantiates a FileManager, creates <file>.noblanks

  ==============================================================================
*/

#include "Compiler.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

// Instantiates a BREN_Compiler object which creates an instance of FileManager
BREN_Compiler::BREN_Compiler (){
	globalFileManager.prepareForCompilation();
	numErrors = 0;

	instantiateCommandObjects();

	cout << "\t[Compiler]: Initialized Compiler\n";
	return;
}

// Shuts Down the BREN_Compiler object
void BREN_Compiler::shutdown (){
	globalFileManager.shutdown();
	cout << "\t[Compiler]: Shutdown BREN_Compiler\n";
	return;
}

/* ==============================================================================
	Public Methods
============================================================================== */

// Compiles the preprocessed .noblanks file into the final .obj, getting one line at a time and calling parseLine()
void BREN_Compiler::compile(){
	string currentLine;
	bool continueCompiling = true;
	int lineCount = 0;


	currentLine = globalFileManager.getNextLine();
	cout << "\t[Compiler]: Got first line: " << currentLine << endl;
	if (currentLine == "@"){
		continueCompiling = false;
		cout << "\t[Compiler]: ERROR: File appears to be empty\n";
	}

	while (continueCompiling){
		parseLine(currentLine);

		currentLine = globalFileManager.getNextLine();
		lineCount++;
		cout << "\t[Compiler]: Got line " << lineCount << ": " << currentLine << endl;
		if (currentLine == "@"){
			continueCompiling = false;
		}
	}
}

/* ==============================================================================
	Private Methods
============================================================================== */

void BREN_Compiler::parseLine(string currentLine){
	char currentCharacter = currentLine[0];
	switch (currentCharacter){
		case 'R':
			cout << "\t[Compiler]: Found Read Command\n";
			if (!mainREADHandler.newREAD(currentLine)){
				cout << "\t[Compiler]: ERROR: Failed to handle READ: " << currentLine << endl << endl << endl;
				numErrors++;
			}
			else {
				cout << "\t[Compiler]: Successfully handled READ: " << currentLine << endl << endl << endl;
			}
			break;
		case 'W':
			cout << "\t[Compiler]: Found Write Command\n";
			if (!mainWRITEHandler.newWRITE(currentLine)){
				cout << "\t[Compiler]: ERROR: Failed to handle WRITE: " << currentLine << endl << endl << endl;
				numErrors++;
			}
			else {
				cout << "\t[Compiler]: Successfully handled WRITE: " << currentLine << endl << endl << endl;
			}
			break;
		case 'S':
			cout << "\t[Compiler]: Found Stop Command\n";
			if (!mainSTOPHandler.newSTOP(currentLine)){
				cout << "\t[Compiler]: ERROR: Failed to handle STOP: " << currentLine << endl << endl << endl;
				numErrors++;
			}
			else {
				cout << "\t[Compiler]: Successfully handled STOP: " << currentLine << endl << endl << endl;
			}
			break;
	}
}

void BREN_Compiler::instantiateCommandObjects(){
	mainREADHandler.prepareREAD(&globalFileManager, &globalMemoryManager);
	mainWRITEHandler.prepareWRITE(&globalFileManager);
	mainSTOPHandler.prepareSTOP(&globalFileManager);
}