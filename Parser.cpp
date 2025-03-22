#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Syntax.h"

void Parser::Parse(Program & program) {
	int temp = 0;
	while(pointer < static_cast<int>(tokens.size()) && temp < 25) {
		std::cout << tokens.at(pointer).getType() << std::endl;
		switch(tokens.at(pointer).getType()) {
			case NUMBER:
				program.Append(Expr());
				break;
			case IDENTIFIER:
				program.Append(Expr());	
				break;
			case EOT:
				pointer = tokens.size(); // just end program
				break;
		}

		++temp;
	}
}

void Parser::Eat(TokenType tt) {
	if(tokens.at(pointer).getType() == tt) {
		++pointer;
	} else {
		throw std::invalid_argument("Incorrect TokenType");
	}
}

// Expressions
std::unique_ptr<AST> Parser::Call() {
	Token id = tokens.at(pointer);
	Eat(IDENTIFIER);
	std::unique_ptr<Parameters> p = std::make_unique<Parameters>();
	while(tokens.at(pointer).getType() == LPAREN) {
		Eat(LPAREN);
		while(tokens.at(pointer).getType() != RPAREN && tokens.at(pointer).getType() != EOT) {
			if(tokens.at(pointer).getType() == COMMA) {
				Eat(COMMA);
			} else {
				p->Append(Expr()); // risky but can fix later
			}
		}
		Eat(RPAREN);
	}

	return std::unique_ptr<AST>(new FuncCall(id, std::move(p)));

}
std::unique_ptr<AST> Parser::Factor() {
	Token token = tokens.at(pointer);
	
	switch(token.getType()) {
		case NUMBER:
			Eat(NUMBER);
			return std::unique_ptr<AST>(new Numeric(token));
			break;
		case IDENTIFIER:
			if(tokens.at(pointer+1).getType() == LPAREN) {
				return Call();
			} else {
				Eat(IDENTIFIER);
				return std::unique_ptr<AST>(new Identifier(token));
			}
			break;
		case STRING:
			Eat(STRING);
			return std::unique_ptr<AST>(new String(token));
			break;
		case LPAREN:
			Eat(LPAREN);
			auto node = Expr(); // returns ptr to BinOp node
			Eat(RPAREN);
			return node;
			break;
	}

	return std::unique_ptr<AST>(new Identifier(token)); // temporary
}

std::unique_ptr<AST> Parser::Term() {
	auto node = Factor();
	
	// Math * and /
	while(tokens.at(pointer).getType() == STAR || tokens.at(pointer).getType() == SLASH) {
		Token token = tokens.at(pointer);
		
		if(token.getType() == STAR) { //multiply
			Eat(STAR);
		} else if (token.getType() == SLASH) { //divide
			Eat(SLASH);
		}

		node = std::unique_ptr<AST>(new BinOp(std::move(node), token, Factor()));
	}

	// Comparison Operators
	while(tokens.at(pointer).getType() == COMPARE || tokens.at(pointer).getType() == BANG_EQUAL || tokens.at(pointer).getType() == LESS || tokens.at(pointer).getType() == LESS_EQUAL || tokens.at(pointer).getType() == MORE || tokens.at(pointer).getType() == MORE_EQUAL) {
		Token token = tokens.at(pointer);
		
		switch(token.getType()) {
			case COMPARE:
				Eat(COMPARE);
				break;
			case BANG_EQUAL:
				Eat(BANG_EQUAL);
				break;
			case LESS:
				Eat(LESS);
				break;
			case LESS_EQUAL:
				Eat(LESS_EQUAL);
				break;
			case MORE:
				Eat(MORE);
				break;
			case MORE_EQUAL:
				Eat(MORE_EQUAL);
				break;
		}

		node = std::unique_ptr<AST>(new CompOp(std::move(node), token, Factor()));
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

	while(tokens.at(pointer).getType() == EQUAL) {
		Token token = tokens.at(pointer);
		
		if(token.getType() == EQUAL) { // +
			Eat(EQUAL);
		}

		node = std::unique_ptr<AST>(new VarAssign(std::move(node), token, Term()));
	}

	return node;
}

// Variables
