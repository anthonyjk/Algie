#include "Token.h"
#include "Lexer.h"
#include <string>
#include <iostream>

void Lexer::Lex() {
	std::ifstream File(path);

	std::string line;
	while(getline(File, line)) {
		ScanLine(line);
	}

	File.close();
}


// Adds to token vector
void Lexer::ScanLine(std::string line) {
	pointer = 0;

	while(pointer < static_cast<int>(line.size())) {
		tokens.push_back(NextToken(line));
	}
}

Token Lexer::NextToken(std::string line) {
	while(pointer < static_cast<int>(line.size())) {	
		//std::cout << line.at(pointer) << std::endl;
		if(isdigit(line.at(pointer))) {
			return Token(NUMBER, CollectNumeric(line));
		}

		switch(line.at(pointer)) {
			case '(':
				++pointer;
				return Token(LPAREN, "(");
				break;
			case ')':
				++pointer;
				return Token(RPAREN, ")");
				break;
			case '=':
				// do a check at some point to see if its
				// 	= or ==

				++pointer;
				return Token(EQUAL, "=");
			case '"':
				++pointer;
				// collect after ptr advance
				return Token(STRING, CollectString(line));
				break;
			case '\n':
				++pointer;
				return Token(NEWLINE, "\n");
				break;
			case ' ':
				++pointer;
				break;
			default:
				std::string symbol = CollectIdentifier(line); // collect before ptr advance

				++pointer;
				return Token(IDENTIFIER, symbol);
				break;
		}
	}

	++pointer;

	return Token(EOT, "EOT"); // TEMPORARY!!!
}

std::string Lexer::CollectIdentifier(std::string line) {
	line = line.substr(pointer, line.size());
	std::string symbol;

	for(char c : line) {
		if(c == ' ' || c == '\n' || isalnum(c) == false) {
			break;
		}

		symbol += c;
	}

	pointer += symbol.size() - 1;

	return symbol;
}

std::string Lexer::CollectString(std::string line) {
	line = line.substr(pointer, line.size());

	if(line.find('\"') == std::string::npos) {
		std::cout << "STRING ERROR!" << std::endl; // make error later
	}

	std::string str;

	for(char c : line) {
		if(c == '\"') {
			break;
		}

		str += c;
	}
	
	pointer += str.size() + 1;

	return str;

}

std::string Lexer::CollectNumeric(std::string line) {
	line = line.substr(pointer, line.size());

	std::string num;

	for(char c : line) {
		if(isdigit(c) == false && c != '.') {
			break;
		}

		num += c;
	}

	pointer += num.size();
	
	return num;
}

void Lexer::DisplayTokens() {
	for(Token t : tokens) {
		std::cout << t.getType() << " | " << t.getValue() << std::endl;
	}
}
