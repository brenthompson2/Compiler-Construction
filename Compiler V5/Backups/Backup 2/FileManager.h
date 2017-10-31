/* ==============================================================================

	File: FileManger.h
	Author: Brendan Thompson
	Updated: 10/30/17

	Description: Interface for main FileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- opens .transy, .obj, .noblanks, .literal, and .core files
		- syncs lineLabels with LineLabelTable
		- preprocesses .transy into .noblanks
		- upon request hands the compiler one line at a time from the preprocessed file
		- writes char/string/int to .obj file
		- writes one literal at a time to .literal
		- writes one ID at a time to .core
		- compiler command flags determine what files are kept (-n -o -l -c)

============================================================================== */

#pragma once

/* ==============================================================================
	File Includes
============================================================================== */

#include "LineLabelTable.h"

#include <iostream>	// Console IO
#include <iomanip> // std::setprecision()
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

/* ==============================================================================
	Symbolic Constants
============================================================================== */

#define MAX_STRING_LENGTH 50
#define MAX_LINE_LENGTH 50
#define FILE_END_SENTINEL "@"
#define NO_LINE_LABEL -1

// File Prefixes
// const char transyFileType[8] = ".transy";
const char noBlankFileType[10] = ".noblanks";
const char objOutFileType[5] = ".obj";
const char literalOutFileType[9] = ".literal";
const char coreOutFileType[6] = ".core";

/* ==============================================================================
	File Manager Class Interface
============================================================================== */

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

	// Sets the FileManagers's Global FileNames & Links to the Parent's LineManager
	bool prepareForCompilation(string fileToCompile, LineLabelTable *lineManager);

	// Creates the preprocessed .noblanks file & upon completion returns status of success
	bool preprocessFile();

	/* ==============================================================================
		Public File IO Methods
	============================================================================== */

	// Returns the next line from the preprocessed file (.noblanks), else returns "@"
	string getNextLine();

	// Writes the char "value" to the .obj output file
	// void writeCharToObj (char value);

	// Writes the int "value" to the .obj output file
	void writeNumToObj (float value);

	// Writes the string "currentString" to the .obj output file
	void writeStringToObj (string currentString);

	// Writes the string "currentString" to the .literal output file
	void writeStringToLiteral (string currentString);

	// Writes the float "value" to the .literal output file
	void writeNumToLiteral (float value);

	// Writes the string "currentString" to the .core output file
	void writeStringToCore (string currentString);

	// Writes the float "value" to the .core output file
	void writeNumToCore (float value);

	/* ==============================================================================
		Public Flag Methods
	============================================================================== */

	// parses the flags and manages the global flag bools
	void setFlags(char *arrayOfFlags, int numberOfFlags);

	// sets the keepObjFlag to true
	void setCompilationResult(bool completedSuccessfully);

private:
	/* ==============================================================================
		Private Members
	============================================================================== */

	// Files & File Names
	ifstream globalInputFile; // <fileName>.transy
	ifstream preprocessedInFile; // <fileName>.noblanks
	ofstream noBlanksOutFile; // <fileName>.noblanks
	ofstream objOutFile; // <fileName>.obj
	ofstream literalOutFile; // <fileName>.literal
	ofstream coreOutFile; // <fileName>.core
	char globalFileStem[MAX_STRING_LENGTH]; // stem of filename
	char globalPreprocessedFileName[MAX_STRING_LENGTH]; // globalFileStem += .noblanks
	char globalObjFileName[MAX_STRING_LENGTH]; // globalFileStem += .obj
	char globalLiteralFileName[MAX_STRING_LENGTH]; // globalFileStem += .literal
	char globalCoreFileName[MAX_STRING_LENGTH]; // globalFileStem += .core

	// Flags
	bool keepNoBlanksFlag; // -n = keep even if compiles successfully
	bool keepObjFlag; // -o = keep even if compilation fails
	bool keepLiteralFlag;
	bool keepCoreFlag;

	// Parent's Objects
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


