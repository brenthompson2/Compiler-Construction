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
#define MAX_NUM_FILES 7

/* ==============================================================================
	Main Driver
============================================================================== */
int main (int argc, char**argv){
	int numFiles = argc - 1;
	string fileNameArray[MAX_NUM_FILES];

	cout << "\nFiles to Compile:\n";
	for (int i = 0; i < numFiles; i++){
		cout << "\t" << i << ": " << argv[i + 1];
		fileNameArray[i] = argv[i + 1];
	}
	cout << endl;

	cout << "\nPreparing for Compilation...\n";
	BREN_Compiler mainCompiler;
	mainCompiler.prepareForCompilation(numFiles, fileNameArray);

	cout << "\n\nCompiling...\n";
	mainCompiler.compile();

	// cout << "\n\nShutting Down Compiler...\n";
	cout << "Finished Compilation\n";
	return 0;
}