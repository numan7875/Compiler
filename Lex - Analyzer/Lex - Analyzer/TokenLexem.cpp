#include "TokenLexem.h"

TokenLexeme::TokenLexeme() {
	token = "";
	lexeme = "";
}

TokenLexeme::TokenLexeme(string tok, string lex):token(tok),lexeme(lex) {}

TokenLexeme::~TokenLexeme() {}

TokenLexeme TokenLexeme::createToken(string tok,string lex) {
	return TokenLexeme(tok,lex);
}
