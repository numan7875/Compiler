#include "Lex Analyzer.h"

using namespace std;

int main() {
	string codepath = "test.txt";
	string keyPath = "table.txt";
	string wordPath = "words.txt";
	LexAnalyzer lex(codepath);
	lex.classDriver(keyPath,wordPath);
	return 0;
}