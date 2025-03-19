#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum TokenType {
	// Single Character
	LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,
	PLUS, MINUS, STAR, SLASH, COMMA, NEWLINE, COLON,

	// Single/Two Character
	BANG, EQUAL, BANG_EQUAL, COMPARE, LESS, LESS_EQUAL, MORE, MORE_EQUAL,
	
	// Identifiers
	IDENTIFIER, STRING, NUMBER,

	// Multi-Character
	AND, OR, IF, WHILE, FOR, TRUE, FALSE,

	// Other
	UNKNOWN,

	EOT // End of Tokens
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
