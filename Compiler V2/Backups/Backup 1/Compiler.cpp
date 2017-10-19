/*
  ==============================================================================

	File: Compiler.cpp
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Interface for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "Compiler.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

// Instantiates a BREN_Compiler object, tell FileManager to preprocess .transy file, and instantiates objects for handling commands
BREN_Compiler::BREN_Compiler (){
	numErrors = 0;
	cout << "\t[Compiler]: Initialized Compiler\n";
	return;
}

// Shuts Down the BREN_Compiler object
BREN_Compiler::~BREN_Compiler (){
	cout << "\t[Compiler]: Shutdown BREN_Compiler\n";
	return;
}

/* ==============================================================================
	Public Methods
============================================================================== */

// populates globalFileNameArray and tells the FileManager to preprocess all the files in fileNameArray and instantiates the objects for handling commands
void BREN_Compiler::prepareForCompilation(int numFiles, string arrayOfFileNames[]){
	globalNumFilesInArray = numFiles;
	for (int i = 0; i < globalNumFilesInArray; i++){
		globalFileNameArray[i] = arrayOfFileNames[i];
		globalFileManager.prepareForCompilation(globalFileNameArray[i]);
	}

	instantiateCommandObjects();

	cout << "\t[Compiler]: Prepared to Compile Files:\n";
	for (int i = 0; i < globalNumFilesInArray; i++){
		cout << "\t\t" << i << ": " << globalFileNameArray[i];
	}
	cout << endl;
	return;
}

// Compiles the preprocessed .noblanks file into the final .obj, getting one line at a time and calling parseLine()
void BREN_Compiler::compile(){
	string currentLine;
	bool continueCompiling = true;
	int lineCount = 0;


	currentLine = globalFileManager.getNextLine();
	cout << "\t[Compiler]: Got first line: " << currentLine << endl;
	if (currentLine == FILE_END_SENTINEL){
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

	if (numErrors == 0){
		cout << "\t[Compiler]: Successfully Compiled the file\n";

	}
	else {
		cout << "\t[Compiler]: Completed Compiling with " << numErrors << " errors\n";
	}

	globalMemoryManager.printSymbolTable();

	return;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// iterates through the line one character at a time and tells the appropriate object to handle the command
void BREN_Compiler::parseLine(string currentLine){
	char currentCharacter = currentLine[0];
	switch (currentCharacter){
		case 'A':
			if ((currentLine[1] == 'R') && (currentLine[2] == 'E') && (currentLine[3] == 'A') && (currentLine[4] == 'D')){
				// cout << "\t[Compiler]: Found aREAD Command\n";
				if (!mainAREADHandler.newAREAD(currentLine, &numErrors)){
					cerr << "\t[Compiler]: ERROR: Failed to handle aREAD: " << currentLine << endl << endl << endl;
				}
				else {
					cout << "\t[Compiler]: Successfully handled aREAD: " << currentLine << endl << endl << endl;
				}
				break;
			}
			if ((currentLine[1] == 'W') && (currentLine[2] == 'R') && (currentLine[3] == 'I') && (currentLine[4] == 'T') && (currentLine[5] == 'E')){
				// cout << "\t[Compiler]: Found aWRITE Command\n";
				if (!mainAWRITEHandler.newAWRITE(currentLine, &numErrors)){
					cerr << "\t[Compiler]: ERROR: Failed to handle aWRITE: " << currentLine << endl << endl << endl;
				}
				else {
					cout << "\t[Compiler]: Successfully handled aWRITE: " << currentLine << endl << endl << endl;
				}
				break;
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line : " << currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'D':
			if ((currentLine[1] == 'I') && (currentLine[2] == 'M')){
				// cout << "\t[Compiler]: Found Dim Command\n";
				if (!mainDIMHandler.newDIM(currentLine, &numErrors)){
					cerr << "\t[Compiler]: ERROR: Failed to handle DIM: " << currentLine << endl << endl << endl;
				}
				else {
					cout << "\t[Compiler]: Successfully handled DIM: " << currentLine << endl << endl << endl;
				}
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line : " << currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'R':
			if ((currentLine[1] == 'E') && (currentLine[2] == 'A') && (currentLine[3] == 'D')){
				// cout << "\t[Compiler]: Found Read Command\n";
				if (!mainREADHandler.newREAD(currentLine, &numErrors)){
					cerr << "\t[Compiler]: ERROR: Failed to handle READ: " << currentLine << endl << endl << endl;
				}
				else {
					cout << "\t[Compiler]: Successfully handled READ: " << currentLine << endl << endl << endl;
				}
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line : " << currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'S':
			if ((currentLine[1] == 'T') && (currentLine[2] == 'O') && (currentLine[3] == 'P')){
				// cout << "\t[Compiler]: Found Stop Command\n";
				if (!mainSTOPHandler.newSTOP(currentLine, &numErrors)){
					cerr << "\t[Compiler]: ERROR: Failed to handle STOP: " << currentLine << endl << endl << endl;
				}
				else {
					cout << "\t[Compiler]: Successfully handled STOP: " << currentLine << endl << endl << endl;
				}
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line : " << currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'W':
			if ((currentLine[1] == 'R') && (currentLine[2] == 'I') && (currentLine[3] == 'T') && (currentLine[4] == 'E')){
				// cout << "\t[Compiler]: Found Write Command\n";
				if (!mainWRITEHandler.newWRITE(currentLine, &numErrors)){
					cerr << "\t[Compiler]: ERROR: Failed to handle WRITE: " << currentLine << endl << endl << endl;
				}
				else {
					cout << "\t[Compiler]: Successfully handled WRITE: " << currentLine << endl << endl << endl;
				}
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line : " << currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		default:
			cerr << "\t[Compiler]: ERROR: Failed to interpret command " << currentLine << endl << endl << endl;
			break;
	}
}

// instantiates objects for handling commands by passing the FileManager & MemoryManager by reference
void BREN_Compiler::instantiateCommandObjects(){
	mainREADHandler.prepareREAD(&globalFileManager, &globalMemoryManager);
	mainWRITEHandler.prepareWRITE(&globalFileManager, &globalMemoryManager);
	mainDIMHandler.prepareDIM(&globalFileManager, &globalMemoryManager);
	mainAREADHandler.prepareAREAD(&globalFileManager, &globalMemoryManager);
	mainAWRITEHandler.prepareAWRITE(&globalFileManager, &globalMemoryManager);
	mainSTOPHandler.prepareSTOP(&globalFileManager);
}