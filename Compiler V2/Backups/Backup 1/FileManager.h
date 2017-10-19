/*
  ==============================================================================

	File: FileManger.h
	Author: Brendan Thompson
	Updated: 10/01/17

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
#define FILE_END_SENTINEL "@"

class FileManager {
public:
	/* ==============================================================================
		Constructor & Destructor
	============================================================================== */

	FileManager(); // Instantiates a FileManager object which opens .transy input file & both .noblanks and .obj output files
	~FileManager(); // Shuts down the FileManager by closing preprocessed input file & .obj output file

	/* ==============================================================================
		Public Methods
	============================================================================== */

	// prepares for compilation by preprocessing the .transy file into .noblanks by removing blank lines, spaces, and unifying all characters to uppercase and then re-opening the preprocessed file
	bool prepareForCompilation(string fileName);

	// Returns the next line from the preprocessed file (.noblanks), else returns "@"
	string getNextLine();

	// Writes the char "value" to the .obj output file
	void writeCharToObj (char value);

	// Writes the int "value" to the .obj output file
	void writeNumToObj (int value);

	// Writes the string "currentString" to the .obj output file
	void writeStringToObj (string currentString);

private:
	/* ==============================================================================
		Private Members
	============================================================================== */
	ifstream preprocessedFile; // <fileName>.noblanks
	ofstream objFile; // <fileName>.obj
	char globalFileName[MAX_STRING_LENGTH]; // stem of filename

	/* ==============================================================================
		Private File IO Methods
	============================================================================== */

	// opens .transy input file and also .noblanks and .obj output files
	bool prepareFileIO(string inputFile, ifstream &transyInFile, ofstream &noBlanksOutFile, char preprocessedFileName[]);

	// reopens preprocessedFile <fileName>.noblanks to be used as input
	bool openPreprocessedFile(char preprocessedFileName[]);

	// Trims the originalFileName & defines globalFileName (stem), noBlanksFileName & preproccessedFileName (stem.noblanks), objFileName (stem.obj)
	void createFileNames(string originalFileName, char transyInfileName[], char noBlankOutfileName[], char objOutfileName[], char preprocessedFileName[]);

	// Writes <fileName>.noBlanks by removing whitespace and unifying everything to upper case
	bool writeNoBlanksFile(ifstream &inputFile, ofstream &noBlanksOutFile);
};


