#ifndef TOKEN_H
#define TOKEN_H
#include <string>

enum TokenType {
	// Single Character
	LPAREN, RPAREN, LBRACKET, RBRACKET, LBRACE, RBRACE,
	PLUS, MINUS, STAR, SLASH, COMMA, NEWLINE,

	// Single/Two Character
	EQUAL, COMPARE, LESS, LESS_EQUAL, MORE, MORE_EQUAL,
	
	// Identifiers
	IDENTIFIER, STRING, NUMBER,

	// Multi-Character
	AND, OR,

	EOT // End of Tokens
};

class Token {
	public:
		Token(TokenType type, std::string value) : type(type), value(value) {}
		std::string getValue(){ return value; }
		TokenType getType(){ return type; }
	private:
		TokenType type;
		std::string value;
};

#endif // TOKEN_H
