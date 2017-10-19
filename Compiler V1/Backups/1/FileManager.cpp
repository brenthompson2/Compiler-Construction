/*
  ==============================================================================

	File: FileManger.cpp
	Author: Brendan Thompson
	Updated: 09/24/17

	Description: Implementation of main FileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/


#include "FileManager.h"


/* ==============================================================================
Constructor & Destructor
============================================================================== */

// Instantiates a FileManager object which opens Input and Output files
FileManager::FileManager(){

	if (!prepareFileIO()){
		cout << "\t\t[FILE MANAGER]: ERROR: failed to open files. Aborting...\n";
		exit(1);
	}

	cout << "\t\t[FILE MANAGER]: Preprocessed .transy file\n";
	return ;
}

// Shuts down the FileManager by closing input & output files
void FileManager::shutdown(){
	preprocessedFile.close();
	objFile.close();
	cout << "\t\t[FILE MANAGER]: Shutdown FileManager\n";
}

/* ==============================================================================
	Public Functions
============================================================================== */

// prepares for compilation by preprocessing the .transy file into .noblanks by removing blank lines, spaces, and unifying all characters to uppercase and then re-opening the preprocessed file
bool FileManager::prepareForCompilation(){
	char currentCharacter;
	bool gotNewLine = false;

	// cout << "Characters written to .noblanks output file--\n-->";
	while(globalInputFile >> std::noskipws >> currentCharacter){
		if (currentCharacter == '\n'){
			gotNewLine = true;
		}
		if (!isspace(currentCharacter)){
			if (gotNewLine){
				gotNewLine = false;
				// cout << '\n';
				writeCharToNoBlanks ('\n');
			}
			// cout << currentCharacter;
			writeCharToNoBlanks (toupper(currentCharacter));
		}
	}
	// cout << "<-----End Of OutputFile-->\n";

	// cout << "Successfully Created " << globalFileName << ".noblanks\n";

	globalInputFile.close();
	noBlanksFile.close();

	// Prepare to compile preprocessed file
	// attempt to open preprocessed file
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << preprocessedFileName << " for input..." << endl;
	preprocessedFile.open(preprocessedFileName);
	if (!preprocessedFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open preprocessed input file" <<endl;
        return false;
	}

	return true;
}

// Returns the next line from the preprocessed file (.noblanks)
string FileManager::getNextLine(){
	string currentLine;
	if (!(preprocessedFile.eof())){
		getline(preprocessedFile, currentLine);
		// cout << "\t\t[FILE MANAGER]: Got Line: " << currentLine << endl;
	}
	else {
		currentLine = "@";
		// cout << "\t\t[FILE MANAGER]: Found End Of File: " << currentLine << endl;
	}
	return currentLine;
}

// Writes the char "value" to the .obj output file
void FileManager::writeCharToObj (char value){
	objFile << value;
}

// Writes the char "value" to the .obj output file
void FileManager::writeNumToObj (int value){
	objFile << value;
}

/* ==============================================================================
	Private File IO Functions
============================================================================== */

// Opens Input & Output Files
bool FileManager::prepareFileIO(){
	char transyFileName[MAX_STRING_LENGTH];
	char noBlankFileName[MAX_STRING_LENGTH];
	char objFileName[MAX_STRING_LENGTH];

	//attempt to open globalInputFile
	cout<<"\nWhat file would you like to read in? ";
	cin>>transyFileName;
    // cout << "Attempting to open " << transyFileName << " ..." << endl;
    globalInputFile.open(transyFileName);
    if (!globalInputFile) {
        cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open " << transyFileName << " for input" << endl;
        return false;
    }

    createFileNames(transyFileName, noBlankFileName, objFileName);

	//attempt to open output files
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << noBlankFileName << " for output..." << endl;
	noBlanksFile.open(noBlankFileName);
	if (!noBlanksFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .noblanks output file" <<endl;
        return false;
	}
    cout << "\t\t[FILE MANAGER]: Attempting to open " << objFileName << " for output..." << endl;
	objFile.open(objFileName);
	if (!objFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .obj output file" <<endl;
        return false;
	}

	return true;
}

// Trims the originalFileName & defines globalFileName, noBlanksFileName, and objFileName
void FileManager::createFileNames(char* originalFileName, char* noBlankFileName, char* objFileName){
	const char noBlankFileType[10] = ".noblanks";
	const char objFileType[5] = ".obj";

	//get globalFileName, create .noblanks, and create .obj
    // cout << "Attempting to find stem of " << originalFileName << endl;
    strcpy(globalFileName, originalFileName);
    for (int i = 0; i < MAX_STRING_LENGTH; i++){
    	if (globalFileName[i] == '.'){
    		globalFileName[i] = '\0';
    		strcpy(noBlankFileName, globalFileName);
    		strcat(noBlankFileName, noBlankFileType);
    		strcpy(objFileName, globalFileName);
    		strcat(objFileName, objFileType);
    		strcpy(preprocessedFileName, noBlankFileName);
    	}
    }
    // cout << "The stem of " << originalFileName << " is " << globalFileName << "<--" << endl;
}

// Writes the char "value" to the .noblanks output file
void FileManager::writeCharToNoBlanks (char value){
	noBlanksFile << value;
}
