#include "Token.h"
#include "Lexer.h"
#include "Parser.h"

void Parser::Parse() {
	for(const Token & t : tokens) {
		std::cout << t << std::endl; 
	}
}
