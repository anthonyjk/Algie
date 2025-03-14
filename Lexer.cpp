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
	
	int counter = 0;
	while(pointer < static_cast<int>(line.size()) && counter < 20) {
		tokens.push_back(NextToken(line));
		++counter;
	}
}

Token Lexer::NextToken(std::string line) {
	while(pointer < static_cast<int>(line.size())) {	
		std::cout << line.at(pointer) << std::endl;
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
			case '[':
				++pointer;
				return Token(LBRACKET, "[");
				break;
			case ']':
				++pointer;
				return Token(RBRACKET, "]");
				break;
			case '{':
				++pointer;
				return Token(LBRACE, "{");
				break;
			case '}':
				++pointer;
				return Token(RBRACE, "}");
				break;
			case '+':
				++pointer;
				return Token(PLUS, "+");
				break;
			case '*':
				++pointer;
				return Token(STAR, "*");
				break;
			case '/':
				++pointer;
				return Token(SLASH, "/");
				break;
			case ',':
				++pointer;
				return Token(COMMA, ",");
				break;
			case '-':
				++pointer;
				return Token(MINUS, "-");
				break;
			case '=':
				if(pointer+1 < static_cast<int>(line.size()) && line.at(pointer+1) == '=') {
					pointer += 2;
					return Token(COMPARE, "==");
				}

				++pointer;
				return Token(EQUAL, "=");
				break;
			case '<':
				if(pointer+1 < static_cast<int>(line.size()) && line.at(pointer+1) == '=') {
					pointer += 2;
					return Token(LESS_EQUAL, "<=");
				}

				++pointer;
				return Token(LESS, "<");
				break;
			case '>':
				if(pointer+1 < static_cast<int>(line.size()) && line.at(pointer+1) == '=') {
					pointer += 2;
					return Token(MORE_EQUAL, ">=");
				}

				++pointer;
				return Token(MORE, ">");
				break;
			case '\"':
				++pointer;
				return Token(STRING, CollectString(line));
				break;
			case ':':
				++pointer;
				return Token(COLON, ":");
				break;
			case '\n':
				++pointer;
				return Token(NEWLINE, "\n");
				break;
			case '\t':
				++pointer;
				break;
			case ' ':
				++pointer;
				break;
			default:
				std::cout << "default " << std::endl;
				if(isalpha(line.at(pointer)) || line.at(pointer) == '_') {
					std::string symbol = CollectIdentifier(line);
					
					++pointer;
					if(symbol == "and") {
						return Token(AND, symbol);
					} else if(symbol == "if") {
						return Token(IF, symbol);
					} else if(symbol == "while") {
						return Token(WHILE, symbol);
					} else if(symbol == "or") {
						return Token(OR, symbol);
					} else if(symbol == "for") {
						return Token(FOR, symbol);
					} else if(symbol == "true") {
						return Token(TRUE, symbol);
					} else if(symbol == "false") {
						return Token(FALSE, symbol);
					} else {
						return Token(IDENTIFIER, symbol);
					}
				} else {
					std::string unk(1, line.at(pointer));
					++pointer;
					return Token(UNKNOWN, unk);
				}
				break;
		}
	}

	++pointer;

	return Token(EOT, "EOT"); // TEMPORARY!!!
}

std::string Lexer::CollectIdentifier(std::string line, bool fix_pointer) {
	line = line.substr(pointer, line.size());
	std::string symbol;

	for(char c : line) {
		if(c == ' ' || c == '\n' || (isalnum(c) == false && c != '_')) {
			break;
		}

		symbol += c;
	}
	
	if(!fix_pointer) { // if not fixing pointer in position
		pointer += symbol.size() - 1;
	}

	return symbol;
}

std::string Lexer::CollectString(std::string line) {
	line = line.substr(pointer, line.size());

	std::cout << line << std::endl;

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
