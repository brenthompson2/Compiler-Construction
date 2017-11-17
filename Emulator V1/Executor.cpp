/* ==============================================================================

	File: Executor.cpp
	Author: Brendan Thompson
	Updated: 11/16/17

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
	// globalProgramManager.printProgramLineTable();
	// globalMemoryManager.printCoreMemory();
	// globalLiteralManager.printLiteralTable();

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
		if ((*currentProgramLine).numElementsInLine != NOT_VALID_PROGRAM){
			handleCommand((*currentProgramLine), &programCounter);
			linesRunCount++;
		}
		else {
			continueCompiling = false;
		}
	}

	// Manage Compilation Result
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
	// 	case DIM_OP_CODE: // 0
	// 		// cout << "\t[Executor]: Found DIM Command\n";
	// 		mainDIMHandler.handleDIM(currentLine, *currentProgramCounter);
	// 		break;
		case READ_OP_CODE: // 1
			cout << "\t[Executor]: Found READ Command\n";
			mainREADHandler.handleREAD(&currentLineObject, (*currentProgramCounter));
			(*currentProgramCounter)++;
			break;
	// 	case WRITE_OP_CODE: // 2
	// 		// cout << "\t[Executor]: Found WRITE Command\n";
	// 		mainWRITEHandler.handleWRITE(currentLine, *currentProgramCounter);
	// 		break;
	// 	case STOP_OP_CODE: // 3
	// 		// cout << "\t[Executor]: Found STOP command\n";
	// 		mainSTOPHandler.handleSTOP(currentLine, *currentProgramCounter);
	// 		break;
	// 	case 4: // 4
	// 		cout << "\t[Executor]: Error: Found Invalid Op Code 4\n";
	// 		globalglobalNumErrors++;
	// 		break;
	// 	case CDUMP_OP_CODE: // 5
	// 		// cout << "\t[Executor]: Found CDUMP Command\n";
	// 		mainCDUMPHandler.handleCDUMP(currentLine, *currentProgramCounter);
	// 		break;
	// 	case LISTO_OP_CODE: // 6
	// 		// cout << "\t[Executor]: Found LISTO Command\n";
	// 		mainLISTOHandler.handleLISTO(currentLine, *currentProgramCounter);
	// 		break;
	// 	case NOP_OP_CODE: // 7
	// 		// cout << "\t[Executor]: Found NOP Command\n";
	// 		mainNOPHandler.handleNOP(currentLine, *currentProgramCounter);
	// 		break;
	// 	case GOTO_OP_CODE: // 8
	// 		// cout << "\t[Executor]: Found GOTO Command\n";
	// 		mainAREADHandler.handleAREAD(currentLine, *currentProgramCounter);
	// 		break;
	// 	case 9: // 9
	// 		cout << "\t[Executor]: Error: Found Invalid Op Code 9\n";
	// 		globalglobalNumErrors++;
	// 		break;
	// 	case IFA_OP_CODE: // 10
	// 		// cout << "\t[Executor]: Found IFA Command\n";
	// 		mainIFAHandler.handleIFA(currentLine, *currentProgramCounter);
	// 		break;
	// 	case AREAD_OP_CODE: // 11
	// 		// cout << "\t[Executor]: Found aREAD Command\n";
	// 		mainAREADHandler.handleAREAD(currentLine, *currentProgramCounter);
	// 		break;
	// 	case AWRITE_OP_CODE: // 12
	// 		// cout << "\t[Executor]: Found aWRITE Command\n";
	// 		mainAWRITEHandler.handleAWRITE(currentLine, *currentProgramCounter);
	// 		break;
	// 	case SUBP_OP_CODE: // 13
	// 		// cout << "\t[Executor]: Found SUBP Command\n";
	// 		mainSUBPHandler.handleSUBP(currentLine, *currentProgramCounter);
	// 		break;
	// 	case LOOP_OP_CODE: // 14
	// 		// cout << "\t[Executor]: Found LOOP Command\n";
	// 		mainLOOPHandler.handleLOOP(currentLine, *currentProgramCounter);
	// 		break;
	// 	case LOOPEND_OP_CODE: // 15
	// 		// cout << "\t[Executor]: Found LOOP-END Command\n";
	// 		mainLOOPENDHandler.handleLOOPEND(currentLine, *currentProgramCounter);
	// 		break;
		case LREAD_OP_CODE: // 16
			cout << "\t[Executor]: Found LREAD Command\n";
			// mainLREADHandler.handleLREAD(currentLineObject, *currentProgramCounter);
			(*currentProgramCounter)++;
			break;
	// 	case LWRITE_OP_CODE: // 17
	// 		// cout << "\t[Executor]: Found LWRITE Command\n";
	// 		mainLWRITEHandler.handleLWRITE(currentLine, *currentProgramCounter);
	// 		break;
	// 	case IF_OP_CODE: // 18
	// 		// cout << "\t[Executor]: Found IF Command\n";
	// 		mainIFHandler.handleIF(currentLine, *currentProgramCounter);
	// 		break;
	// 	case CLS_OP_CODE: // 19
	// 		// cout << "\t[Executor]: Found CLS Command\n";
	// 		mainCLSHandler.handleCLS(currentLine, *currentProgramCounter);
	// 		break;
	// 	case ASSIGNMENT_OP_CODE: // 20
	// 		// cout << "\t[Executor]: Found ASSIGNMENT Command\n";
	// 		mainASSIGNMENTHandler.handleASSIGNMENT(currentLine, *currentProgramCounter);
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
	// mainWRITEHandler.prepareWRITE(&globalFileManager, &globalMemoryManager);
	// mainSTOPHandler.prepareSTOP(&globalFileManager);

	// mainDIMHandler.prepareDIM(&globalFileManager, &globalMemoryManager);
	// mainAREADHandler.prepareAREAD(&globalFileManager, &globalMemoryManager);
	// mainAWRITEHandler.prepareAWRITE(&globalFileManager, &globalMemoryManager);

	// mainGOTOHandler.prepareGOTO(&globalFileManager, &globalLineManager);
	// mainLOOPHandler.prepareLOOP(&globalFileManager, &globalMemoryManager);
	// mainLOOPENDHandler.prepareLOOPEND(&globalFileManager);
	// mainIFAHandler.prepareIFA(&globalFileManager, &globalMemoryManager, &globalLineManager);
	// mainNOPHandler.prepareNOP(&globalFileManager);
	// mainLISTOHandler.prepareLISTO(&globalFileManager);

	// mainLREADHandler.prepareLREAD(&globalFileManager, &globalLiteralManager);
	// mainLWRITEHandler.prepareLWRITE(&globalFileManager, &globalLiteralManager);
	// mainIFHandler.prepareIF(&globalFileManager, &globalMemoryManager, &globalLineManager);
	// mainCLSHandler.prepareCLS(&globalFileManager);
	// mainCDUMPHandler.prepareCDUMP(&globalFileManager, &globalMemoryManager);
	// mainSUBPHandler.prepareSUBP(&globalFileManager, &globalMemoryManager);

	// mainASSIGNMENTHandler.prepareASSIGNMENT(&globalFileManager, &globalMemoryManager);
}
