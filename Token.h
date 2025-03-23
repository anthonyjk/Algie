#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum TokenType {
	// Single Character
	LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE, // 0-5
	PLUS, MINUS, STAR, SLASH, COMMA, NEWLINE, COLON, SEMICOLON, // 6-13

	// Single/Two Character
	BANG, EQUAL, BANG_EQUAL, COMPARE, LESS, LESS_EQUAL, MORE, MORE_EQUAL, // 14-21
	
	// Identifiers
	IDENTIFIER, STRING, NUMBER, // 22-24

	// Multi-Character
	AND, OR, IF, WHILE, FOR, TRUE, FALSE, IN, // 25-32

	// Other
	UNKNOWN, //33

	EOT // End of Tokens: 34
};

class Token {
	public:
		Token(TokenType type, std::string value) : type(type), value(value) {}
		std::string getValue() const { return value; }
		TokenType getType() const { return type; }
		friend std::ostream & operator<<(std::ostream & os, const Token & token) {
			os << token.getType() << " | " << token.getValue();
			return os;
		}
	private:
		TokenType type;
		std::string value;
};

#endif // TOKEN_H
