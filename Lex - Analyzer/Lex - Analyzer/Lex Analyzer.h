#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include <hash_map>
#include "RelationalOperator.h"
#include "Keyword.h"
#include "ArithmeticOperators.h"
#include "TokenLexem.h"
#include <vector>

using namespace std;

class LexAnalyzer {
private:
	int keyCount = 9;
	hash_map<string, Keyword> dataType;
	hash_map<int, string>keyStr;
	hash_map<int, string>arStr;
	hash_map<int, string>roStr;
	vector<TokenLexeme> pairs;

	int lineCount;

	ifstream codeFile;
	string words;
	char codeIndex;

public:
	LexAnalyzer() {}
	LexAnalyzer(std::string codePath);
	~LexAnalyzer();

	//Class Functions
	string enumToString(int index,int choice) {
		switch (choice) {
			case 1:
				return keyStr[index];
				break;
			case 2:
				return arStr[index];
				break;
			case 3:
				return roStr[index];
				break;
			default:
				break;
		}
	}

	// 0 -> Not Identifier, 1 -> Identifier , 2 -> Keyword
	int identifiers();
	bool isDataType(string);

	// Is Relational Operator
	RelationalOperator isRO();

	//White Space remove
	bool removeWhiteSpace();

	//Remove Blocking and Line Comments
	bool removeComments();

	// Constant integers
	string isIntegars();

	//Constant Literals - Return that character, in case no Literal NULL and error case -1
	char ConstLiteral();

	//Arithmetic Operators
	ArithmeticOperator isArithtOperator();

	//Punctuation
	char punctuation();

	//write to File for Token lexeme pair form
	void writeToFile(string file,string tokenLex);
	//Driver
	void classDriver(string, string);
};

