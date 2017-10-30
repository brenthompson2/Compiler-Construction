/*
  ==============================================================================

	File: Compiler.h
	Author: Brendan Thompson
	Updated: 10/08/17

	Description: Interface for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class

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

#include "tREAD.h"
#include "tWRITE.h"
#include "tSTOP.h"
#include "tDIM.h"
#include "taREAD.h"
#include "taWRITE.h"
#include "tGOTO.h"
#include "tLOOP.h"
#include "tLOOPEND.h"
#include "tIFA.h"
#include "tNOP.h"
#include "tLISTO.h"
#include "tlREAD.h"
#include "tlWRITE.h"
#include "tIF.h"
#include "tCLS.h"
// #include "tCDUMP.h"
// #include "tSUBP.h"


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
	void compile();

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
	// tCDUMP mainCDUMPHandler;
	// tSUBP mainSUBPHandler;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// iterates through the line one character at a time and tells the appropriate object to handle the command
	void handleCommand(string currentLine, int correspondingLineNumber);

	// instantiates objects for handling commands by passing the FileManager, MemoryManager, SymbolTable, LineLabelTable, and/or LiteralTable by reference
	void instantiateCommandObjects();
};



