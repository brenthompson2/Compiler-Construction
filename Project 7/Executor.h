/* ==============================================================================

	File: Executor.h
	Author: Brendan Thompson
	Updated: 11/20/17

	Description: Interface for Main Executor Object made for Transylvania University University Fall Term 2017 Executor Construction class
		- creates an instance of FileManager, SymbolTable, LiteralTable, LineLabelTable, and ProgramLineTable
		- gets one line at a time and manages commands with command handling objects

============================================================================== */

/* ==============================================================================
	File Includes
============================================================================== */
#include <iostream>	// Console IO
#include <fstream>	// File IO
#include <stdlib.h>	// Exit()

using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::string;

#include "EFileManager.h"
#include "SymbolTable.h"
#include "LiteralTable.h"
#include "ProgramLineTable.h"

#include "./ExecutorCommands/eREAD.h"
#include "./ExecutorCommands/eWRITE.h"
// #include "./ExecutorCommands/eSTOP.h" // NOT USING COMMAND HANDLER
#include "./ExecutorCommands/eDIM.h" // NOT YET IMPLEMENTED
#include "./ExecutorCommands/eaREAD.h" // NOT YET IMPLEMENTED
#include "./ExecutorCommands/eaWRITE.h" // NOT YET IMPLEMENTED
// #include "./ExecutorCommands/eGOTO.h"
// #include "./ExecutorCommands/eLOOP.h"
// #include "./ExecutorCommands/eLOOPEND.h"
// #include "./ExecutorCommands/eIFA.h"
// #include "./ExecutorCommands/eNOP.h" // NOT USING COMMAND HANDLER
// #include "./ExecutorCommands/eLISTO.h" // NOT USING COMMAND HANDLER
#include "./ExecutorCommands/elREAD.h"
#include "./ExecutorCommands/elWRITE.h"
// #include "./ExecutorCommands/eIF.h"
// #include "./ExecutorCommands/eCLS.h" // NOT USING COMMAND HANDLER
#include "./ExecutorCommands/eCDUMP.h"
#include "./ExecutorCommands/eSUBP.h" // NOT YET IMPLEMENTED
// #include "./ExecutorCommands/eASSIGNMENT.h"

/* ==============================================================================
	Symbolic Constants
============================================================================== */
#define MAX_STRING_LENGTH 50
#define MAX_VARIABLE_LENGTH 128
#define MAX_LINE_LENGTH 50
#define MAX_NUM_FLAGS 7
#define MAX_NUM_LINES_IN_TRANSY_PROGRAM 1000

/* ==============================================================================
	BREN_Executor Class
============================================================================== */

class BREN_Executor {
public:
	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */

	BREN_Executor();
	~BREN_Executor();


	/* ==============================================================================
		Public Methods
	============================================================================== */

	// Tells the FileManager to prepare the fileToExecute, handle flags, and fills the ProgramLineTable
	bool prepareForExecution(string fileToExecute, char *arrayOfFlags, int numberOfFlags);

	// Executes the .obj file by getting a line from ProgramLineTable and calling handleCommand()
	void execute();

private:
	/* ==============================================================================
		Private Member Variables
	============================================================================== */
	int globalNumErrors;
	bool globalFoundStopCommand;

	// Global Helper Objects
	EFileManager globalFileManager;
	SymbolTable globalMemoryManager;
	LiteralTable globalLiteralManager;
	ProgramLineTable globalProgramManager;

	// objects for handling (executing) commands
	eREAD mainREADHandler;
	eWRITE mainWRITEHandler;
	// eSTOP mainSTOPHandler; // NOT USING COMMAND HANDLER
	eDIM mainDIMHandler;
	eaREAD mainAREADHandler;
	eaWRITE mainAWRITEHandler;
	// eGOTO mainGOTOHandler;
	// eLOOP mainLOOPHandler;
	// eLOOPEND mainLOOPENDHandler;
	// eIFA mainIFAHandler;
	// eNOP mainNOPHandler; // NOT USING COMMAND HANDLER
	// eLISTO mainLISTOHandler; // NOT USING COMMAND HANDLER
	elREAD mainLREADHandler;
	elWRITE mainLWRITEHandler;
	// eIF mainIFHandler;
	// eCLS mainCLSHandler; // NOT USING COMMAND HANDLER
	eCDUMP mainCDUMPHandler;
	eSUBP mainSUBPHandler;
	// eASSIGNMENT mainASSIGNMENTHandler;

	/* ==============================================================================
		Private Methods
	============================================================================== */

	// tells the appropriate object to handle the command in the line
	void handleCommand(ProgramLineObject currentLineObject, int *currentProgramCounter);

	// instantiates objects for handling commands by passing the FileManager, MemoryManager, SymbolTable, LineLabelTable, and/or LiteralTable by reference
	void instantiateCommandObjects();
};



