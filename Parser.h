#ifndef PARSER_H
#define PARSER_H
#include <vector>
#include <iostream>

class Parser {
	public:
		Parser(std::vector<Token> tk_vec) : tokens(tk_vec) {}
		void Parse();
	private:
		std::vector<Token> tokens;

};

#endif // PARSER_H
