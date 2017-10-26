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
#include "LineLabelTable.h"

#include "tREAD.h"
#include "tWRITE.h"
#include "STOP.h"
#include "DIM.h"
#include "aREAD.h"
#include "aWRITE.h"
#include "GOTO.h"
#include "LOOP.h"
#include "LOOPEND.h"
#include "IFA.h"
#include "NOP.h"
#include "LISTO.h"


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
	string globalFileName;
	int numErrors;

	// Global Helper Objects
	FileManager globalFileManager;
	SymbolTable globalMemoryManager;
	LineLabelTable globalLineManager;

	// objects for handling commands
	tREAD mainREADHandler;
	tWRITE mainWRITEHandler;
	STOP mainSTOPHandler;
	DIM mainDIMHandler;
	aREAD mainAREADHandler;
	aWRITE mainAWRITEHandler;
	GOTO mainGOTOHandler;
	LOOP mainLOOPHandler;
	LOOPEND mainLOOPENDHandler;
	IFA mainIFAHandler;
	NOP mainNOPHandler;
	LISTO mainLISTOHandler;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// iterates through the line one character at a time and tells the appropriate object to handle the command
	void getCommand(string currentLine, int correspondingLineNumber);

	// instantiates objects for handling commands by passing the FileManager & MemoryManager by reference
	void instantiateCommandObjects();
};



