#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Syntax.h"
#include <string>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[]) {
	if(argc == 1) {
		std::cout << "No provided source code file." << std::endl;
		return 64; // Code 64 -> Command Line Input Error
	}

	Lexer myLexer(argv[1]); // pass path to source file to Lexer
	Parser myParser(myLexer.Lex());
	Program myProgram;
	myParser.Parse(myProgram);
	
	myLexer.DisplayTokens();
	myProgram.Display();
	
	return 0;
}
