#pragma once 

#include <vector>

#include "tokens.h"
#include "expr.h"

namespace alox
{

	class Parser
	{
	public:
		Parser();
		~Parser();
		void addTkns(std::vector<Token> tokens);
		Expr* parse();
		Expr* expression();
		Expr* equality();
		Expr* comparison();
		Expr* term();
		Expr* factor();
		Expr* unary();
		Expr* primary();
	private:
		std::vector<Token> _tkns;
		unsigned int _current;
		bool match(std::vector<TokenType> ifany);
		Token previous();
		Token peek();
		bool isAtEnd();
		bool consume(TokenType tknType, std::string errMsg);
		void sync();
	};

}