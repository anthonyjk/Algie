#ifndef TOKEN_H
#define TOKEN_H
#include <string>
#include <iostream>

enum TokenType {
	// Single Character
	LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE, // 0-5
	PLUS, MINUS, STAR, SLASH, COMMA, NEWLINE, COLON, // 6-12

	// Single/Two Character
	BANG, EQUAL, BANG_EQUAL, COMPARE, LESS, LESS_EQUAL, MORE, MORE_EQUAL, // 13-20
	
	// Identifiers
	IDENTIFIER, STRING, NUMBER, // 21-23

	// Multi-Character
	AND, OR, IF, WHILE, FOR, TRUE, FALSE, // 24-30

	// Other
	UNKNOWN, //31

	EOT // End of Tokens: 32
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
