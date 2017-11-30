/* ==============================================================================

	File: Executor.cpp
	Author: Brendan Thompson
	Updated: 11/30/17

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
	globalFoundStopCommand = false;
	globalNumErrors = 0;
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

	// Handle Flags

	// Load Program
	// cout << "\t[Executor]: Attempting to load " << fileToExecute << "...\n";
	successfullyPrepared = globalFileManager.prepareForExecution(fileToExecute, &globalProgramManager, &globalMemoryManager, &globalLiteralManager);

	// Print Program, Core, & Literal Tables
	globalProgramManager.printProgramLineTable();
	// globalMemoryManager.printCoreMemory();
	// globalLiteralManager.ePrintLiteralTable();

	return successfullyPrepared;
}

// Executes the .obj file by getting a line from globalProgramManager and calling handleCommand()
void BREN_Executor::execute(){
	ProgramLineObject *currentProgramLine;
	bool continueCompiling = true;
	int linesRunCount = 0;
	int programCounter = 0;

	while (continueCompiling){
		currentProgramLine = globalProgramManager.getCopyOfNextProgramObject(programCounter);
		if ((*currentProgramLine).numElementsInLine != END_OF_PROGRAM){
			handleCommand((*currentProgramLine), &programCounter);
			linesRunCount++;
		}
		else {
			if (!globalFoundStopCommand){
				cout << "\n\t[Warning]: Finished Executing without STOP command\n";
			}
			continueCompiling = false;
		}

		if (globalFoundStopCommand){
			continueCompiling = false;
		}

	}

	// globalMemoryManager.printCoreMemory();

	// Manage Execution Result
	if (globalNumErrors == 0){
		cout << "\n\t[Executor]: Successfully Executed the file\n";
	}
	else {
		cout << "\n\t[Executor]: Completed Executing with " << globalNumErrors << " errors\n";
	}

	return;
}

/* ==============================================================================
	Private Methods
============================================================================== */

// tells the appropriate object to handle the command in the line
void BREN_Executor::handleCommand(ProgramLineObject currentLineObject, int *currentProgramCounter){
	int currentOpCode = currentLineObject.opCode;

	switch (currentOpCode){
		case DIM_OP_CODE: // 0
			// cout << "\t[Executor]: Found DIM Command\n";
			mainDIMHandler.handleDIM(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case READ_OP_CODE: // 1
			// cout << "\t[Executor]: Found READ Command\n";
			mainREADHandler.handleREAD(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case WRITE_OP_CODE: // 2
			// cout << "\t[Executor]: Found WRITE Command\n";
			mainWRITEHandler.handleWRITE(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case STOP_OP_CODE: // 3
			// cout << "\t[Executor]: Found STOP command\n";
			// mainSTOPHandler.handleSTOP(&currentLineObject); // NOT USING COMMAND HANDLER
			(*currentProgramCounter) = END_OF_PROGRAM;
			globalFoundStopCommand = true;
			break;
		case 4: // 4
			cout << "\t[Executor]: Error: Found Invalid Op Code 4\n";
			globalNumErrors++;
			(*currentProgramCounter)++;
			break;
		case CDUMP_OP_CODE: // 5
			// cout << "\t[Executor]: Found CDUMP Command\n";
			mainCDUMPHandler.handleCDUMP(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case LISTO_OP_CODE: // 6
			// cout << "\t[Executor]: Found LISTO Command\n";
			// mainLISTOHandler.handleLISTO(&currentLineObject, *currentProgramCounter); // NOT USING COMMAND HANDLER
			globalProgramManager.printProgramLineTable();
			(*currentProgramCounter)++;
			break;
		case NOP_OP_CODE: // 7
			// cout << "\t[Executor]: Found NOP Command\n";
			// mainNOPHandler.handleNOP(&currentLineObject, *currentProgramCounter); // NOT USING COMMAND HANDLER
			(*currentProgramCounter)++;
			break;
	// 	case GOTO_OP_CODE: // 8
	// 		// cout << "\t[Executor]: Found GOTO Command\n";
	// 		mainAREADHandler.handleAREAD(&currentLineObject, *currentProgramCounter);
	// 		break;
		case 9: // 9
			cout << "\t[Executor]: Error: Found Invalid Op Code 9\n";
			globalNumErrors++;
			(*currentProgramCounter)++;
			break;
	// 	case IFA_OP_CODE: // 10
	// 		// cout << "\t[Executor]: Found IFA Command\n";
	// 		mainIFAHandler.handleIFA(&currentLineObject, *currentProgramCounter);
	// 		break;
		case AREAD_OP_CODE: // 11
			// cout << "\t[Executor]: Found aREAD Command\n";
			mainAREADHandler.handleAREAD(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case AWRITE_OP_CODE: // 12
			// cout << "\t[Executor]: Found aWRITE Command\n";
			mainAWRITEHandler.handleAWRITE(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case SUBP_OP_CODE: // 13
			// cout << "\t[Executor]: Found SUBP Command\n";
			mainSUBPHandler.handleSUBP(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case LOOP_OP_CODE: // 14
			// cout << "\t[Executor]: Found LOOP Command\n";
			globalLoopManager.handleLOOP(&currentLineObject, currentProgramCounter);
			break;
		case LOOPEND_OP_CODE: // 15
			// cout << "\t[Executor]: Found LOOP-END Command\n";
			globalLoopManager.handleLOOPEND(currentProgramCounter);
			break;
		case LREAD_OP_CODE: // 16
			// cout << "\t[Executor]: Found LREAD Command\n";
			mainLREADHandler.handleLREAD(&currentLineObject);
			(*currentProgramCounter)++;
			break;
		case LWRITE_OP_CODE: // 17
			// cout << "\t[Executor]: Found LWRITE Command\n";
			mainLWRITEHandler.handleLWRITE(&currentLineObject);
			(*currentProgramCounter)++;
			break;
	// 	case IF_OP_CODE: // 18
	// 		// cout << "\t[Executor]: Found IF Command\n";
	// 		mainIFHandler.handleIF(&currentLineObject, *currentProgramCounter);
	// 		break;
		case CLS_OP_CODE: // 19
			// cout << "\t[Executor]: Found CLS Command\n";
			// mainCLSHandler.handleCLS(&currentLineObject, *currentProgramCounter);
			cout << string(100, '\n');
			(*currentProgramCounter)++;
			break;
	// 	case ASSIGNMENT_OP_CODE: // 20
	// 		// cout << "\t[Executor]: Found ASSIGNMENT Command\n";
	// 		mainASSIGNMENTHandler.handleASSIGNMENT(&currentLineObject, *currentProgramCounter);
	// 		break;
		default:
			cout << "\t[Executor]: Error: Invalid Op Code \"" << currentOpCode << "\"\n";
			globalNumErrors++;
			(*currentProgramCounter)++;
			break;
	}
}

// instantiates objects for handling commands by passing the FileManager, MemoryManager, SymbolTable, LineLabelTable, and/or LiteralTable by reference
void BREN_Executor::instantiateCommandObjects(){
	mainREADHandler.prepareREAD(&globalMemoryManager);
	mainWRITEHandler.prepareWRITE(&globalMemoryManager);

	mainDIMHandler.prepareDIM(&globalMemoryManager);
	mainAREADHandler.prepareAREAD(&globalMemoryManager);
	mainAWRITEHandler.prepareAWRITE(&globalMemoryManager);
	mainLREADHandler.prepareLREAD(&globalLiteralManager);
	mainLWRITEHandler.prepareLWRITE(&globalLiteralManager);
	mainCDUMPHandler.prepareCDUMP(&globalMemoryManager);
	mainSUBPHandler.prepareSUBP(&globalMemoryManager);

	globalLoopManager.prepareLoopManager(&globalMemoryManager, &globalProgramManager);
	// mainGOTOHandler.prepareGOTO(&globalFileManager, &globalLineManager);
	// mainIFAHandler.prepareIFA(&globalFileManager, &globalMemoryManager, &globalLineManager);
	// mainIFHandler.prepareIF(&globalFileManager, &globalMemoryManager, &globalLineManager);

	// mainASSIGNMENTHandler.prepareASSIGNMENT(&globalFileManager, &globalMemoryManager);
}
