/*
  ==============================================================================

	File: Compiler.cpp
	Author: Brendan Thompson
	Updated: 10/12/17

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
	instantiateCommandObjects();
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
bool BREN_Compiler::prepareForCompilation(string fileToCompile, char *arrayOfFlags, int numberOfFlags){
	bool successfullyPrepared = false;

	// Set Member Variables
	globalFileName = fileToCompile;
	globalFileManager.setFlags(arrayOfFlags, numberOfFlags);

	// PreProcess File
	successfullyPrepared = globalFileManager.prepareForCompilation(fileToCompile, &globalLineManager);
	if (successfullyPrepared){
		successfullyPrepared = globalFileManager.preprocessFile();
	}

	globalLineManager.printLineLabelTable();

	return successfullyPrepared;
}

// Compiles the preprocessed .noblanks file into the final .obj, getting one line at a time and calling getCommand()
void BREN_Compiler::compile(){
	string currentLine;
	bool continueCompiling = true;
	int lineCount = 0;
	int actualLineNumber;


	currentLine = globalFileManager.getNextLine();
	actualLineNumber = globalLineManager.getTransyLineNumber(lineCount);
	cout << "\t[Compiler]: Attempting to Compile Input File Line number: " << actualLineNumber << endl;
	if (currentLine == FILE_END_SENTINEL){
		continueCompiling = false;
		cout << "\t[Compiler]: ERROR: File appears to be empty\n";
	}

	while (continueCompiling){
		getCommand(currentLine, actualLineNumber);

		currentLine = globalFileManager.getNextLine();
		lineCount++;
		actualLineNumber = globalLineManager.getTransyLineNumber(lineCount);

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
void BREN_Compiler::getCommand(string currentLine, int correspondingLineNumber){
	char currentCharacter = currentLine[0];
	switch (currentCharacter){
		case 'A':
			// AREAD
			if ((currentLine[1] == 'R') && (currentLine[2] == 'E') && (currentLine[3] == 'A') && (currentLine[4] == 'D')){
				// cout << "\t[Compiler]: Found aREAD Command\n";
				numErrors += mainAREADHandler.handleAREAD(currentLine, correspondingLineNumber);
			}
			// AWRITE
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
		case 'C':
			// CLS
			if ((currentLine[1] == 'L') && (currentLine[2] == 'S')){
				// cout << "\t[Compiler]: Found CLS Command\n";
				numErrors += mainCLSHandler.handleCLS(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'D':
			// DIM
			if ((currentLine[1] == 'I') && (currentLine[2] == 'M')){
				// cout << "\t[Compiler]: Found Dim Command\n";
				numErrors += mainDIMHandler.handleDIM(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'G':
			// DIM
			if ((currentLine[1] == 'O') && (currentLine[2] == 'T') && (currentLine[3] == 'O')){
				// cout << "\t[Compiler]: Found GOTO Command\n";
				numErrors += mainGOTOHandler.handleGOTO(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'I':
			// DIM
			if ((currentLine[1] == 'F') && (currentLine[2] == 'A')){
				// cout << "\t[Compiler]: Found IFA Command\n";
				numErrors += mainIFAHandler.handleIFA(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'L':
			if ((currentLine[1] == 'I') && (currentLine[2] == 'S') && (currentLine[3] == 'T') && (currentLine[4] == 'O')){
				// LISTO
				// cout << "\t[Compiler]: Found LISTO Command\n";
				numErrors += mainLISTOHandler.handleLISTO(currentLine, correspondingLineNumber);
			}
			else {
				if ((currentLine[1] == 'O') && (currentLine[2] == 'O') && (currentLine[3] == 'P')){
					// LOOP-END
					if ((currentLine[4] == '-') && (currentLine[5] == 'E') && (currentLine[6] == 'N') && (currentLine[7] == 'D')){
						// cout << "\t[Compiler]: Found LOOPEND Command\n";
						numErrors += mainLOOPENDHandler.handleLOOPEND(currentLine, correspondingLineNumber);
					}
					// LOOP
					else {
						// cout << "\t[Compiler]: Found LOOP Command\n";
						numErrors += mainLOOPHandler.handleLOOP(currentLine, correspondingLineNumber);
					}
				}
				else {
					cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
					numErrors++;
				}
			}
			break;
		case 'N':
			// NOP
			if ((currentLine[1] == 'O') && (currentLine[2] == 'P')){
				// cout << "\t[Compiler]: Found NOP Command\n";
				numErrors += mainNOPHandler.handleNOP(currentLine, correspondingLineNumber);
			}
			else {
				cout << "\t[Compiler]: Invalid Command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
				numErrors++;
			}
			break;
		case 'R':
			// READ
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
			// STOP
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
			// WRITE
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

// instantiates objects for handling commands by passing the FileManager, MemoryManager, SymbolTable, LineLabelTable, and/or LiteralTable by reference
void BREN_Compiler::instantiateCommandObjects(){
	mainREADHandler.prepareREAD(&globalFileManager, &globalMemoryManager);
	mainWRITEHandler.prepareWRITE(&globalFileManager, &globalMemoryManager);
	mainSTOPHandler.prepareSTOP(&globalFileManager);

	mainDIMHandler.prepareDIM(&globalFileManager, &globalMemoryManager);
	mainAREADHandler.prepareAREAD(&globalFileManager, &globalMemoryManager);
	mainAWRITEHandler.prepareAWRITE(&globalFileManager, &globalMemoryManager);

	mainGOTOHandler.prepareGOTO(&globalFileManager, &globalLineManager);
	mainLOOPHandler.prepareLOOP(&globalFileManager, &globalMemoryManager);
	mainLOOPENDHandler.prepareLOOPEND(&globalFileManager);
	mainIFAHandler.prepareIFA(&globalFileManager, &globalMemoryManager, &globalLineManager);
	mainNOPHandler.prepareNOP(&globalFileManager);
	mainLISTOHandler.prepareLISTO(&globalFileManager);

	// mainLREADHandler.prepareLREAD(&globalFileManager);
	// mainLWRITEHandler.prepareLWRITE(&globalFileManager);
	// mainIFAHandler.prepareIFA(&globalFileManager);
	mainCLSHandler.prepareCLS(&globalFileManager);
	// mainCDUMPHandler.prepareCDUMP(&globalFileManager);
	// mainSUBPHandler.prepareSUBP(&globalFileManager);
}
