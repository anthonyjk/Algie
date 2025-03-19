#ifndef PARSER_H
#define PARSER_H
#include "Syntax.h"
#include <vector>
#include <iostream>
#include <memory>
#include <stdexcept>

class Parser {
	public:
		Parser(std::vector<Token> tk_vec) : tokens(tk_vec) {}
		std::unique_ptr<AST> Parse();
		void Eat(TokenType);
		std::unique_ptr<AST> Factor();
		std::unique_ptr<AST> Term();
		std::unique_ptr<AST> Expr();
	private:
		std::vector<Token> tokens;
		int pointer{0};
};

#endif // PARSER_H
