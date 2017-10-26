/*
  ==============================================================================

	File: FileManger.cpp
	Author: Brendan Thompson
	Updated: 10/12/17

	Description: Implementation of main FileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class

  ==============================================================================
*/

#include "FileManager.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

// Instantiates a FileManager object
FileManager::FileManager(){
	keepObjFile = true;
	keepNoBlanksFile = false;
	return ;
}

// Shuts down the FileManager by calling removeFiles()
FileManager::~FileManager(){
	removeFiles();
	cout << "\t\t[FILE MANAGER]: Shutdown FileManager\n";
	return;
}

/* ==============================================================================
	Public Pre-Compiling Methods
============================================================================== */

// parses the flags and manages the global flag bools
void FileManager::setFlags(char *arrayOfFlags, int numberOfFlags){
	char currentFlag;

	for (int i = 0; i < numberOfFlags; i++){
		currentFlag = arrayOfFlags[i];
		if ((currentFlag == 'n') || (currentFlag == 'N')){
			keepNoBlanksFile = true;
		}
		if ((currentFlag == 'o') || (currentFlag == 'O')){
			keepObjFile = true;
		}
	}
}

// Sets the FileManagers's Global FileNames & Links to the ParentLineManager
bool FileManager::prepareForCompilation(string fileToCompile, LineLabelTable *lineManager){
	ParentLineManager = lineManager;
	bool successfullyPrepared = false;

	// Create Global File Names & Open All Files
	createFileNames(fileToCompile);
	successfullyPrepared = openFirstFiles(fileToCompile);
	if (!successfullyPrepared){
		cout << "\t\t[FILE MANAGER]: Error! Unable to Prepare Files for Preprocessing\n";
	}

	return successfullyPrepared;
}

// Creates & Opens the preprocessed .noblanks file & upon completion returns status of success
bool FileManager::preprocessFile(){
	bool successfullyPreprocessed = false;

	// Preprocess Files
	gatherLineLabels();
	inputFile.seekg(0, ifstream::beg);

	writeNoBlanksFile();

	// Open & Close Files
	inputFile.close();
	noBlanksOutFile.close();
	successfullyPreprocessed = openCompilationFiles();

	if (!successfullyPreprocessed){
		cout << "\t\t[FILE MANAGER]: Error! Unable to Preprocess File\n";
	}
	else {
		cout << "\t\t[FILE MANAGER]: Preprocesses Successfully. Prepared to Compile...\n";
	}
	return successfullyPreprocessed;
}

/* ==============================================================================
	Public File IO Methods
============================================================================== */

// Returns the next line from the preprocessed file (.noblanks), else returns "@"
string FileManager::getNextLine(){
	string currentLine;
	if (!(preprocessedInFile.eof())){
		getline(preprocessedInFile, currentLine);
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
	objOutFile << value;
	// cout << "\t\t[FILE MANAGER]: Wrote " << value << " to .obj\n";
	return;
}

// Writes the int "value" to the .obj output file
void FileManager::writeNumToObj (int value){
	objOutFile << value;
	// cout << "\t\t[FILE MANAGER]: Wrote " << value << " to .obj\n";
	return;
}

// Writes the string "currentString" to the .obj output file
void FileManager::writeStringToObj (string currentString){
	int i = 0;
	while (currentString[i] != '\0'){
		objOutFile << currentString[i];
		// cout << "\t\t[FILE MANAGER]: Wrote " << currentString[i] << " to .obj\n";
		i++;
	}
	return;
}

/* ==============================================================================
	Private File Management Functions
============================================================================== */

// Sets the global file names
void FileManager::createFileNames(string originalFileName){
	// Create the File Prefixes
	// const char transyFileType[8] = ".transy";
	const char noBlankFileType[10] = ".noblanks";
	const char objOutFileType[5] = ".obj";

	// Clear the File Names
	strcpy(globalFileStem, "");
	strcpy(globalPreprocessedFileName, "");
	strcpy(globalObjFileName, "");

	// cout << "\nTransy File\t\tStem\t\tNo Blank File\t\tPreprocessedFile\t\tobjOutFile\n";
	// cout << originalFileName << "\t" << globalFileStem << "\t" << globalPreprocessedFileName << "\t" << globalObjFileName << endl;
	// cout << endl;


	// parse the originalFileName and get the stem
	bool notFinished = true;
	int iterator = 0;
	char currentCharacter;

    // cout << "Attempting to find stem of " << originalFileName << endl;
    while (notFinished){
    	currentCharacter = originalFileName[iterator];
    	// cout << "CurrentChar: " << currentCharacter << endl;
    	if (currentCharacter == '.'){
    		globalFileStem[iterator] = '\0';
    		notFinished = false;
    	}
    	else {
    		globalFileStem[iterator] = currentCharacter;
    	}
    	iterator++;
    }

    // create other file names
    strcpy(globalPreprocessedFileName, globalFileStem);
    strcpy(globalObjFileName, globalFileStem);
    strcat(globalPreprocessedFileName, noBlankFileType);
	strcat(globalObjFileName, objOutFileType);

	return;
}

// opens .transy input file and noblanks output file
bool FileManager::openFirstFiles(string inputFileName){
	// INFILES
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << inputFileName << " for input..." << endl;
    inputFile.open(inputFileName.c_str());
    if (!inputFile) {
        cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open " << inputFileName << " for input" << endl;
        return false;
    }

	// OUTFILES
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalPreprocessedFileName << " for input..." << endl;
	noBlanksOutFile.open(globalPreprocessedFileName);
	if (!noBlanksOutFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open "<< globalPreprocessedFileName << " for input" <<endl;
        return false;
	}

	return true;
}

// opens .noblanks input file & .obj output file
bool FileManager::openCompilationFiles(){
	// INFILES
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalPreprocessedFileName << " for input..." << endl;
	preprocessedInFile.open(globalPreprocessedFileName);
	if (!preprocessedInFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open "<< globalPreprocessedFileName << " for input" <<endl;
        return false;
	}

	// OUTFILES
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalObjFileName << " for output..." << endl;
	objOutFile.open(globalObjFileName);
	if (!objOutFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .obj output file" <<endl;
        return false;
	}

	return true;
}

// conditionally removes .noblanks & .obj
void FileManager::removeFiles(){
	preprocessedInFile.close();
	objOutFile.close();

	if (!keepNoBlanksFile){
		cout << "\t\t[FILE MANAGER]: Removing " << globalPreprocessedFileName << "...\n";
		remove(globalPreprocessedFileName);
	}
	if (!keepObjFile){
		cout << "\t\t[FILE MANAGER]: Removing " << globalObjFileName << "...\n";
		remove(globalObjFileName);
	}
}

/* ==============================================================================
	Private Line Label Reading Functions (First Pass)
============================================================================== */

// Parses the file and syncs line labels with the ParentLineManager
void FileManager::gatherLineLabels(){
	string currentLine;
	string lineLabel;
	int currentLineNumber = 0;
	int numCharsInLineLabel;

	while (!(inputFile.eof())){
		getline(inputFile, currentLine);
		// cout << "\t\t[FILE MANAGER]: Checking for Label in Line: " << currentLine << endl;
		numCharsInLineLabel = checkForLineLabel(currentLine);

		if (numCharsInLineLabel > 0){ // Found Line Label
			lineLabel = currentLine.substr(0, numCharsInLineLabel);
			// cout << "\t\t[FILE MANAGER]: Found Line Label: " << lineLabel << endl;
			(*ParentLineManager).addLineLabel(lineLabel, currentLineNumber);
		}
		currentLineNumber++;
	}
}

// Parses the line looking for a : to signify a line label, and returns index
int FileManager::checkForLineLabel(string currentLine){
	char currentCharacter;
	int currentCharIndex = 0;
	int indexColonInLabel = NO_LINE_LABEL;
	bool continueSearching = true;

	while (continueSearching){
		currentCharacter = currentLine[currentCharIndex];

		// Found Line Label, set indexColonInLabel & stop searching
		if (currentCharacter == ':'){
			// cout << "\t\t[FILE MANAGER]: Found Line Label in line: " << currentLine << endl;
			continueSearching = false;
			indexColonInLabel = currentCharIndex;
		}

		// Got // Comment, stop searching
		if (currentCharacter == '/'){
			continueSearching = false;
		}

		// Got c* Comment, stop searching
		if (((currentCharacter == 'c') || (currentCharacter == 'C')) && (currentLine[currentCharIndex + 1] == '*')){
			continueSearching = false;
		}

		// Got Comma, stop searching
		if (currentCharacter == ','){
			continueSearching = false;
		}

		// Got Open Bracket, stop searching
		if (currentCharacter == '['){
			continueSearching = false;
		}

		// Got Open Bracket, stop searching
		if (currentCharacter == '='){
			continueSearching = false;
		}

		// Got End Of Line, stop searching
		if (currentCharacter == '\0'){
			continueSearching = false;
		}

		currentCharIndex++;
	}

	return indexColonInLabel;
}

/* ==============================================================================
	Private No-Blanks Writing Functions
============================================================================== */

// Writes <fileName>.noBlanks by removing whitespace and unifying everything to upper case
bool FileManager::writeNoBlanksFile(){
	string currentLine;
	int currentLineNumber = 0;
	bool validLineToAdd = false;
	bool wroteFirstLine = false;

	while (!(inputFile.eof())){
		getline(inputFile, currentLine);
		// cout << "\t\t[FILE MANAGER]: Got Line: " << currentLine << endl;
		validLineToAdd = checkCurrentLine(&currentLine);

		if (validLineToAdd){  // Valid Line to Preprocess
			// cout << "\t\t[FILE MANAGER]: Adding " << currentLine << " to .noblanks file\n";
			if (wroteFirstLine){
				noBlanksOutFile << endl;
			}
			else {
				wroteFirstLine = true;
			}
			noBlanksOutFile << currentLine;
			(*ParentLineManager).addLine(currentLineNumber);
		}
		currentLineNumber++;
	}
}

// iterates through the line, changes *currentLine to a proper version, and returns whether or not it is a valid line to add to the .noblanks file
bool FileManager::checkCurrentLine(string *currentLine) {
	// cout << "\n\t\t\t[FILE MANAGER]: Checking Line -->" << (*currentLine) << "<--\n";
	string newVersionOfLine;
	char currentCharacter;
	int oldLineCursor = 0;
	int newLineCursor = 0;

	int lengthOfString = (*currentLine).length();
	bool continueParsingLine = true;
	bool validLineToAdd = false;

	currentCharacter = (*currentLine)[0];

	// Check For Line Label
	int indexLineLabel = checkForLineLabel((*currentLine));
	if ((continueParsingLine) && (indexLineLabel != NO_LINE_LABEL)){

		// Trim Off Line Label
		int numCharsInString = (*currentLine).length();
		newVersionOfLine = (*currentLine).substr(indexLineLabel + 1, numCharsInString);
		// cout << "\t\t\t[FILE MANAGER]: Found Line label. Changing -->" << (*currentLine) << "<-- to -->" << newVersionOfLine << "<--\n";
		(*currentLine) = newVersionOfLine;

		// Reset Parser
		lengthOfString = (*currentLine).length();
		newVersionOfLine = "";
		currentCharacter = (*currentLine)[0];
	}

	// line is empty
	if (lengthOfString == 0){
		// cout << "\t\t\t[FILE MANAGER]: Line is empty, returning false...\n";
		continueParsingLine = false;
		validLineToAdd = false;
	}

	// line starts with "c*" full-line comment
	if (((currentCharacter == 'c') || (currentCharacter == 'C'))){
		if ((*currentLine)[1] == '*'){
			// cout << "\t\t\t[FILE MANAGER]: Line started with c* full line comment, returning false...\n";
			continueParsingLine = false;
			validLineToAdd = false;
		}
	}

	// line starts with "//" full-line comment
	if (currentCharacter == '/'){
		if ((*currentLine)[1] == '/'){
			// cout << "\t\t\t[FILE MANAGER]: Line started with // full line comment, returning false...\n";
			continueParsingLine = false;
			validLineToAdd = false;
		}
	}

	// Parse through the line
	for (int i = 0; (i < lengthOfString) && continueParsingLine; i++){


		// current character is NOT a space or a tab and therefore it is a valid character that needs to be added
		if (! ((currentCharacter == ' ') || (currentCharacter == '\t')) ){
			newVersionOfLine += ((char) toupper(currentCharacter));
			newLineCursor++;
			validLineToAdd = true;
			// cout << "\t\t\t[FILE MANAGER]: " << currentCharacter << " is a valid character. New Version of Line: " << newVersionOfLine << endl;
		}

		oldLineCursor++;
		currentCharacter = (*currentLine)[oldLineCursor];
		// cout << "\t\t\t[FILE MANAGER]: Checking Character: " << currentCharacter << endl;

		// "//" comment starting
		if (currentCharacter == '/'){
			if ((*currentLine)[oldLineCursor + 1] == '/'){ // got // full-line comment
				newVersionOfLine[newLineCursor] = '\n';
				continueParsingLine = false;
				validLineToAdd = true;
			}
		}

		// new line character not first character
		if (currentCharacter == '\r'){
			continueParsingLine = false;
			validLineToAdd = true;
		}
	}

	// cout << "\t\t\t[FILE MANAGER]: Changing -->" << (*currentLine) << "<-- to -->" << newVersionOfLine << "<--\n";
	(*currentLine) = newVersionOfLine;
	return validLineToAdd;
}
