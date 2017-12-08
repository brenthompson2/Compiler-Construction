/* ==============================================================================

	File: EFileManager.cpp
	Author: Brendan Thompson
	Updated: 11/16/17

	Description: Implementation of main EFileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- opens .obj, .literal, and .core files
		- syncs objInputFile with ParentProgramManager
		- syncs literalInputFile with ParentLiteralManager
		- syncs coreInputFile with ParentMemoryManager

============================================================================== */

#include "EFileManager.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

// Instantiates a EFileManager object
EFileManager::EFileManager(){
	// keepObjFlag = false;
	// keepNoBlanksFlag = false;
	// keepLiteralFlag = false;
	// keepCoreFlag = false;
	// cout << "\t\t[EFileManager]: Initialized EFileManager\n";
	return ;
}

// Shuts down the EFileManager by calling removeFiles()
EFileManager::~EFileManager(){
	// cout << "\t\t[FILE MANAGER]: Shutdown EFileManager\n";
	return;
}

/* ==============================================================================
	Public Pre-Execution Methods
============================================================================== */

// Sets the EFileManagers's Global FileNames and links with the parentProgramManager, parentMemoryManager, parentLiteralManager
bool EFileManager::prepareForExecution(string fileToExecute, ProgramLineTable *currentProgramManager, SymbolTable *currentMemoryManager, LiteralTable *currentLiteralManager){
	// cout << "\t\t[FILE MANAGER]: Preparing For Execution..." << endl;
	bool successfullyPrepared = false;

	ParentProgramManager = currentProgramManager;
	ParentMemoryManager = currentMemoryManager;
	ParentLiteralManager = currentLiteralManager;

	// Create Global File Names & Open All Files
	createFileNames(fileToExecute);
	successfullyPrepared = openFiles();
	if (successfullyPrepared){
		loadProgram();
	}
	else {
		cout << "\t\t[FILE MANAGER]: Error! Unable to Open Files for Input\n";
	}

	return successfullyPrepared;
}

// Loads the objInputFile, literalInputFile, and coreInputFile into their associated data structure
void EFileManager::loadProgram(){
	loadProgramLines();
	loadLiterals();
	loadCoreMemory();
	closeFiles();
	return;
}

/* ==============================================================================
	Private File Management Functions
============================================================================== */

// Sets the global file names
void EFileManager::createFileNames(string originalFileName){
	char fileStem[MAX_STRING_LENGTH]; // globalFileStem += .obj

	// Clear the File Names
	strcpy(fileStem, "");
	strcpy(globalObjFileName, "");
	strcpy(globalLiteralFileName, "");
	strcpy(globalCoreFileName, "");

	// Prepare to parse the originalFileName and get the stem
	bool notFinished = true;
	int iterator = 0;
	char currentCharacter;

    // cout << "Attempting to find stem of " << originalFileName << endl;
    while (notFinished){
    	currentCharacter = originalFileName[iterator];
    	// cout << "CurrentChar: " << currentCharacter << endl;
    	if (currentCharacter == '.'){
    		fileStem[iterator] = '\0';
    		notFinished = false;
    	}
    	else {
    		fileStem[iterator] = currentCharacter;
    	}
    	iterator++;
    }

    // create other file names
    strcpy(globalObjFileName, fileStem);
	strcat(globalObjFileName, objInFileType);
    strcpy(globalLiteralFileName, fileStem);
	strcat(globalLiteralFileName, literalInFileType);
    strcpy(globalCoreFileName, fileStem);
	strcat(globalCoreFileName, coreInFileType);

	// cout << "\nTransy File\t\tStem\t\tNo Blank File\t\tPreprocessedFile\t\tobjOutFile\n";
	// cout << originalFileName << "\t" << fileStem << "\t" << globalObjFileName << "\t" << globalLiteralFileName << "\t" << globalCoreFileName << endl;
	// cout << endl;

	return;
}

// opens .obj, .core, & .literal input files
bool EFileManager::openFiles(){
	// INFILES
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalObjFileName << " for input..." << endl;
    objInputFile.open(globalObjFileName);
    if (!objInputFile) {
        cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open " << globalObjFileName << " for input" << endl;
        return false;
    }

    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalLiteralFileName << " for input..." << endl;
	literalInputFile.open(globalLiteralFileName);
	if (!literalInputFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .literal input file" <<endl;
        return false;
	}

    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalCoreFileName << " for input..." << endl;
	coreInputFile.open(globalCoreFileName);
	if (!coreInputFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .core input file" <<endl;
        return false;
	}

	return true;
}

// closes .obj, .core, & .literal input files
void EFileManager::closeFiles(){
	objInputFile.close();
	literalInputFile.close();
	coreInputFile.close();
}

/* ==============================================================================
	Private Load Functions
============================================================================== */

// Reads the objInputFile and syncs lines with the ParentProgramManager
void EFileManager::loadProgramLines(){
	string currentLine;
	while (!(objInputFile.eof())){
		getline(objInputFile, currentLine);
		(*ParentProgramManager).addLine(currentLine);
	}
	return;
}

// Parses the literalInputFile and syncs lines with the ParentLiteralManager
void EFileManager::loadLiterals(){
	string currentLine;
	while (!(literalInputFile.eof())){
		getline(literalInputFile, currentLine);
		(*ParentLiteralManager).loadLine(currentLine);
	}
	return;
}

// Parses the coreInputFile and syncs lines with the ParentMemoryManager
void EFileManager::loadCoreMemory(){
	string currentLine;
	while (!(coreInputFile.eof())){
		getline(coreInputFile, currentLine);
		(*ParentMemoryManager).loadLine(currentLine);
	}
	return;
}