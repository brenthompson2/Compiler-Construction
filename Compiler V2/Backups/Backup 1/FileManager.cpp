/*
  ==============================================================================

	File: FileManger.cpp
	Author: Brendan Thompson
	Updated: 10/01/17

	Description: Implementation of main FileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "FileManager.h"

/* ==============================================================================
Constructor & Destructor
============================================================================== */

// Instantiates a FileManager object which opens .transy input file and both .noblanks and .obj output files
FileManager::FileManager(){
	return ;
}

// Shuts down the FileManager by closing preprocessed input file & .obj output file
FileManager::~FileManager(){
	preprocessedFile.close();
	objFile.close();
	cout << "\t\t[FILE MANAGER]: Shutdown FileManager\n";
}

/* ==============================================================================
	Public Functions
============================================================================== */

// prepares for compilation by preprocessing the .transy file into .noblanks by removing blank lines, spaces, and unifying all characters to uppercase and then re-opening the preprocessed file
bool FileManager::prepareForCompilation(string fileName){
	ofstream noBlanksOutputFile; // <fileName>.noblanks
	ifstream transyInputFile; // <fileName>.transy
	char preprocessedFileName[MAX_STRING_LENGTH];

	if (!prepareFileIO(fileName, transyInputFile, noBlanksOutputFile, preprocessedFileName)){
		cerr << "\t\t[FILE MANAGER]: ERROR: failed to open file " << fileName << ". Aborting...\n";
		exit(1);
	}

	writeNoBlanksFile(transyInputFile, noBlanksOutputFile);

	transyInputFile.close();
	noBlanksOutputFile.close();



	if (!openPreprocessedFile(preprocessedFileName)){
		cerr << "\t\t[FILE MANAGER]: ERROR: failed to open input file" << preprocessedFileName << ". Aborting...\n";
		exit(1);
	}

	cout << "\t\t[FILE MANAGER]: Successfully preprocessed " << fileName << " into " << preprocessedFileName << endl;
	return true;
}

// Returns the next line from the preprocessed file (.noblanks), else returns "@"
string FileManager::getNextLine(){
	string currentLine;
	if (!(preprocessedFile.eof())){
		getline(preprocessedFile, currentLine);
		// cout << "\t\t[FILE MANAGER]: Got Line: " << currentLine << endl;
	}
	else {
		currentLine = FILE_END_SENTINEL;
		// cout << "\t\t[FILE MANAGER]: Found End Of File: " << currentLine << endl;
	}
	return currentLine;
}

// Writes the char "value" to the .obj output file
void FileManager::writeCharToObj (char value){
	objFile << value;
	// cout << "\t\t[FILE MANAGER]: Wrote " << value << " to .obj\n";
	return;
}

// Writes the int "value" to the .obj output file
void FileManager::writeNumToObj (int value){
	objFile << value;
	// cout << "\t\t[FILE MANAGER]: Wrote " << value << " to .obj\n";
	return;
}

// Writes the string "currentString" to the .obj output file
void FileManager::writeStringToObj (string currentString){
	int i = 0;
	while (currentString[i] != '\0'){
		objFile << currentString[i];
		// cout << "\t\t[FILE MANAGER]: Wrote " << currentString[i] << " to .obj\n";
		i++;
	}
	return;
}

/* ==============================================================================
	Private File IO Functions
============================================================================== */

// opens .transy input file and also .noblanks and .obj output files
bool FileManager::prepareFileIO(string inputFile, ifstream &transyInFile, ofstream &noBlanksOutFile, char preprocessedFileName[]){
	char transyFileName[MAX_STRING_LENGTH];
	char noBlankFileName[MAX_STRING_LENGTH];
	char objFileName[MAX_STRING_LENGTH];

    createFileNames(inputFile, transyFileName, noBlankFileName, objFileName, preprocessedFileName);

	//attempt to open input file
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << transyFileName << " for input..." << endl;
    transyInFile.open(transyFileName);
    if (!transyInFile) {
        cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open " << transyFileName << " for input" << endl;
        return false;
    }

	//attempt to open output files
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << noBlankFileName << " for output..." << endl;
	noBlanksOutFile.open(noBlankFileName);
	if (!noBlanksOutFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .noblanks output file" <<endl;
        return false;
	}
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << objFileName << " for output..." << endl;
	objFile.open(objFileName);
	if (!objFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .obj output file" <<endl;
        return false;
	}

	return true;
}

bool FileManager::openPreprocessedFile(char preprocessedFileName[]){
  // cout << "\t\t[FILE MANAGER]: Attempting to open " << preprocessedFileName << " for input..." << endl;
	preprocessedFile.open(preprocessedFileName);
	if (!preprocessedFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open preprocessed input file" <<endl;
        return false;
	}
	return true;
}

// Trims the originalFileName & defines globalFileName (stem), noBlanksFileName & preproccessedFileName (stem.noblanks), objFileName (stem.obj)
void FileManager::createFileNames(string originalFileName, char transyInfileName[], char noBlankOutfileName[], char objOutfileName[], char preprocessedFileName[]){
	const char transyFileType[8] = ".transy";
	const char noBlankFileType[10] = ".noblanks";
	const char objFileType[5] = ".obj";

	strcpy(transyInfileName, "");
	strcpy(noBlankOutfileName, "");
	strcpy(objOutfileName, "");
	strcpy(preprocessedFileName, "");

	// cout << "\nTransy File\t\tNo Blank File\t\tPreprocessedFile\t\tobjFile\n";
	// cout << transyInfileName << "\t" << noBlankOutfileName << "\t" << preprocessedFileName << "\t" << objOutfileName << endl;
	// cout << endl;


	bool notFinished = true;
	int i = 0;
	char currentCharacter;

	//get globalFileName, create .noblanks, and create .obj
    // cout << "Attempting to find stem of " << originalFileName << endl;
    while (notFinished){
    	currentCharacter = originalFileName[i];
    	// cout << "CurrentChar: " << currentCharacter << endl;
    	if (currentCharacter == '.'){
    		globalFileName[i] = '\0';
    		transyInfileName[i] = '\0';
    		noBlankOutfileName[i] = '\0';
    		objOutfileName[i] = '\0';
    		notFinished = false;
    	}
    	else {
    		globalFileName[i] = currentCharacter;
    		transyInfileName[i] = currentCharacter;
	    	noBlankOutfileName[i] = currentCharacter;
	    	objOutfileName[i] = currentCharacter;
    	}

    	i++;
    }
    // cout << "The stem of " << originalFileName << " is " << globalFileName << "<--" << endl;

    strcat(transyInfileName, transyFileType);
    strcat(noBlankOutfileName, noBlankFileType);
	strcat(objOutfileName, objFileType);
    strcpy(preprocessedFileName, noBlankOutfileName);

 	// cout << "\nTransy File\tNo Blank File\tPreprocessedFile\tobjFile\n";
	// cout << transyInfileName << "\t" << noBlankOutfileName << "\t" << preprocessedFileName << "\t" << objOutfileName << endl;
	// cout << endl;
	return;
}

// Writes <fileName>.noBlanks by removing whitespace and unifying everything to upper case
bool FileManager::writeNoBlanksFile(ifstream &inputFile, ofstream &noBlanksOutFile){
	char currentCharacter;
	bool gotNewLine = false;
	bool readingComment = false;
	bool readingInlineComment = false;
	bool wroteFirstChar = false;

	cout << "Characters written to .noblanks output file--\n-->";
	while(inputFile >> std::noskipws >> currentCharacter){
		if (gotNewLine){
			if (currentCharacter == 'c'){
				if (inputFile.peek() == '*'){ // got c* full-line comment
					readingComment = true;
					gotNewLine = false;
					inputFile >> currentCharacter;
				}
			}
			if (currentCharacter == '/'){
				if (inputFile.peek() == '/'){ // got // full-line comment
					readingComment = true;
					gotNewLine = false;
					inputFile >> currentCharacter;
				}
			}
		}
		else {
			if (currentCharacter == '/'){
				if (inputFile.peek() == '/'){ // got // in-line comment
					readingInlineComment = true;
					inputFile >> currentCharacter;
				}
			}
		}

		if (currentCharacter == '\n'){ // got new line character
			if (!readingComment){
				gotNewLine = true;
			}
			readingComment = false;
			readingInlineComment = false;
		}

		if (!readingComment && !readingInlineComment) {
			if (!isspace(currentCharacter)){
				if (wroteFirstChar){
					if (gotNewLine){
						gotNewLine = false;
						cout << '\n';
						noBlanksOutFile << '\n';
					}
				}
				cout << (char) toupper(currentCharacter);
				noBlanksOutFile << (char) toupper(currentCharacter);
				gotNewLine = false;
				wroteFirstChar = true;
			}
		}
	}
	cout << "<-----End Of OutputFile\n";

	// cout << "\t\t[FILE MANAGER]: Successfully Created " << globalFileName << ".noblanks\n";
	return true;
}