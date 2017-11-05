/*
  ==============================================================================

	File: Compiler.cpp
	Author: Brendan Thompson
	Updated: 11/05/17

	Description: Interface for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- creates an instance of FileManager, SymbolTable, LiteralTable, and LineLabelTable
		- gets one line at a time and manages commands with command handling objects

  ==============================================================================
*/

#include "Compiler.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

// Instantiates a BREN_Compiler object, tell FileManager to preprocess .transy file, and instantiates objects for handling commands
BREN_Compiler::BREN_Compiler (){
	numErrors = 0;
	foundFirstLineAfterDIM = false;
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
	// globalFileName = fileToCompile;
	globalFileManager.setFlags(arrayOfFlags, numberOfFlags);
	globalLiteralManager.linkWithParentFileManager(&globalFileManager);
	globalMemoryManager.linkWithParentFileManager(&globalFileManager);

	// PreProcess File
	// cout << "\t[Compiler]: Attempting to preprocess file...\n";
	successfullyPrepared = globalFileManager.prepareForCompilation(fileToCompile, &globalLineManager);
	if (successfullyPrepared){
		successfullyPrepared = globalFileManager.preprocessFile();
	}
	numErrors += globalLineManager.syncLabelsWithLines();

	// globalLineManager.printLineLabelTable();

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
	if (actualLineNumber == NOT_FOUND_IN_ARRAY){
		continueCompiling = false;
		cout << "\t[Compiler]: ERROR: File appears to be empty\n";
	}

	while (continueCompiling){
		handleCommand(currentLine, actualLineNumber);

		currentLine = globalFileManager.getNextLine();
		lineCount++;
		actualLineNumber = globalLineManager.getTransyLineNumber(lineCount);

		if (currentLine == FILE_END_SENTINEL){
			continueCompiling = false;
		}
		else {
			cout << "\n\t[Compiler]: Attempting to Compile Input File Line number: " << actualLineNumber << ": " << currentLine << endl;
		}
	}

	// Manage Compilation Result
	if (numErrors == 0){
		cout << "\n\t[Compiler]: Successfully Compiled the file\n";
		globalFileManager.setCompilationResult(true);
		globalMemoryManager.setCompilationResult(SUCCESSFULLY_COMPILED);
	}
	else {
		cout << "\n\t[Compiler]: Completed Compiling with " << numErrors << " errors\n";
		globalMemoryManager.setCompilationResult(FAILED_COMPILATION);
	}

	// Output Core & Literal Files
	// globalMemoryManager.printSymbolTable();
	globalMemoryManager.outputCoreFile();
	globalLiteralManager.printLiteralTable();
	globalLiteralManager.outputLiteralFile();
	// globalLineManager.printLineLabelTable();
	// globalLineManager.printLineMapping();

	return;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// tells the appropriate object to handle the command in the line
void BREN_Compiler::handleCommand(string currentLine, int correspondingLineNumber){
	char currentCharacter = currentLine[0];
	bool caseFound = false;

	if (checkForAssignment(currentLine, correspondingLineNumber)){
		// cout << "\t[Compiler]: Found Assignment Command\n";
		// numErrors += mainASSIGNMENTHandler.handleASSIGNMENT(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}

	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "AREAD", 5)))){
		// cout << "\t[Compiler]: Found aREAD Command\n";
		numErrors += mainAREADHandler.handleAREAD(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "AWRITE", 6)))){
		// cout << "\t[Compiler]: Found aWRITE Command\n";
		numErrors += mainAWRITEHandler.handleAWRITE(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "CDUMP", 5)))){
		// cout << "\t[Compiler]: Found CDUMP Command\n";
		numErrors += mainCDUMPHandler.handleCDUMP(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "CLS", 3)))){
		// cout << "\t[Compiler]: Found CLS Command\n";
		numErrors += mainCLSHandler.handleCLS(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "DIM", 3)))){
		// cout << "\t[Compiler]: Found DIM Command\n";
		if (foundFirstLineAfterDIM) {
			cerr << "\t[Compiler]: ERROR: Found DIM Command not at top of file on line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
			numErrors++;
		}
		else {
			numErrors += mainDIMHandler.handleDIM(currentLine, correspondingLineNumber);
		}
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "GOTO", 4)))){
		// cout << "\t[Compiler]: Found GOTO Command\n";
		numErrors += mainGOTOHandler.handleGOTO(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "IFA", 3)))){
		// cout << "\t[Compiler]: Found IFA Command\n";
		numErrors += mainIFAHandler.handleIFA(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	else {
		if (!(strncmp(currentLine.c_str(), "IF", 2))){
			// cout << "\t[Compiler]: Found IF Command\n";
			numErrors += mainIFHandler.handleIF(currentLine, correspondingLineNumber);
			caseFound = true;
			foundFirstLineAfterDIM = true;
		}
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LISTO", 5)))){
		// cout << "\t[Compiler]: Found LISTO Command\n";
		numErrors += mainLISTOHandler.handleLISTO(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LOOP-END", 8)))){
		// cout << "\t[Compiler]: Found LOOPEND Command\n";
		numErrors += mainLOOPENDHandler.handleLOOPEND(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	else {
		if (!(strncmp(currentLine.c_str(), "LOOP", 4))){
			// cout << "\t[Compiler]: Found LOOP Command\n";
			numErrors += mainLOOPHandler.handleLOOP(currentLine, correspondingLineNumber);
			caseFound = true;
			foundFirstLineAfterDIM = true;
		}
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LREAD", 5)))){
		// cout << "\t[Compiler]: Found lREAD Command\n";
		numErrors += mainLREADHandler.handleLREAD(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LWRITE", 6)))){
		// cout << "\t[Compiler]: Found lWRITE Command\n";
		numErrors += mainLWRITEHandler.handleLWRITE(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "NOP", 3)))){
		// cout << "\t[Compiler]: Found NOP Command\n";
		numErrors += mainNOPHandler.handleNOP(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "READ", 4)))){
		// cout << "\t[Compiler]: Found READ Command\n";
		numErrors += mainREADHandler.handleREAD(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "STOP", 4)))){
		// cout << "\t[Compiler]: Found STOP Command\n";
		numErrors += mainSTOPHandler.handleSTOP(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "SUBP", 4)))){
		// cout << "\t[Compiler]: Found SUBP Command\n";
		numErrors += mainSUBPHandler.handleSUBP(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "WRITE", 5)))){
		// cout << "\t[Compiler]: Found WRITE Command\n";
		numErrors += mainWRITEHandler.handleWRITE(currentLine, correspondingLineNumber);
		caseFound = true;
		foundFirstLineAfterDIM = true;
	}

	if (!caseFound){
		cerr << "\t[Compiler]: ERROR: Failed to interpret command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
	}
}

// iterates through the line one character at a time returns whether or not it was assignment;
bool BREN_Compiler::checkForAssignment(string currentLine, int correspondingLineNumber){
	char currentCharacter;
	bool foundEquals = false;
	bool foundComma = false;
	bool isAssignment = false;

	for (int characterIterator = 0; characterIterator < currentLine.size(); characterIterator++){
		currentCharacter = currentLine[characterIterator];

		if (currentCharacter == '='){
			foundEquals = true;
		}

		if (currentCharacter == ','){
			foundComma = true;
		}
	}

	if (foundEquals && (!foundComma)){
		isAssignment = true;

	}

	return isAssignment;
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

	mainLREADHandler.prepareLREAD(&globalFileManager, &globalLiteralManager);
	mainLWRITEHandler.prepareLWRITE(&globalFileManager, &globalLiteralManager);
	mainIFHandler.prepareIF(&globalFileManager, &globalMemoryManager, &globalLineManager);
	mainCLSHandler.prepareCLS(&globalFileManager);
	mainCDUMPHandler.prepareCDUMP(&globalFileManager, &globalMemoryManager);
	mainSUBPHandler.prepareSUBP(&globalFileManager, &globalMemoryManager);

	// mainASSIGNMENTHandler.prepareASSIGNMENT();
}
