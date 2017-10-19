/*
  ==============================================================================

	File: CompilerDriver.cpp
	Author: Brendan Thompson
	Updated: 09/24/17

	Description: Driver for Main compiler Object made for Transylvania University University Fall Term 2017 Compiler Construction class


  ==============================================================================
*/

/* ==============================================================================
	File Includes
============================================================================== */
#include "Compiler.h"
#include <iostream>	// Console IO


/* ==============================================================================
	Main Driver
============================================================================== */
int main (){
	cout << "Preparing for Compilation...\n";
	BREN_Compiler mainCompiler;

	cout << "\n\nCompiling...\n";
	mainCompiler.compile();

	cout << "\n\nShutting Down Compiler...\n";
	mainCompiler.shutdown();
	cout << "Finished Compilation\n";
	return 0;
}