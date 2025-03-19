#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Syntax.h"

/*
 *	Quick example of smart pointers with AST Objects
 *
 *	BinOp op;
 *	std::unique_ptr = std::make_unique<BinOp>();
 *	*ptr = op;
 *	return ptr;
 *
 *	for return types of std::unique_ptr<AST>
 */

std::unique_ptr<AST> Parser::Parse() {
	//for(const Token & t : tokens) {
	//	std::cout << t << std::endl; 
	//}
	//
	return Expr();
}

void Parser::Eat(TokenType tt) {
	if(tokens.at(pointer).getType() == tt) {
		++pointer;
	} else {
		throw std::invalid_argument("Incorrect TokenType");
	}
}

std::unique_ptr<AST> Parser::Factor() {
	Token token = tokens.at(pointer);
	if(token.getType() == NUMBER) {
		Eat(NUMBER);
		return std::unique_ptr<AST>(new Num(token));
	} else if (token.getType() == LPAREN) {
		Eat(LPAREN);
		auto node = Expr(); // returns ptr to BinOp node
		Eat(RPAREN);
		return node;
	} else {
		return std::unique_ptr<AST>(new Num(token)); // temp
	}
}

std::unique_ptr<AST> Parser::Term() {
	auto node = Factor();

	while(tokens.at(pointer).getType() == STAR || tokens.at(pointer).getType() == SLASH ) {
		Token token = tokens.at(pointer);
		
		if(token.getType() == STAR) { //multiply
			Eat(STAR);
		} else if (token.getType() == SLASH) { //divide
			Eat(SLASH);
		}

		node = std::unique_ptr<AST>(new BinOp(std::move(node), token, Factor()));
	}

	return node;
}

std::unique_ptr<AST> Parser::Expr() {
	auto node = Term();

	while(tokens.at(pointer).getType() == PLUS || tokens.at(pointer).getType() == MINUS ) {
		Token token = tokens.at(pointer);
		
		if(token.getType() == PLUS) { // +
			Eat(PLUS);
		} else if (token.getType() == MINUS) { // -
			Eat(MINUS);
		}

		node = std::unique_ptr<AST>(new BinOp(std::move(node), token, Term()));
	}

	return node;

}

