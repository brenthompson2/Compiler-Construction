/* ==============================================================================

	File: Main.cpp
	Author: Brendan Thompson
	Updated: 11/09/17

	Description: Driver for Infix to Postfix Converter

============================================================================== */

/* ==============================================================================
	File Includes
============================================================================== */

#include <iostream>	// Console IO

#include "ExpressionFixConverter.h"

using std::cin;
using std::cout;
using std::endl;
using std::string;

/* ==============================================================================
	Main Driver
============================================================================== */

int main(){
	ExpressionFixConverter mainExpressionConverter;

	string infixExpression;
	string postfixExpression[MAX_NUM_INPUT_VALUES];

	int numInputValues;

	// Convert
	infixExpression = "apple=1+(2/3)*5";
	mainExpressionConverter.infixToPostfix(infixExpression, postfixExpression, &numInputValues);
	cout << "Infix:\t\t" << infixExpression << endl;

	// Print
	cout << "Postfix:\t";
	for (int i = 0; i <= numInputValues; i++){
		cout << postfixExpression[i];
	}
	cout << endl;

	// Convert
	infixExpression = "banana=1^2";
	mainExpressionConverter.infixToPostfix(infixExpression, postfixExpression, &numInputValues);
	cout << "Infix:\t\t" << infixExpression << endl;

	// Print
	cout << "Postfix:\t";
	for (int i = 0; i <= numInputValues; i++){
		cout << postfixExpression[i];
	}
	cout << endl;

	return 0;
}