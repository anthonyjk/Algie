#ifndef SYNTAX_H
#define SYNTAX_H
#include <iostream>
#include <memory>

class AST {
	public:
		virtual void Display() { std::cout << "AST"; };
		virtual ~AST() = default;
};

class BinOp: public AST { // Binary Operation
	public:
		BinOp(std::unique_ptr<AST> left, Token op, std::unique_ptr<AST> right) : left(std::move(left)), op(op), right(std::move(right)) {}
		void Display() override { std::cout << "BinOp Obj"; }
	private:
		std::unique_ptr<AST> left;
		Token op;
		std::unique_ptr<AST> right;
};

class Num: public AST { // numeric
	public:
		Num(Token token) : token(token) {}
		void Display() override { std::cout << "Numeric Obj"; }
	private:
		Token token;
};

#endif // SYNTAX_H
