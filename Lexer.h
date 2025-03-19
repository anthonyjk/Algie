#ifndef LEXER_H
#define LEXER_H
#include <string>
#include <vector>
#include <fstream>

class Lexer {
	public:
		Lexer(std::string path) : path(path) {}		
		std::vector<Token> Lex();
		void ScanLine(std::string);
		Token NextToken(std::string);
		std::string CollectIdentifier(std::string line, bool fix_pointer = false);
		std::string CollectString(std::string line);
		std::string CollectNumeric(std::string line);
		void DisplayTokens();
		std::vector<Token> getTokens() { return tokens; }
	private:
		std::string path;
		std::vector<Token> tokens;
		int pointer{0};
};

#endif // LEXER_H
