#pragma once
#include <string>

using namespace std;

class TokenLexeme {
public:
	TokenLexeme();
	TokenLexeme(string tok, string lex);
	~TokenLexeme();
	TokenLexeme createToken(string tok,string lex);
	string getToken() { return token; }
	string getLexeme() { return lexeme; }

private:
	string token;
	string lexeme;
};

