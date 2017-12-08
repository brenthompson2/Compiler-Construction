/* ==============================================================================

	File: FileManger.cpp
	Author: Brendan Thompson
	Updated: 10/30/17

	Description: Implementation of main FileManager for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- opens .transy, .obj, .noblanks, .literal, and .core files
		- syncs lineLabels with LineLabelTable
		- preprocesses .transy into .noblanks
		- upon request hands the compiler one line at a time from the preprocessed file
		- writes char/string/int to .obj file
		- writes one literal at a time to .literal
		- writes one ID at a time to .core
		- compiler command flags determine what files are kept (-n -o -l -c)

============================================================================== */

#include "FileManager.h"

/* ==============================================================================
	Constructor & Destructor
============================================================================== */

// Instantiates a FileManager object
FileManager::FileManager(){
	keepObjFlag = false;
	keepNoBlanksFlag = false;
	keepLiteralFlag = false;
	keepCoreFlag = false;
	// cout << "\t\t[FileManager]: Initialized FileManager\n";
	return ;
}

// Shuts down the FileManager by calling removeFiles()
FileManager::~FileManager(){
	removeFiles();
	// cout << "\t\t[FILE MANAGER]: Shutdown FileManager\n";
	return;
}

/* ==============================================================================
	Public Pre-Compiling Methods
============================================================================== */

// Sets the FileManagers's Global FileNames & Links to the Parent's LineManager
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
	globalInputFile.clear();
	globalInputFile.seekg(0);

	// cout << "\t\t[FILE MANAGER]: Attempting to writeNoBlanksFile...\n";
	writeNoBlanksFile();

	// Open & Close Files
	globalInputFile.close();
	noBlanksOutFile.close();
	successfullyPreprocessed = openCompilationFiles();

	if (!successfullyPreprocessed){
		cout << "\t\t[FILE MANAGER]: Error! Unable to Preprocess File\n";
	}
	else {
		// cout << "\t\t[FILE MANAGER]: Preprocessed Successfully. Prepared to Compile...\n";
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

// Writes the int "value" to the .obj output file
void FileManager::writeNumToObj (double value){
	objOutFile << std::setprecision(8) << value;
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

// Writes the string "currentString" to the .literal output file
void FileManager::writeStringToLiteral (string currentString){
	int i = 0;
	while (currentString[i] != '\0'){
		literalOutFile << currentString[i];
		// cout << "\t\t[FILE MANAGER]: Wrote " << currentString[i] << " to .literal\n";
		i++;
	}
	return;
}

// Writes the double "value" to the .literal output file
void FileManager::writeNumToLiteral (double value){
	literalOutFile << std::setprecision(8) << value;
	// cout << "\t\t[FILE MANAGER]: Wrote " << value << " to .obj\n";
	return;
}

// Writes the string "currentString" to the .core output file
void FileManager::writeStringToCore (string currentString){
	int i = 0;
	while (currentString[i] != '\0'){
		coreOutFile << currentString[i];
		// cout << "\t\t[FILE MANAGER]: Wrote " << currentString[i] << " to .core\n";
		i++;
	}
	return;
}

// Writes the double "value" to the .core output file
void FileManager::writeNumToCore (double value){
	coreOutFile << std::setprecision(8) << value;
	// cout << "\t\t[FILE MANAGER]: Wrote " << value << " to .obj\n";
	return;
}

/* ==============================================================================
	Public Flag Methods
============================================================================== */

// parses the flags and manages the global flag bools
void FileManager::setFlags(char *arrayOfFlags, int numberOfFlags){
	char currentFlag;

	for (int i = 0; i < numberOfFlags; i++){
		currentFlag = arrayOfFlags[i];
		if ((currentFlag == 'n') || (currentFlag == 'N')){
			keepNoBlanksFlag = true;
		}
		if ((currentFlag == 'o') || (currentFlag == 'O')){
			keepObjFlag = true;
		}
		if ((currentFlag == 'l') || (currentFlag == 'L')){
			keepLiteralFlag = true;
		}
		if ((currentFlag == 'c') || (currentFlag == 'C')){
			keepCoreFlag = true;
		}
	}
	return;
}

// sets the keepObjFlag to true
void FileManager::setCompilationResult(bool completedSuccessfully){
	if (completedSuccessfully){
		keepObjFlag = true;
		keepLiteralFlag = true;
		keepCoreFlag = true;
	}
	return;
}

/* ==============================================================================
	Private File Management Functions
============================================================================== */

// Sets the global file names
void FileManager::createFileNames(string originalFileName){
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
    strcat(globalPreprocessedFileName, noBlankFileType);
    strcpy(globalObjFileName, globalFileStem);
	strcat(globalObjFileName, objOutFileType);
    strcpy(globalLiteralFileName, globalFileStem);
	strcat(globalLiteralFileName, literalOutFileType);
    strcpy(globalCoreFileName, globalFileStem);
	strcat(globalCoreFileName, coreOutFileType);

	return;
}

// opens .transy input file and noblanks output file
bool FileManager::openFirstFiles(string inputFileName){
	// INFILES
    // cout << "\t\t[FILE MANAGER]: Attempting to open " << inputFileName << " for input..." << endl;
    globalInputFile.open(inputFileName.c_str());
    if (!globalInputFile) {
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

    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalLiteralFileName << " for output..." << endl;
	literalOutFile.open(globalLiteralFileName);
	if (!literalOutFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .literal output file" <<endl;
        return false;
	}

    // cout << "\t\t[FILE MANAGER]: Attempting to open " << globalCoreFileName << " for output..." << endl;
	coreOutFile.open(globalCoreFileName);
	if (!coreOutFile) {
		cerr << "\t\t[FILE MANAGER]: ERROR: Failed to open .core output file" <<endl;
        return false;
	}

	return true;
}

// conditionally removes .noblanks & .obj
void FileManager::removeFiles(){
	preprocessedInFile.close();
	objOutFile.close();
	literalOutFile.close();
	coreOutFile.close();

	if (!keepNoBlanksFlag){
		// cout << "\t\t[FILE MANAGER]: Removing " << globalPreprocessedFileName << "...\n";
		remove(globalPreprocessedFileName);
	}
	if (!keepObjFlag){
		// cout << "\t\t[FILE MANAGER]: Removing " << globalObjFileName << "...\n";
		remove(globalObjFileName);
	}
	if (!keepLiteralFlag){
		// cout << "\t\t[FILE MANAGER]: Removing " << globalLiteralFileName << "...\n";
		remove(globalLiteralFileName);
	}
	if (!keepCoreFlag){
		// cout << "\t\t[FILE MANAGER]: Removing " << globalCoreFileName << "...\n";
		remove(globalCoreFileName);
	}
	return;
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

	while (!(globalInputFile.eof())){
		getline(globalInputFile, currentLine);
		// cout << "\t\t[FILE MANAGER]: Checking for Label in Line: " << currentLine << endl;
		numCharsInLineLabel = checkForLineLabel(currentLine);

		if (numCharsInLineLabel > 0){ // Found Line Label
			lineLabel = currentLine.substr(0, numCharsInLineLabel);
			// cout << "\t\t[FILE MANAGER]: Found Line Label: " << lineLabel << endl;
			(*ParentLineManager).addLineLabel(lineLabel, currentLineNumber);
		}
		currentLineNumber++;
	}
	return;
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

		// Got Open Quote, stop searching
		if (currentCharacter == '"'){
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

	while (!(globalInputFile.eof())){
		getline(globalInputFile, currentLine);
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
	bool parsingLiteral = false;
	bool continueParsingLine = true;
	bool validLineToAdd = true;

	currentCharacter = (*currentLine)[0];

	// Check For Line Label
	int indexLineLabel = checkForLineLabel((*currentLine));
	if (indexLineLabel != NO_LINE_LABEL){

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

		if (parsingLiteral) {
			// new line character during literal
			if (currentCharacter == '\r'){
				continueParsingLine = false;
				cerr << "\t\t\t[FILE MANAGER]: Found end of line before end of quote: " << *currentLine << endl;
			}
			newVersionOfLine += currentCharacter;
			newLineCursor++;
			// cout << "\t\t\t[FILE MANAGER]: " << currentCharacter << " is part of a literal. New Version of Line: " << newVersionOfLine << endl;
		}
		else { // current character is NOT part of a literal, a space, or a tab and therefore it is a valid character that needs to be added
			if (! ((currentCharacter == ' ') || (currentCharacter == '\t')) ){
				newVersionOfLine += ((char) toupper(currentCharacter));
				newLineCursor++;
				// cout << "\t\t\t[FILE MANAGER]: " << currentCharacter << " is a valid character. New Version of Line: " << newVersionOfLine << endl;
			}
		}

		oldLineCursor++;
		currentCharacter = (*currentLine)[oldLineCursor];
		// cout << "\t\t\t[FILE MANAGER]: Checking Character: \"" << currentCharacter << "\"\n";

		// "//" comment starting
		if (currentCharacter == '/'){
			if ((*currentLine)[oldLineCursor + 1] == '/'){ // got // full-line comment
				newVersionOfLine[newLineCursor] = '\n';
				continueParsingLine = false;
			}
		}

		// new line character mid line
		if (currentCharacter == '\r'){
			continueParsingLine = false;
		}

		// found "literal in quotes"
		if (currentCharacter == '\"'){
			if (!parsingLiteral) {
				// cout << "\t\t\t[FILE MANAGER]: Started Parsing literal\n";
				parsingLiteral = true;
			}
			else {
				// cout << "\t\t\t[FILE MANAGER]: Finished Parsing literal\n";
				parsingLiteral = false;
			}
		}
	}

	// cout << "\t\t\t[FILE MANAGER]: Changing -->" << (*currentLine) << "<-- to -->" << newVersionOfLine << "<--\n";
	(*currentLine) = newVersionOfLine;
	return validLineToAdd;
}
