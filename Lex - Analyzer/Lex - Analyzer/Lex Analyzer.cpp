#include "Lex Analyzer.h"

LexAnalyzer::LexAnalyzer(std::string codePath) {

	dataType["int"] = INT;
	dataType["else"] = ELSE;
	dataType["while"] = WHILE;
	dataType["char"] = CHAR;
	dataType["void"] = VOID;
	dataType["return"] = RETURN;
	dataType["cout"] = COUT;
	dataType["if"] = IF;
	dataType["cin"] = CIN;

	arStr[ADD] = "ADD";
	arStr[SUB] = "SUB";
	arStr[DIV] = "DIV";
	arStr[MUL] = "MUL";

	keyStr[IF] = "IF";
	keyStr[ELSE] = "ELSE";
	keyStr[WHILE] = "WHILE";
	keyStr[RETURN] = "RETURN";
	keyStr[COUT] = "COUT";
	keyStr[CIN] = "CIN";

	keyStr[INT] = "INT";
	keyStr[CHAR] = "CHAR";
	keyStr[VOID] = "VOID";

	roStr[NE] = "NE";
	roStr[LE] = "LE";
	roStr[LT] = "LT";
	roStr[GE] = "GE";
	roStr[GT] = "GT";
	roStr[E] = "E";
	roStr[AS] = "AS";



	try {
		codeFile.open(codePath, std::ios::in);
	} catch (const std::exception&) {
		cout << codePath << " File doesn't Exist" << endl;
	}
	lineCount = 1;
}

LexAnalyzer::~LexAnalyzer() {
	codeFile.close();
}

int LexAnalyzer::identifiers() {
		int state = 1;
		std::string dataTypes;
		do {
			switch (state) {
				case 1:
					if (isalpha(codeIndex)) {
						state = 2;
						dataTypes.push_back(codeIndex);
					} else {
						return 0;
					}
					break;
				case 2:
					if (isalnum(codeIndex)) {
						dataTypes.push_back(codeIndex);
						state = 2;
					} else {
							words = dataTypes;
						if (isDataType(dataTypes)) {
							return 2;
						} else {
							return 1;
						}
					}
					break;
				/*case 3:
					words = dataTypes;
					if (isDataType(dataTypes)) {
						return 2;
					} else {
						return 1;
					}
					break;*/
				default:
					break;
			}
		} while (codeFile.get(codeIndex));
}

bool LexAnalyzer::isDataType(string dataTypes) {
	if (dataType[dataTypes] != NULL)
		return true;
	return false;
}

RelationalOperator LexAnalyzer::isRO() {
	int state = 1;
	do {
		switch (state) {
			case 1:
				if (codeIndex == '<') {
					state = 2;
				} else if (codeIndex == '>') {
					state = 5;
				} else if (codeIndex == '=') {
					state = 8;
				} else {
					return NO;
				}
				break;

			case 2:
				if (codeIndex == '>') {
					state = 11;
					/*return NE;*/
				} else if (codeIndex == '=') {
					state = 3;/*
					return LE;*/
				} else {/*
					state = 4;*/
					return LT;
				}
				break;
			case 3:
				return LE;
				break;
			/*case 4:
				return LT;
				break;*/
			case 5:
				if (codeIndex == '=') {/*
					return GE;*/
					state = 6;
				} else {/*
					state = 7;*/
					return GT;
				}
				break;
			case 6:
				return GE;
				break;
			/*case 7:
				return GT;
				break;*/
			case 8:
				if (codeIndex == '=') {/*
					return E;*/
					state = 9;
				} else {
					return AS;/*
					state = 10;*/
				}
				break;
			case 9:
				return E;
				break;
			/*case 10:
				return AS;
				break;*/
			case 11:
				return NE;
				break;
			default:
				break;
		}
	} while (codeFile.get(codeIndex));
}

bool LexAnalyzer::removeWhiteSpace() {
	do {
		if (codeIndex == '\n')
			lineCount++;
		if (!isspace(codeIndex)) {
			return true;
		}
	} while (codeFile.get(codeIndex));
	return false;
}

bool LexAnalyzer::removeComments() {
	int state = 1;
	do {
		switch (state)
		{
			case 1:
				if (codeIndex == '/') {
					state = 2;
				} else {
					return true;
				}
				break;
			case 2:
				if (codeIndex == '*') {
					state = 3;
				} else if (codeIndex == '/') {
					state = 6;
				} else {
					codeFile.putback(codeIndex);      //Retaining Previous Values
					codeIndex = '/';
					return true;
				}
				break;
			case 3:
				if (codeIndex == '*') {
					state = 4;
				} else {
					state = 3;
				}
				break;
			case 4:
				if (codeIndex == '/') {/*
					return;*/
					state = 5;
				} else {
					state = 3;
				}
				break;
			case 5:
				return true;
				break;
			case 6:
				if (codeIndex == '\n') {
					return true;
				} else {
					state = 6;
				}
				break;
			/*case 7:
				if (codeIndex == '/') {
					state = 8;
				} else {
					state = 6;
				}
				break;
			case 8:
				return;
				break;*/
			default:
				break;
		}
	} while (codeFile.get(codeIndex));
	return false;
}

string LexAnalyzer::isIntegars() {
	int state = 1;
	string digit = "";
	do {
		switch (state) {
			case 1:
				if (isdigit(codeIndex)) {
					digit.push_back(codeIndex);
					state = 2;
				} else {
					return digit;
				}
				break;
			case 2:
				if (isdigit(codeIndex)) {
					digit.push_back(codeIndex);
					state = 2;
				}else
					return digit;
				break;
			/*case 3:
				return digit;
				break;*/
			default:
				break;
		}
	} while (codeFile.get(codeIndex));

	return "";
}

char LexAnalyzer::ConstLiteral() {
	int state = 1;
	char constLiteral;

	do {
		switch (state) {
			case 1:
				if (codeIndex == 39) {//Single Quote
					state = 2;
				} else {
					return NULL;
				}
				break;
			case 2:
				state = 3;
				constLiteral = codeIndex;
				break;
			case 3:
				if (codeIndex == 39) {/*
					return constLiteral;*/
					state = 4;
				} else {
					return -1;
				}
				break;
			case 4:
				return constLiteral;
				break;
			default:
				break;
		}
	} while (codeFile.get(codeIndex));
	return 0;
}

ArithmeticOperator LexAnalyzer::isArithtOperator() {
	int state = 1;
	ArithmeticOperator ARO = NAR;
	do {
		switch (state) {
			case 1:
				if (codeIndex == '+') {
					state = 2;
				} else if (codeIndex == '-') {
					state = 3;
				} else if (codeIndex == '*') {
					state = 4;
				} else if (codeIndex == '/') {
					state = 5;
				} else {
					return NAR;
				}
				break;
			case 2:
				return ADD;
				break;
			case 3:
				return SUB;
				break;
			case 4:
				return MUL;
				break;
			case 5:
				return DIV;
				break;
			/*case 6:
				return ARO;
				break;*/
			default:
				break;
		}
	} while (codeFile.get(codeIndex));
	return ARO;
}

char LexAnalyzer::punctuation() {
	int state = 1;
	char punc;
	do {
		switch (state)
		{
			case 1:
				if (codeIndex == '(') {
					state = 2;
					punc = codeIndex;
				}else if (codeIndex == ')') {
					state = 2;
					punc = codeIndex;
				}else if (codeIndex == '{') {
					state = 2;
					punc = codeIndex;
				}else if (codeIndex == '}') {
					state = 2;
					punc = codeIndex;
				}else if (codeIndex == '[') {
					state = 2;
					punc = codeIndex;
				}else if (codeIndex == ']') {
					state = 2;
					punc = codeIndex;
				} else if (codeIndex == ';') {
					state = 2;
					punc = codeIndex;
				}else if (codeIndex == ',') {
					state = 2;
					punc = codeIndex;
				} else {
					return 0;
				}
				break;
			case 2:
				return punc;
				break;
			/*case 3:
				return punc;
				break;*/
			default:
				break;
		}
	} while (codeFile.get(codeIndex));
	return 0;
}

void LexAnalyzer::writeToFile(string file,string tokenLex) {
	ofstream tableStream, tokenStream;
	try {
		tableStream.open(file);
		tokenStream.open(tokenLex);
	} catch (const std::exception&) {
		cout << "Error Opening output file" << endl;
	}

	for each (TokenLexeme var in pairs) {
		if (var.getToken() == "ID") {
			tableStream << var.getLexeme() << endl;
		}
		tokenStream << "(" << var.getToken() <<
				"," << var.getLexeme() << ")" << endl;
	}
	/*TokenLexeme iterate;
	for (size_t i = 0; i < pairs.size(); i++) {
		iterate = pairs[i];
		if (iterate.getToken() == "ID") {
			tableStream << iterate.getLexeme() << endl;
		}
		tokenStream << "(" << iterate.getToken() <<
				"," << iterate.getLexeme() << ")" << endl;
	}*/
}

void LexAnalyzer::classDriver(string table, string tokenLex) {
	TokenLexeme obj;
	char ch;
	//Pre-Input functions requirement
	codeFile.get(codeIndex);

	while (!codeFile.eof()) {

		//First Remove any whitespace or comments if any
		if (this->removeWhiteSpace()) {
			if (!this->removeComments()) {
				writeToFile(table, tokenLex);
				return;
			}
		} else {
			writeToFile(table, tokenLex);
			return;
		}

		//then check
	   // 0 -> Not Identifier, 1 -> Identifier , 2 -> Keyword
		int isKey = this->identifiers();
		if (isKey == 1) {
			pairs.push_back(obj.createToken("ID", words));          //writing to vector for token lexeme pair
			cout << "Identifier :: " << words << endl;
		} else if (isKey == 2) {
			pairs.push_back(obj.createToken(words, "^"));
			cout << "Keywords :: " << words << endl;
		} else {
			//punctuation, returns 0 if not Punctuation
			ch = this->punctuation();
			if (ch != 0) {
				cout << "Punctuation :: " << ch << endl;
				words = ch;
				pairs.push_back(obj.createToken(words, "^"));
			} else {
				//if not Punctuation then Is it RO?
				RelationalOperator ro = this->isRO();
				if (ro != NO) {
					if (ro == AS) {
						cout << "Assignment Operator :: " << ro << endl;
						pairs.push_back(obj.createToken("AS", "ET"));
					} else {
						cout << "Relational Operator :: " << (ro) << endl;
						pairs.push_back(obj.createToken("RO", roStr[ro]));
					}
				} else if (ro == NO) {
					//if not RO then Is it AO?
					ArithmeticOperator ao = this->isArithtOperator();
					if (ao != NAR) {
						cout << "Arithmetic Operator :: " << ao << endl;
						pairs.push_back(obj.createToken(arStr[ao], "^"));         //HERE ATTENTION
					} else if (ao == NAR) {
						//if not AO then Is it Integers?
						string integ = this->isIntegars();
						if (!integ.empty()) {
							pairs.push_back(obj.createToken("NUMCNST", integ));                //HERE ATTENTION
							cout << "Integer :: " << integ << endl;
						} else {
							//Constant Literals
							char cha = this->ConstLiteral();
							if (cha == 0) {
								cout << "Error at line :: " << lineCount << endl;
								return;
							} else if (cha == -1) {
								cout << "Error at line :: " << lineCount << endl;
								return;
							} else {
								string of;
								of.push_back(cha);
								pairs.push_back(obj.createToken("LITCNST", of));           //HERE ATTENTION
								cout << "Constant Literals :: " << cha << endl;
								return;
							}
						}
					}
				}
			}
		}

		//	//remove whitespace
		//	this->removeWhiteSpace();
		//	this->removeComments();

		//	//punctuation
		//	ch = this->punctuation();
		//	if (ch != 0) {
		//		cout << "Punctuation :: " << ch << endl;
		//		words = ch;
		//		pairs.push_back(obj.createToken(words,""));
		//	}

		//	//remove whitespace
		//	this->removeWhiteSpace();
		//	this->removeComments();

		//	//Relational Operator
		//	RelationalOperator ro = this->isRO();
		//	if (ro != NO) {
		//		cout << "Relational Operator :: " << (ro) << endl;
		//		pairs.push_back(obj.createToken("RO",roStr[ro]));
		//	}

		//	//remove whitespace
		//	this->removeWhiteSpace();
		//	this->removeComments();

		//	//Arithmetic Operator
		//	ArithmeticOperator ao =  this->isArithtOperator();
		//	if (ao != NAR) {
		//		cout << "Arithmetic Operator :: " << ao << endl;
		//		pairs.push_back(obj.createToken("RO",arStr[ao]));
		//	}

		//	//remove whitespace
		//	this->removeWhiteSpace();
		//	this->removeComments();

		//	//Integers
		//	string integ = this->isIntegars();
		//	if (!integ.empty()) {
		//		cout << "Integer :: " << integ << endl;
		//	}
		//	//remove whitespace
		//	this->removeWhiteSpace();
		//	this->removeComments();

		//	//Constant Literals
		//	char cha = this->ConstLiteral();
		//	if (cha != 0)
		//		cout << "Constant Literals :: " << cha << endl;
		//	else if (cha == -1)
		//		cout << "Error at line :: " << lineCount << endl;
		//}
		//cout << "hello :: "<<lineCount<<endl;
	}
	writeToFile(table, tokenLex);
}






