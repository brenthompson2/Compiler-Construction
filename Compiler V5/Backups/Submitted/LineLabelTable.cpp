/* =============================================================================

	File: LineLabelTable.cpp
	Author: Brendan Thompson
	Updated: 10/30/17

	Description: Implementation for LineLabelTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class
		- manages Line Label names and their associated .obj & .transy line numbers
		- Max 1000 lines in the program

==============================================================================*/

#include "LineLabelTable.h"


/* ==============================================================================
Constructor & Destructor
============================================================================== */

LineLabelTable::LineLabelTable(){
	globalNumLinesOfCode = 0;
	globalNumLabels = 0;
	// cout << "\t\t[LineLabelTable]: Initialized LineLabelTable\n";
	return;
}

LineLabelTable::~LineLabelTable(){
	// cout << "\t\t[LineLabelTable]: Shutdown LineLabelTable\n";
	return;
}

/* ==============================================================================
	Public Manipulator Methods
============================================================================== */

// adds a new line to the LineLabelTable by mapping it's transyLineNumber
void LineLabelTable::addLine(int actualTransyLineNumber){
	// cout << "\t\t\t[LineLabelTable]: Mapping line #: " << globalNumLinesOfCode << " to transy line #: " << actualTransyLineNumber << endl;

	LineNumberArray[globalNumLinesOfCode] = actualTransyLineNumber;
	globalNumLinesOfCode++;

	return;
}

// adds a label to the table index associated with the transyLineNumber
void LineLabelTable::addLineLabel(string newLineLabel, int newTransyLineNumber){
	transform(newLineLabel.begin(), newLineLabel.end(), newLineLabel.begin(), ::toupper); // Converts Label to Upper Case

	if (alreadyExists(newLineLabel)){
		cout << "\t\t\t[LineLabelTable]: Error: " << newLineLabel << " already exists\n";
	}
	else {
		// cout << "\t\t\t[LineLabelTable]: Adding Line Label " << newLineLabel << " to Line Label Table for .transy file line number: " << newTransyLineNumber << endl;
		LineLabelArray[globalNumLabels].labelName = newLineLabel;
		LineLabelArray[globalNumLabels].transyLineNumber = newTransyLineNumber;
		globalNumLabels++;
	}

	return;
}

// Iterates through line labels and sets the objLineNumber to the next appropriate line of obj code, decided by the transyLineNumber, and returns num labels after last line of actual code
int LineLabelTable::syncLabelsWithLines(){
	cout << "\t\t\t[LineLabelTable]: Syncing " << globalNumLabels << " Line Labels with Line Numbers\n";

	string currentLineLabel;
	int currentTransyLineNumber;
	bool foundNewLineNumber;
	int numErrors = 0;

	for (int labelIterator = 0; labelIterator < globalNumLabels; labelIterator++){
		currentLineLabel = LineLabelArray[labelIterator].labelName;
		currentTransyLineNumber = LineLabelArray[labelIterator].transyLineNumber;
		foundNewLineNumber = false;

		// Get Appropriate Transy Line
		int lineIterator = 0;
		while (!foundNewLineNumber){
			int tempTransyLineNumber = LineNumberArray[lineIterator];

			if (tempTransyLineNumber < currentTransyLineNumber){
				lineIterator++;
			}
			else {
				if (LineLabelArray[labelIterator].objLineNumber == lineIterator) {
					// cout << "\t\t\t\t[LineLabelTable]: Line Label " << currentLineLabel << " already correct at " << LineLabelArray[labelIterator].objLineNumber << endl;
				}
				else {
					// cout << "\t\t\t\t[LineLabelTable]: Changing OBJ Line For " << currentLineLabel << " from " << LineLabelArray[labelIterator].objLineNumber << " to " << lineIterator << endl;
					LineLabelArray[labelIterator].objLineNumber = lineIterator;
				}
				foundNewLineNumber = true;
			}

			// Catch Running Past Num Lines of Code
			if (lineIterator >= globalNumLinesOfCode){
				foundNewLineNumber = true;
				cout << "\t\t\t\t[LineLabelTable]: Error: Can not find a line of Transy code after line label " << currentLineLabel << " on line " << currentTransyLineNumber << endl;
				LineLabelArray[labelIterator].objLineNumber = NOT_FOUND_IN_ARRAY;
				numErrors++;
			}
		}
	}

	return numErrors;
}

/* ==============================================================================
	Public Accessor Methods
============================================================================== */

// returns the TransyLineNumber for the currentObjLineNumber
int LineLabelTable::getTransyLineNumber(int currentObjLineNumber){
 	int associatedLineNumber;

 	if (currentObjLineNumber < globalNumLinesOfCode){
 		associatedLineNumber = LineNumberArray[currentObjLineNumber];
 	}
 	else {
 		associatedLineNumber = NOT_FOUND_IN_ARRAY;
 	}

 	return associatedLineNumber;
 }

// returns the currentObjLineNumber for the nameOfLabel
int LineLabelTable::getObjLineNumber(string nameOfLabel){
 	int associatedLineNumber = NOT_FOUND_IN_ARRAY;

 	for (int i = 0; i < globalNumLabels; i++){
		if (LineLabelArray[i].labelName == nameOfLabel){
			associatedLineNumber = LineLabelArray[i].objLineNumber;
			break;
		}
 	}

 	return associatedLineNumber;
 }

// iterates through the LineLabelTable and prints the labelName & transyLineNumber
void LineLabelTable::printLineLabelTable(){
	cout << "\t\t\t[LineLabelTable]: Line Label Table currently has " << globalNumLabels << " labels\n";

	for (int i = 0; i < globalNumLabels; i++){
		cout << "\t\t\t" << LineLabelArray[i].labelName << "\tOBJ#: " << LineLabelArray[i].objLineNumber << "\tTransy#: " << LineLabelArray[i].transyLineNumber << endl;
	}

	return;
}

// iterates through the LineNumberArray and prints the matching .transy line
void LineLabelTable::printLineMapping(){
	cout << "\t\t\t[LineLabelTable]: Line Mapper currently has " << globalNumLinesOfCode << " lines\n";

	for (int i = 0; i < globalNumLinesOfCode; i++){
		cout << "\t\t\tOBJ#: " << i << ":\tTransy#: " << LineNumberArray[i] << endl;
	}

	return;
}

/* ==============================================================================
	Private Manipulator Methods
============================================================================== */

/* ==============================================================================
	Private Accessor Methods
============================================================================== */

// returns whether or not the line label already exists
bool LineLabelTable::alreadyExists(string currentLineLabel){
	bool wasFound = false;

 	for (int i = 0; i < globalNumLabels; i++){
		if (LineLabelArray[i].labelName == currentLineLabel){
			wasFound = true;
			break;
		}
 	}

 	return wasFound;

}