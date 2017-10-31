/*
  ==============================================================================

	File: CompilerDriver.cpp
	Author: Brendan Thompson
	Updated: 10/12/17

	Description: Driver for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- creates an instance of Compiler, tells it to prepare for compilation, tells it to compile, and shutdowns the compiler
		- takes in flags and a fileName as a parameter

  ==============================================================================
*/

/* ==============================================================================
	File Includes
============================================================================== */
#include "Compiler.h"
#include <iostream>	// Console IO
#include <stdlib.h>	// Exit()

/* ==============================================================================
	Symbolic Constants
============================================================================== */
#define MAX_NUM_FLAGS 7


/* ==============================================================================
	Function Declarations
============================================================================== */

// takes in the command line arguments passed to the compiler and parses them into flags and the fileName
bool parseArguments(int numArguments, char* *arrayOfArgs, char *arrayOfFlags, string *fileName, int *numFlags);

/* ==============================================================================
	Main Driver
============================================================================== */

int main (int argc, char**argv){
	int numFlags = 0;

	string fileName;
	char arrayOfFlags[MAX_NUM_FLAGS];
	bool gotFilename = false;
	bool continueWithCompilation = true;

	cout << "\n[Driver]: Preparing for Compilation...\n";
	continueWithCompilation = parseArguments(argc, argv, arrayOfFlags, &fileName, &numFlags);
	if (!continueWithCompilation){
		cout << "[Driver]: Error Parsing Command Line Arguments, aborting...\n";
		exit(1);
	}

	BREN_Compiler mainCompiler;
	continueWithCompilation = mainCompiler.prepareForCompilation(fileName, arrayOfFlags, numFlags);
	if (!continueWithCompilation){
		cout << "[Driver]: Error Preparing for Compilation, aborting...\n";
		exit(1);
	}

	cout << "\n\n[Driver]: Compiling...\n";
	mainCompiler.compile();

	cout << "\n\n[Driver]: Finished Compilation\n";

	return 0;
}

/* ==============================================================================
	Helper Functions
============================================================================== */

// takes in the command line arguments passed to the compiler and parses them into flags and the fileName
bool parseArguments(int numArguments, char* *arrayOfArgs, char *arrayOfFlags, string *fileName, int *numFlags){

	string currentArg;
	bool gotFilename = false;

	// If No File Specified
	if (numArguments == 1){
		(*fileName) = "test1.transy";
		return true;
	}

	// Get Flags
	// cout << "\n[Driver]: Getting Flags...\n";
	for (int i = 1; i < numArguments; i++){
		currentArg = (arrayOfArgs[i]);
		// cout << "[Driver]: Parsing Arg " << i << ": " << currentArg << endl;

		// Got Flag
		if (currentArg[0] == '-'){
			int flagIterator = 1;

			// Parse Nested Flags
			while (currentArg[flagIterator] != '\0'){
				arrayOfFlags[(*numFlags)] = currentArg[flagIterator];
				// cout << "[Driver]: Got Flag: " << i << ": " << arrayOfFlags[(*numFlags)] << endl;
				(*numFlags)++;
				flagIterator++;
			}
		}
		else {
			if (i != numArguments -1){
				cout << "[Driver]: Error: Expected Flag\n";
				return false;
			}
			else {
				(*fileName) = (arrayOfArgs[i]);
				gotFilename = true;
			}

		}
	}

	if (!gotFilename){
		(*fileName) = "test1.transy";
	}

	cout << "[Driver]: Got Filename: " << (*fileName) << endl;

	return true;

}
