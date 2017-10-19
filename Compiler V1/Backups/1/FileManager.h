/*
  ==============================================================================

	File: FileManger.h
	Author: Brendan Thompson
	Updated: 09/24/17

	Description: Interface for main FileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

// ==============================================================================
// Reads in a user specified file and outputs it as trimmedOutput.txt after removing all white spaces and blank lines

#pragma once

#include <iostream>	// Console IO
#include <fstream>	// File IO
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat
#include <string> // getline()
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::fstream;
using std::ofstream;
using std::string;
using std::getline;

#define MAX_STRING_LENGTH 50
#define MAX_LINE_LENGTH 50

class FileManager {
public:
	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */

	FileManager(); // Instantiates a FileManager object which opens Input and Output files
	void shutdown(); // Shuts down the FileManager by closing input & output files

	/* ==============================================================================
		Public Methods
	============================================================================== */
	bool prepareForCompilation(); // preprocesses the .transy file into .noblanks by removing blank lines, spaces, and unifying all characters to uppercase
	string getNextLine(); // returns the next line from the preprocessed file (.noblanks)
	void writeCharToObj (char value); // Writes the char "value" to the .obj output file
	void writeNumToObj (int value); // Writes the int "value" to the .obj output file

private:
	/* ==============================================================================
		Private Members
	============================================================================== */
	ifstream globalInputFile;
	ifstream preprocessedFile;
	ofstream noBlanksFile;
	ofstream objFile;
	char globalFileName[MAX_STRING_LENGTH];
	char preprocessedFileName[MAX_STRING_LENGTH];

	/* ==============================================================================
		Private File IO Methods
	============================================================================== */

	bool prepareFileIO(); 	// Opens Input & Output Files
	void createFileNames(char* originalFileName, char* noBlankFileName, char* objFileName);	// Trims the originalFileName & defines globalFileName, noBlanksFileName, and objFileName
	void writeCharToNoBlanks (char value); // Writes the char "value" to the .noblanks output file

};


