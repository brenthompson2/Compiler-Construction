/*
  ==============================================================================

	File: Compiler.cpp
	Author: Brendan Thompson
	Updated: 10/09/17

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
void BREN_Compiler::prepareForCompilation(string fileToCompile){
	// globalNumFilesInArray = numFiles;
	// for (int i = 0; i < globalNumFilesInArray; i++){
	// 	globalFileNameArray[i] = arrayOfFileNames[i];
	// 	globalFileManager.prepareForCompilation(globalFileNameArray[i]);
	// }

	globalFileName = fileToCompile;
	globalFileManager.prepareForCompilation(fileToCompile, globalLinesOfCodeArray, &globalNumLinesOfCodeInArray);
	// printLineMappingArray();

	instantiateCommandObjects();

	return;
}

// Compiles the preprocessed .noblanks file into the final .obj, getting one line at a time and calling parseLine()
void BREN_Compiler::compile(){
	string currentLine;
	bool continueCompiling = true;
	int lineCount = 0;
	int actualLineNumber;


	currentLine = globalFileManager.getNextLine();
	actualLineNumber = getOriginalLineNumber(lineCount);
	cout << "\t[Compiler]: Attempting to Compile Input File Line number: " << actualLineNumber << endl;
	if (currentLine == FILE_END_SENTINEL){
		continueCompiling = false;
		cout << "\t[Compiler]: ERROR: File appears to be empty\n";
	}

	while (continueCompiling){
		parseLine(currentLine, actualLineNumber);

		currentLine = globalFileManager.getNextLine();
		lineCount++;
		actualLineNumber = getOriginalLineNumber(lineCount);

		if (currentLine == "@"){
			continueCompiling = false;
		}
		else {
			cout << "\n\t[Compiler]: Attempting to Compile Input File Line number: " << actualLineNumber << ": " << currentLine << endl;
		}
	}

	if (numErrors == 0){
		cout << "\n\t[Compiler]: Successfully Compiled the file\n";

	}
	else {
		cout << "\n\t[Compiler]: Completed Compiling with " << numErrors << " errors\n";
	}

	globalMemoryManager.printSymbolTable();

	return;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// iterates through the line one character at a time and tells the appropriate object to handle the command
void BREN_Compiler::parseLine(string currentLine, int correspondingLineNumber){
	char currentCharacter = currentLine[0];
	switch (currentCharacter){
		case 'A':
			if ((currentLine[1] == 'R') && (currentLine[2] == 'E') && (currentLine[3] == 'A') && (currentLine[4] == 'D')){
				// cout << "\t[Compiler]: Found aREAD Command\n";
				numErrors += mainAREADHandler.handleAREAD(currentLine, correspondingLineNumber);
			}
			else {
				if ((currentLine[1] == 'W') && (currentLine[2] == 'R') && (currentLine[3] == 'I') && (currentLine[4] == 'T') && (currentLine[5] == 'E')){
					// cout << "\t[Compiler]: Found aWRITE Command\n";
					numErrors += mainAWRITEHandler.handleAWRITE(currentLine, correspondingLineNumber);
				}
				else {
					cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
					numErrors++;
				}
			}
			break;
		case 'D':
			if ((currentLine[1] == 'I') && (currentLine[2] == 'M')){
				// cout << "\t[Compiler]: Found Dim Command\n";
				numErrors += mainDIMHandler.handleDIM(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'R':
			if ((currentLine[1] == 'E') && (currentLine[2] == 'A') && (currentLine[3] == 'D')){
				// cout << "\t[Compiler]: Found tRead Command\n";
				numErrors += mainREADHandler.handleREAD(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'S':
			if ((currentLine[1] == 'T') && (currentLine[2] == 'O') && (currentLine[3] == 'P')){
				// cout << "\t[Compiler]: Found Stop Command\n";
				numErrors += mainSTOPHandler.handleSTOP(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'W':
			if ((currentLine[1] == 'R') && (currentLine[2] == 'I') && (currentLine[3] == 'T') && (currentLine[4] == 'E')){
				// cout << "\t[Compiler]: Found tWrite Command\n";
				numErrors += mainWRITEHandler.handleWRITE(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		default:
			cerr << "\t[Compiler]: ERROR: Failed to interpret command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
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

// returns the line number in the original input file that correlates with the perceived line number from the preprocessed file
int BREN_Compiler::getOriginalLineNumber(int perceivedLine){
	return globalLinesOfCodeArray[perceivedLine];
}

// prints the whole array of the line numbers in the original input file as they correlate with the perceived line number from the preprocessed file
void BREN_Compiler::printLineMappingArray(){
	cout << "\t[Compiler]: Line Mapping Array:\n";
	for (int i = 0; i < globalNumLinesOfCodeInArray; i++){
		cout << "\t\tLine Number " << i << " is actually: " << globalLinesOfCodeArray[i] << endl;
	}
}
