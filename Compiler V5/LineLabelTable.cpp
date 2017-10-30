/* =============================================================================

	File: LineLabelTable.cpp
	Author: Brendan Thompson
	Updated: 10/13/17

	Description: Implementation for LineLabelTable for Compiler object made for Transylvania University University Fall Term 2017 Compiler Construction class


==============================================================================*/

#include "LineLabelTable.h"


/* ==============================================================================
Constructor & Destructor
============================================================================== */

LineLabelTable::LineLabelTable(){
	globalNumLinesOfCode = 0;
	globalNumLabels = 0;
	cout << "\t\t[LineLabelTable]: Initialized LineLabelTable\n";
	return;
}

LineLabelTable::~LineLabelTable(){
	cout << "\t\t[LineLabelTable]: Shutdown LineLabelTable\n";
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
			associatedLineNumber = i;
			break;
		}
 	}

 	return associatedLineNumber;
 }

// iterates through the LineLabelTable and prints the labelName & transyLineNumber
void LineLabelTable::printLineLabelTable(){
	cout << "\t\t\t[LineLabelTable]: Line Label Table currently has " << globalNumLabels << " labels\n";

	for (int i = 0; i < globalNumLabels; i++){
		cout << "\t\t\tOBJ#: " << i << ":\t" << LineLabelArray[i].labelName << "\tTransy#: " << LineLabelArray[i].transyLineNumber << endl;
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