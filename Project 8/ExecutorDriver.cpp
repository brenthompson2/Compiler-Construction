/*
  ==============================================================================

	File: ExecutorDriver.cpp
	Author: Brendan Thompson
	Updated: 11/16/17

	Description: Driver for Main Executor Object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- creates an instance of Executor, tells it to prepare for execution, tells it to execute, and shutdowns the Executor
		- takes in flags and a fileName as a parameter

  ==============================================================================
*/

/* ==============================================================================
	File Includes
============================================================================== */
#include "Executor.h"
#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()

/* ==============================================================================
	Symbolic Constants
============================================================================== */
#define MAX_NUM_FLAGS 7


/* ==============================================================================
	Function Declarations
============================================================================== */

// takes in the command line arguments passed to the Executor and parses them into flags and the fileName
bool parseArguments(int numArguments, char* *arrayOfArgs, char *arrayOfFlags, string *fileName, int *numFlags);

/* ==============================================================================
	Main Executor Driver
============================================================================== */

int main (int argc, char**argv){
	int numFlags = 0;

	string fileName;
	char arrayOfFlags[MAX_NUM_FLAGS];
	bool gotFilename = false;
	bool continueWithExecution = true;

	cout << "\n[Executor Driver]: Preparing for Execution...\n";
	continueWithExecution = parseArguments(argc, argv, arrayOfFlags, &fileName, &numFlags);
	if (!continueWithExecution){
		cout << "[Executor Driver]: Error Parsing Command Line Arguments, aborting...\n";
		exit(1);
	}

	BREN_Executor mainExecutor;
	continueWithExecution = mainExecutor.prepareForExecution(fileName, arrayOfFlags, numFlags);
	if (!continueWithExecution){
		cout << "[Executor Driver]: Error Preparing for Execution, aborting...\n";
		exit(1);
	}

	cout << "\n\n[Executor Driver]: Executing...\n";
	mainExecutor.execute();

	cout << "\n\n[Executor Driver]: Finished Execution\n";
	return 0;
}

/* ==============================================================================
	Helper Functions
============================================================================== */

// takes in the command line arguments passed to the Executor and parses them into flags and the fileName
bool parseArguments(int numArguments, char* *arrayOfArgs, char *arrayOfFlags, string *fileName, int *numFlags){

	string currentArg;
	bool gotFilename = false;

	// If No File Specified
	if (numArguments == 1){
		(*fileName) = "test1.transy";
		return true;
	}

	// Get Flags
	// cout << "\n[Executor Driver]: Getting Flags...\n";
	for (int i = 1; i < numArguments; i++){
		currentArg = (arrayOfArgs[i]);
		// cout << "[Executor Driver]: Parsing Arg " << i << ": " << currentArg << endl;

		// Got Flag
		if (currentArg[0] == '-'){
			int flagIterator = 1;

			// Parse Nested Flags
			while (currentArg[flagIterator] != '\0'){
				arrayOfFlags[(*numFlags)] = currentArg[flagIterator];
				// cout << "[Executor Driver]: Got Flag: " << i << ": " << arrayOfFlags[(*numFlags)] << endl;
				(*numFlags)++;
				flagIterator++;
			}
		}
		else {
			if (i != numArguments -1){
				cout << "[Executor Driver]: Error: Expected Flag\n";
				return false;
			}
			else {
				(*fileName) = (arrayOfArgs[i]);
				gotFilename = true;
			}

		}
	}

	if (!gotFilename){
		(*fileName) = "test1.obj";
	}

	// cout << "[Executor Driver]: Got Filename: " << (*fileName) << endl;

	return true;

}
