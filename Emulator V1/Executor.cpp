/* ==============================================================================

	File: Executor.cpp
	Author: Brendan Thompson
	Updated: 11/13/17

	Description: Interface for Main Executor Object made for Transylvania University University Fall Term 2017 Executor Construction class
		- creates an instance of FileManager, SymbolTable, LiteralTable, and LineLabelTable
		- gets one line at a time and manages commands with command handling objects

============================================================================== */

#include "Executor.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

// Instantiates a BREN_Executor object, tell FileManager to preprocess .transy file, and instantiates objects for handling commands
BREN_Executor::BREN_Executor (){
	numErrors = 0;
	instantiateCommandObjects();
	cout << "\t[Executor]: Initialized Executor\n";
	return;
}

// Shuts Down the BREN_Executor object
BREN_Executor::~BREN_Executor (){
	cout << "\t[Executor]: Shutdown BREN_Executor\n";
	return;
}

/* ==============================================================================
	Public Methods
============================================================================== */

// Tells the FileManager to prepare the fileToExecute, handle flags, and fills the ProgramLineTable
bool BREN_Executor::prepareForExecution(string fileToExecute, char *arrayOfFlags, int numberOfFlags){
	bool successfullyPrepared = false;

	// Set Member Variables
	// globalFileName = fileToExecute;
	globalFileManager.setFlags(arrayOfFlags, numberOfFlags);
	globalLiteralManager.linkWithParentFileManager(&globalFileManager);
	globalMemoryManager.linkWithParentFileManager(&globalFileManager);

	// PreProcess File
	// cout << "\t[Executor]: Attempting to preprocess file...\n";
	successfullyPrepared = globalFileManager.prepareForCompilation(fileToExecute, &globalLineManager);
	if (successfullyPrepared){
		successfullyPrepared = globalFileManager.preprocessFile();
	}
	numErrors += globalLineManager.syncLabelsWithLines();

	// globalLineManager.printLineLabelTable();

	return successfullyPrepared;
}

// Executes the .obj file by getting a line from ProgramLineTable and calling handleCommand()
void BREN_Executor::execute(){
	string currentLine;
	bool continueCompiling = true;
	int lineCount = 0;
	int actualLineNumber;


	currentLine = globalFileManager.getNextLine();
	actualLineNumber = globalLineManager.getTransyLineNumber(lineCount);
	cout << "\t[Executor]: Attempting to Compile Input File Line number: " << actualLineNumber << endl;
	if (actualLineNumber == NOT_FOUND_IN_ARRAY){
		continueCompiling = false;
		cout << "\t[Executor]: ERROR: File appears to be empty\n";
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
			cout << "\n\t[Executor]: Attempting to Compile Input File Line number: " << actualLineNumber << ": " << currentLine << endl;
		}
	}

	// Manage Compilation Result
	if (numErrors == 0){
		cout << "\n\t[Executor]: Successfully Compiled the file\n";
		globalFileManager.setCompilationResult(true);
		globalMemoryManager.setCompilationResult(SUCCESSFULLY_COMPILED);
	}
	else {
		cout << "\n\t[Executor]: Completed Compiling with " << numErrors << " errors\n";
		globalMemoryManager.setCompilationResult(FAILED_COMPILATION);
	}

	// Output Core & Literal Files
	// globalMemoryManager.printSymbolTable();
	globalMemoryManager.outputCoreFile();
	// globalLiteralManager.printLiteralTable();
	globalLiteralManager.outputLiteralFile();
	// globalLineManager.printLineLabelTable();
	// globalLineManager.printLineMapping();

	return;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// tells the appropriate object to handle the command in the line
void BREN_Executor::handleCommand(string currentLine, int correspondingLineNumber){
	char currentCharacter = currentLine[0];
	bool caseFound = false;

	// if (checkForAssignment(currentLine, correspondingLineNumber)){
	// 	// cout << "\t[Executor]: Found Assignment Command\n";
	// 	numErrors += mainASSIGNMENTHandler.handleASSIGNMENT(currentLine, correspondingLineNumber);
	// 	caseFound = true;
	// }
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "AREAD", 5)))){
		// cout << "\t[Executor]: Found aREAD Command\n";
		numErrors += mainAREADHandler.handleAREAD(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "AWRITE", 6)))){
		// cout << "\t[Executor]: Found aWRITE Command\n";
		numErrors += mainAWRITEHandler.handleAWRITE(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "CDUMP", 5)))){
		// cout << "\t[Executor]: Found CDUMP Command\n";
		numErrors += mainCDUMPHandler.handleCDUMP(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "CLS", 3)))){
		// cout << "\t[Executor]: Found CLS Command\n";
		numErrors += mainCLSHandler.handleCLS(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "DIM", 3)))){
		// cout << "\t[Executor]: Found DIM Command\n";
		numErrors += mainDIMHandler.handleDIM(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "GOTO", 4)))){
		// cout << "\t[Executor]: Found GOTO Command\n";
		numErrors += mainGOTOHandler.handleGOTO(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "IFA", 3)))){
		// cout << "\t[Executor]: Found IFA Command\n";
		numErrors += mainIFAHandler.handleIFA(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	else {
		if (!(strncmp(currentLine.c_str(), "IF", 2))){
			// cout << "\t[Executor]: Found IF Command\n";
			numErrors += mainIFHandler.handleIF(currentLine, correspondingLineNumber);
			caseFound = true;
		}
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LISTO", 5)))){
		// cout << "\t[Executor]: Found LISTO Command\n";
		numErrors += mainLISTOHandler.handleLISTO(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LOOP-END", 8)))){
		// cout << "\t[Executor]: Found LOOPEND Command\n";
		numErrors += mainLOOPENDHandler.handleLOOPEND(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	else {
		if (!(strncmp(currentLine.c_str(), "LOOP", 4))){
			// cout << "\t[Executor]: Found LOOP Command\n";
			numErrors += mainLOOPHandler.handleLOOP(currentLine, correspondingLineNumber);
			caseFound = true;
		}
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LREAD", 5)))){
		// cout << "\t[Executor]: Found lREAD Command\n";
		numErrors += mainLREADHandler.handleLREAD(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "LWRITE", 6)))){
		// cout << "\t[Executor]: Found lWRITE Command\n";
		numErrors += mainLWRITEHandler.handleLWRITE(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "NOP", 3)))){
		// cout << "\t[Executor]: Found NOP Command\n";
		numErrors += mainNOPHandler.handleNOP(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "READ", 4)))){
		// cout << "\t[Executor]: Found READ Command\n";
		numErrors += mainREADHandler.handleREAD(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "STOP", 4)))){
		// cout << "\t[Executor]: Found STOP Command\n";
		numErrors += mainSTOPHandler.handleSTOP(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "SUBP", 4)))){
		// cout << "\t[Executor]: Found SUBP Command\n";
		numErrors += mainSUBPHandler.handleSUBP(currentLine, correspondingLineNumber);
		caseFound = true;
	}
	if ((!caseFound) && (!(strncmp(currentLine.c_str(), "WRITE", 5)))){
		// cout << "\t[Executor]: Found WRITE Command\n";
		numErrors += mainWRITEHandler.handleWRITE(currentLine, correspondingLineNumber);
		caseFound = true;
	}

	if (!caseFound){
		cerr << "\t[Executor]: ERROR: Failed to interpret command in line " << correspondingLineNumber << ": " <<  currentLine << endl << endl << endl;
	}
}

// instantiates objects for handling commands by passing the FileManager, MemoryManager, SymbolTable, LineLabelTable, and/or LiteralTable by reference
void BREN_Executor::instantiateCommandObjects(){
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

	mainASSIGNMENTHandler.prepareASSIGNMENT(&globalFileManager, &globalMemoryManager);
}
