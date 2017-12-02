/*
  ==============================================================================

	File: Compiler.h
	Author: Brendan Thompson
	Updated: 11/05/17

	Description: Interface for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- creates an instance of FileManager, SymbolTable, LiteralTable, and LineLabelTable
		- gets one line at a time and manages commands with command handling objects

  ==============================================================================
*/


// Reads in a user specified file and outputs it as trimmedOutput.txt after removing all white spaces and blank lines

/* ==============================================================================
	File Includes
============================================================================== */
#include <iostream>	// Console IO
#include <fstream>	// File IO
#include <stdlib.h>	// Exit()

#include "FileManager.h"
#include "SymbolTable.h"
#include "LiteralTable.h"
#include "LineLabelTable.h"

#include "./CompilerCommands/tREAD.h"
#include "./CompilerCommands/tWRITE.h"
#include "./CompilerCommands/tSTOP.h"
#include "./CompilerCommands/tDIM.h"
#include "./CompilerCommands/taREAD.h"
#include "./CompilerCommands/taWRITE.h"
#include "./CompilerCommands/tGOTO.h"
#include "./CompilerCommands/tLOOP.h"
#include "./CompilerCommands/tLOOPEND.h"
#include "./CompilerCommands/tIFA.h"
#include "./CompilerCommands/tNOP.h"
#include "./CompilerCommands/tLISTO.h"
#include "./CompilerCommands/tlREAD.h"
#include "./CompilerCommands/tlWRITE.h"
#include "./CompilerCommands/tIF.h"
#include "./CompilerCommands/tCLS.h"
#include "./CompilerCommands/tCDUMP.h"
#include "./CompilerCommands/tSUBP.h"
#include "./CompilerCommands/tASSIGNMENT.h"


using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

/* ==============================================================================
	Symbolic Constants
============================================================================== */
#define MAX_STRING_LENGTH 50
#define MAX_LINE_LENGTH 50
#define MAX_NUM_FLAGS 7
#define MAX_NUM_LINES_IN_TRANSY_PROGRAM 1000

/* ==============================================================================
	BREN_Compiler Class
============================================================================== */

class BREN_Compiler {
public:
	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */
	BREN_Compiler(); // Instantiates a BREN_Compiler object
	~BREN_Compiler();


	/* ==============================================================================
		Public Methods
	============================================================================== */

	// tells the FileManager to preprocess all the files in fileNameArray and instantiates the objects for handling commands
	bool prepareForCompilation(string fileToCompile, char *arrayOfFlags, int numberOfFlags);

	// Compiles the preprocessed .noblanks file into the final .obj, getting one line at a time and calling getCommand()
	bool compile();

private:
	/* ==============================================================================
		Private Member Variables
	============================================================================== */
	// string globalFileName;
	int numErrors;
	bool foundFirstLineAfterDIM;

	// Global Helper Objects
	FileManager globalFileManager;
	SymbolTable globalMemoryManager;
	LiteralTable globalLiteralManager;
	LineLabelTable globalLineManager;

	// objects for handling (translating) commands
	tREAD mainREADHandler;
	tWRITE mainWRITEHandler;
	tSTOP mainSTOPHandler;
	tDIM mainDIMHandler;
	taREAD mainAREADHandler;
	taWRITE mainAWRITEHandler;
	tGOTO mainGOTOHandler;
	tLOOP mainLOOPHandler;
	tLOOPEND mainLOOPENDHandler;
	tIFA mainIFAHandler;
	tNOP mainNOPHandler;
	tLISTO mainLISTOHandler;
	tlREAD mainLREADHandler;
	tlWRITE mainLWRITEHandler;
	tIF mainIFHandler;
	tCLS mainCLSHandler;
	tCDUMP mainCDUMPHandler;
	tSUBP mainSUBPHandler;
	tASSIGNMENT mainASSIGNMENTHandler;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// tells the appropriate object to handle the command in the line
	void handleCommand(string currentLine, int correspondingLineNumber);

	// iterates through the line one character at a time and returns whether or not it was assignment;
	bool checkForAssignment(string currentLine, int correspondingLineNumber);

	// instantiates objects for handling commands by passing the FileManager, MemoryManager, SymbolTable, LineLabelTable, and/or LiteralTable by reference
	void instantiateCommandObjects();
};



