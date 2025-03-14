#include "Token.h"
#include "Lexer.h"

#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if(argc == 1) {
		std::cout << "No provided source code file." << std::endl;
		return 64; // Code 64 -> Command Line Input Error
	}

	Lexer myLexer(argv[1]); // pass path to source file to Lexer
	myLexer.Lex();
	myLexer.DisplayTokens();

	return 0;
}
