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
		void Parse(Program&);
		void Eat(TokenType);
		std::unique_ptr<AST> Block();
		std::unique_ptr<AST> Call();
		std::unique_ptr<AST> Factor();
		std::unique_ptr<AST> Term();
		std::unique_ptr<AST> Expr();
	private:
		std::vector<Token> tokens;
		int pointer{0};
};

#endif // PARSER_H
