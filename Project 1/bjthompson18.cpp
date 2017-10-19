// Project 1
// Brendan Thompson
// 09/06/2017

// Reads in a user specified file and outputs it as trimmedOutput.txt after removing all white spaces and blank lines

#include <iostream>	// Console IO
#include <fstream>	// File IO
#include <stdlib.h>	// Exit()
using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::ifstream;
using std::ofstream;

#define MAX_STRING_LENGTH 50

void prepareFileIO(ifstream &inFile, ofstream &outFile);
void closeFileIO(ifstream &inFile, ofstream &outFile);
void writeCharToFile (char value, ofstream &outFile);


int main (){

	ifstream inputFile;
	ofstream outputFile;

	prepareFileIO(inputFile, outputFile);

	char currentCharacter;
	bool gotNewLine = false;

	// cout << "Characters written to trimmedOutput.txt--\n-->";

	while(inputFile >> std::noskipws >> currentCharacter){
		if (currentCharacter == '\n'){
			gotNewLine = true;
		}
		if (!isspace(currentCharacter)){
			if (gotNewLine){
				gotNewLine = false;
				// cout << '\n';
				writeCharToFile ('\n', outputFile);
			}
			// cout << currentCharacter;
			writeCharToFile (currentCharacter, outputFile);
		}
	}

	// cout << "<-----End Of OutputFile-->\n";

	closeFileIO(inputFile, outputFile);

	cout << "Successfully outputted trimmedOutput.txt\n";

	return 0;
}

void prepareFileIO(ifstream &inFile, ofstream &outFile){
	char fileName[MAX_STRING_LENGTH];
	//attempt to open inFile
	cout<<"What file would you like to read in? ";
	cin>>fileName;
    // cout << "Attempting to open " << fileName << " ..." << endl;
    inFile.open(fileName);
    if (!inFile) {
        cerr << "Can't open " << fileName << " for input; aborting..." << endl;
        exit(1);
    }

	//attempt to open outFile
    // cout << "Attempting to open trimmedOutput.txt..." << endl;
	outFile.open("trimmedOutput.txt");
	if (!outFile)
	{
		cerr << "Failed to open output file: aborting..." <<endl;
		exit(1);
	}

}

void closeFileIO(ifstream &inFile, ofstream &outFile){
	inFile.close();
	outFile.close();
}

void writeCharToFile (char value, ofstream &outFile){
	outFile << value;
}
