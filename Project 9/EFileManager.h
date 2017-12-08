/* ==============================================================================

	File: EFileManager.cpp
	Author: Brendan Thompson
	Updated: 11/16/17

	Description: Implementation of main EFileManager for Executor made for Transylvania University University Fall Term 2017 Compiler Construction class
		- opens .obj, .literal, and .core files
		- syncs objInputFile with ParentProgramManager
		- syncs literalInputFile with ParentLiteralManager
		- syncs coreInputFile with ParentMemoryManager

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include "ProgramLineTable.h"
#include "LiteralTable.h"
#include "CoreMemory.h"

#include <iostream>	// Console IO
#include <iomanip> // std::setprecision()
#include <fstream>	// File IO
#include <stdio.h>	// remove()
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat
#include <string> // getline() substr()
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::fstream;
using std::ofstream;
using std::string;
using std::getline;

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_STRING_LENGTH 50
#define MAX_LINE_LENGTH 50
#define FILE_END_SENTINEL "@"
#define NO_LINE_LABEL -1

// File Prefixes
const char objInFileType[5] = ".obj";
const char literalInFileType[9] = ".literal";
const char coreInFileType[6] = ".core";

/* ==============================================================================
	File Manager Class Interface
============================================================================== */

class EFileManager {
public:
	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */

	EFileManager(); // Instantiates a EFileManager object
	~EFileManager(); // Shuts down the EFileManager by  calling removeFiles()

	/* ==============================================================================
		Public Pre-Execution Methods
	============================================================================== */

	// Sets the EFileManagers's Global FileNames & Links to the Parent's LineManager
	bool prepareForExecution(string fileToExecute, ProgramLineTable *currentProgramManager, CoreMemory *currentMemoryManager, LiteralTable *currentLiteralManager);

	// Loads the objInputFile, literalInputFile, and coreInputFile into their associated data structure
	void loadProgram();

private:
	/* ==============================================================================
		Private Members
	============================================================================== */

	// Files & File Names
	ifstream objInputFile; // <fileName>.obj
	ifstream literalInputFile; // <fileName>.literal
	ifstream coreInputFile; // <fileName>.core
	char globalObjFileName[MAX_STRING_LENGTH]; // globalFileStem += .obj
	char globalLiteralFileName[MAX_STRING_LENGTH]; // globalFileStem += .literal
	char globalCoreFileName[MAX_STRING_LENGTH]; // globalFileStem += .core

	// Parent's Objects
	ProgramLineTable *ParentProgramManager;
	LiteralTable *ParentLiteralManager;
	CoreMemory *ParentMemoryManager;

	/* ==============================================================================
		Private File Management Functions
	============================================================================== */

	// Sets the global file names
	void createFileNames(string originalFileName);

	// opens .obj, .core, & .literal input files
	bool openFiles();

	// closes .obj, .core, & .literal input files
	void closeFiles();


	// /* ==============================================================================
	// 	Private Load Functions
	// ============================================================================== */

	// Reads the objInputFile and syncs lines with the ParentProgramManager
	void loadProgramLines();

	// Parses the literalInputFile and syncs lines with the ParentLiteralManager
	void loadLiterals();

	// Parses the coreInputFile and syncs lines with the ParentMemoryManager
	void loadCoreMemory();
};


