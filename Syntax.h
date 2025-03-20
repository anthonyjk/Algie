#ifndef SYNTAX_H
#define SYNTAX_H
#include <iostream>
#include <memory>
#include <vector>

class AST {
	public:
		virtual void Display() { std::cout << "AST"; };
		virtual ~AST() = default;
};

// Root
class Program: public AST {
	public:
		Program() {}
		void Append(std::unique_ptr<AST> node) {
			tree.push_back(std::move(node));
		}
		void Display() override {
			for(const auto& node : tree) {
				node->Display();
			}
		}
		~Program() = default;
	private:
		std::vector<std::unique_ptr<AST>> tree;
};

// Operators
class BinOp: public AST { // Binary Operation
	public:
		BinOp(std::unique_ptr<AST> left, Token op, std::unique_ptr<AST> right) : left(std::move(left)), op(op), right(std::move(right)) {}
		void Display() override {
			std::cout << "BinOp Called" << std::endl;
			left->Display();

			std::cout << op.getValue() << std::endl;

			right->Display(); 
		}
	private:
		std::unique_ptr<AST> left;
		Token op;
		std::unique_ptr<AST> right;
};

class CompOp: public AST { // Binary Operation
	public:
		CompOp(std::unique_ptr<AST> left, Token op, std::unique_ptr<AST> right) : left(std::move(left)), op(op), right(std::move(right)) {}
		void Display() override {
			std::cout << "CompOp Called" << std::endl;
			left->Display();

			std::cout << op.getValue() << std::endl;

			right->Display(); 
		}
	private:
		std::unique_ptr<AST> left;
		Token op;
		std::unique_ptr<AST> right;
};


// Literals
class Numeric: public AST { // numeric
	public:
		Numeric(Token token) : token(token) {}
		void Display() override { std::cout << token.getValue() << std::endl; }
	private:
		Token token;
};

class String: public AST {
	public:
		String(Token token) : token(token) {}
		void Display() override { std::cout << token.getValue() << std::endl; }
	private:
		Token token;
};

class Boolean: public AST {
	public:
		Boolean(Token token) : token(token) {}
		void Display() override { std::cout << token.getValue() << std::endl; }
	private:
		Token token;
};

// Variables
class Identifier: public AST {
	public:
		Identifier(Token token) : token(token) {}
		void Display() override { std::cout << token.getValue() << std::endl; }
	private:
		Token token;
};

class VarAssign: public AST {
	public:
		VarAssign(std::unique_ptr<AST> left, Token op, std::unique_ptr<AST> right) : left(std::move(left)), op(op), right(std::move(right)) {}
		void Display() override {
			std::cout << "VarAssign Called" << std::endl;
			left->Display();

			std::cout << op.getValue() << std::endl;

			right->Display(); 
		}
	private:
		std::unique_ptr<AST> left;
		Token op; // will be an = operator
		std::unique_ptr<AST> right;
};

#endif // SYNTAX_H
