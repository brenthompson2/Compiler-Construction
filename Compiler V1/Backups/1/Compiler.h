/*
  ==============================================================================

	File: Compiler.h
	Author: Brendan Thompson
	Updated: 09/24/17

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
#include "tREAD.h"
#include "tWRITE.h"
#include "tSTOP.h"

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

/* ==============================================================================
	BREN_Compiler Class
============================================================================== */

class BREN_Compiler {
public:
	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */
	BREN_Compiler(); // Instantiates a BREN_Compiler object which creates an instance of FileManager
	void shutdown();


	/* ==============================================================================
		Public Methods
	============================================================================== */
	void compile(); // Compiles the preprocessed .noblanks file into the final .obj

private:
	/* ==============================================================================
		Private Member Variables
	============================================================================== */
	FileManager globalFileManager;
	LookupTable globalMemoryManager;
	unsigned int numErrors;

	// command handling objects
	tREAD mainREADHandler;
	tWRITE mainWRITEHandler;
	tSTOP mainSTOPHandler;



	/* ==============================================================================
		Private Methods
	============================================================================== */
	void parseLine(string currentLine); // Parses the line and calls the appropriate function based off the command

	void instantiateCommandObjects(); //
};



