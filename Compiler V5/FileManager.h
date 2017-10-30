/*
  ==============================================================================

	File: FileManger.h
	Author: Brendan Thompson
	Updated: 10/13/17

	Description: Interface for main FileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

// ==============================================================================
// Reads in a user specified file and outputs it as trimmedOutput.txt after removing all white spaces and blank lines

#pragma once

#include "LiteralTable.h"
#include "LineLabelTable.h"

#include <iostream>	// Console IO
#include <fstream>	// File IO
#include <stdio.h>	// remove()
#include <stdlib.h>	// Exit()
#include <string.h> // strcpy & strcat
#include <string> // getline() substr()
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
#define FILE_END_SENTINEL "@"
#define NO_LINE_LABEL -1

class FileManager {
public:
	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */

	FileManager(); // Instantiates a FileManager object
	~FileManager(); // Shuts down the FileManager by  calling removeFiles()

	/* ==============================================================================
		Public Pre-Compiling Methods
	============================================================================== */

	// Sets the FileManagers's Global FileNames & Links to the Parent's LineManager & LiteralManager
	bool prepareForCompilation(string fileToCompile, LiteralTable *literalManager, LineLabelTable *lineManager);

	// Creates the preprocessed .noblanks file & upon completion returns status of success
	bool preprocessFile();

	/* ==============================================================================
		Public File IO Methods
	============================================================================== */

	// Returns the next line from the preprocessed file (.noblanks), else returns "@"
	string getNextLine();

	// Writes the char "value" to the .obj output file
	void writeCharToObj (char value);

	// Writes the int "value" to the .obj output file
	void writeNumToObj (int value);

	// Writes the string "currentString" to the .obj output file
	void writeStringToObj (string currentString);

	/* ==============================================================================
		Public Flag Methods
	============================================================================== */

	// parses the flags and manages the global flag bools
	void setFlags(char *arrayOfFlags, int numberOfFlags);

	// sets the keepObjFlag to true
	void setKeepOBJ();

private:
	/* ==============================================================================
		Private Members
	============================================================================== */

	// Files & File Names
	ifstream globalInputFile; // <fileName>.transy
	ifstream preprocessedInFile; // <fileName>.noblanks
	ofstream noBlanksOutFile; // <fileName>.noblanks
	ofstream objOutFile; // <fileName>.obj
	char globalFileStem[MAX_STRING_LENGTH]; // stem of filename
	char globalPreprocessedFileName[MAX_STRING_LENGTH]; // stem of filename
	char globalObjFileName[MAX_STRING_LENGTH]; // stem of filename

	// Flags
	bool keepNoBlanksFlag; // -n = keep even if compiles successfully
	bool keepObjFlag; // -o = keep even if compilation fails

	// Parent's Objects
	LiteralTable *ParentLiteralManager;
	LineLabelTable *ParentLineManager;

	/* ==============================================================================
		Private File Management Functions
	============================================================================== */

	// Sets the global file names
	void createFileNames(string originalFileName);

	// opens .transy input file and noblanks output file
	bool openFirstFiles(string inputFileName);

	// opens .noblanks input file & .obj output file
	bool openCompilationFiles();

	// conditionally removes .noblanks & .obj
	void removeFiles();

	/* ==============================================================================
		Private Line Label Reading Functions (First Pass)
	============================================================================== */

	// Parses the file and syncs line labels with the ParentLineManager
	void gatherLineLabels();

	// Parses the line looking for a : to signify a line label
	int checkForLineLabel(string currentLine);

	/* ==============================================================================
		Private No-Blanks Writing Functions (Second Pass)
	============================================================================== */

	// Writes <fileName>.noBlanks by removing whitespace and unifying everything to upper case
	bool writeNoBlanksFile();

	// iterates through the line, changes *currentLine to a proper version, and returns whether or not it is a valid line to add to the .noblanks file
	bool checkCurrentLine(string *currentLine);
};


