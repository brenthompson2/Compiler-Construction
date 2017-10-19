/*
  ==============================================================================

	File: CompilerDriver.cpp
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Driver for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class


  ==============================================================================
*/

/* ==============================================================================
	File Includes
============================================================================== */
#include "Compiler.h"
#include <iostream>	// Console IO

/* ==============================================================================
	Symbolic Constants
============================================================================== */
#define MAX_NUM_FLAGS 7

/* ==============================================================================
	Main Driver
============================================================================== */
int main (int argc, char**argv){
	// int numFlags;
	// string arrayOfFlags[MAX_NUM_FILES];

	string fileName = argv[1];

	// cout << "\nGetting Flags...\n";
	// for (int i = 0; i < numArguments; i++){
	// 	cout << "\t" << i << ": " << argv[i + 1];
	// 	arrayOfFlags[i] = argv[i + 1];
	// }
	// cout << endl;

	cout << "\nPreparing for Compilation...\n";
	BREN_Compiler mainCompiler;
	mainCompiler.prepareForCompilation(fileName);

	cout << "\n\nCompiling...\n";
	mainCompiler.compile();

	cout << "Finished Compilation\n";
	return 0;
}
