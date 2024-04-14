#include <iostream>
#include "../include/parser.h"
namespace alox
{

	Parser::Parser() : _current(0)
	{
	}
	void Parser::addTkns(std::vector<Token> tokens)
	{
		_tkns = tokens;
	}

	Parser::~Parser()
	{
	}
	Expr* Parser::parse()
	{
		return expression();
	}
	Expr* Parser::expression()
	{
		return equality();
	}
	Expr* Parser::equality()
	{
		Expr* lhs = comparison();
		Expr* ee = lhs;
		while (match({ BANG_EQUAL,EQUAL_EQUAL }))
		{
			Token op = previous();
			Expr* rhs = comparison();
			Expr* nee = new Expr();
			nee->left = ee;
			nee->op = op;
			nee->right = rhs;
			nee->type = BINARY;
			ee = nee;
		}
		return ee;
	}

	Expr* Parser::comparison()
	{
		Expr* lhs = term();
		Expr* ce = lhs;
		while (match({ GREATER, GREATER_EQUAL, LESS, LESS_EQUAL }))
		{
			Token op = previous();
			Expr* rhs = term();
			Expr* nce = new Expr();
			nce->left = ce;
			nce->op = op;
			nce->right = rhs;
			nce->type = BINARY;
			ce = nce;
		}
		return ce;
	}

	Expr* Parser::term()
	{
		Expr* lhs = factor();
		Expr* te = lhs;
		while (match({ MINUS,PLUS }))
		{
			Token op = previous();
			Expr* rhs = factor();
			auto nte = new Expr();
			nte->left = te;
			nte->op = op;
			nte->right = rhs;
			nte->type = BINARY;
			te = nte;
		}
		return te;
	}
	Expr* Parser::factor()
	{
		Expr* lhs = unary();
		Expr* fe = lhs;
		while (match({ SLASH,STAR }))
		{
			Token op = previous();
			Expr* rhs = unary();
			auto nfe = new Expr();
			nfe->left = fe;
			nfe->op = op;
			nfe->right = rhs;
			nfe->type = BINARY;
			fe = nfe;
		}
		return fe;
	}
	Expr* Parser::unary()
	{
		Expr* ue;
		if (match({ BANG,MINUS }))
		{
			Token op = previous();
			Expr* e = unary();
			ue = new Expr();
			ue->type = UNARY;
			ue->op = op;
			ue->left = e;
			return ue;
		}
		return primary();
	}
	Expr* Parser::primary()
	{
		Expr* e = new Expr;

		e->type = LITERAL;
		if (match({ FALSE }))
		{
			e->value.type = BOOLEAN_VALUE;
			e->value.boolean = false;
		}
		else if (match({ TRUE }))
		{
			e->value.type = BOOLEAN_VALUE;
			e->value.boolean = true;
		}
		else if (match({ NIL }))
		{
			e->value.type = NIL_VALUE;
			e->value.nil = NULL;
		}
		else if (match({ NUMBER }))
		{
			e->value.type = NUMBER_VALUE;
			e->value.num = ::atof(previous().str.c_str());
		}
		else if (match({ STRING }))
		{
			e->value.type = STRING_VALUE;
			e->value.str = previous().str;
		}
		else if (match({ LEFT_PAREN }))
		{
			Expr* e0 = expression();
			consume(RIGHT_PAREN, "Expect ')' after expression.");
			e->type = GROUPING;
			e->left = e0;
		}

		return e;
	}
	bool Parser::match(std::vector<TokenType> ifany)
	{
		for (auto t : ifany)
		{
			if (_tkns[_current].type == t)
			{
				_current++;
				return true;
			}
		}
		return false;
	}
	bool Parser::consume(alox::TokenType tknType, std::string errMsg)
	{
		if (_tkns[_current].type == tknType)
		{
			_current++;
			return true;
		}
		std::cerr << errMsg << std::endl;
		return false;
	}
	Token Parser::previous()
	{
		return _tkns[_current - 1];
	}
	Token Parser::peek()
	{
		return _tkns[_current];
	}
	bool Parser::isAtEnd()
	{
		return _tkns[_current].type == _EOF;
	}
	void Parser::sync()
	{
		_current++;
		while (!isAtEnd())
		{
			if (previous().type == SEMICOLON) // at the end of a satetment
				return;
			// at the begining of a statement
			switch (peek().type)
			{
			case AND:
			case CLASS:
			case ELSE:
			case FALSE:
			case FUN:
			case FOR:
			case IF:
			case NIL:
			case OR:
			case PRINT:
			case RETURN:
			case SUPER:
			case THIS:
			case TRUE:
			case VAR:
			case WHILE:
				return;
			}
			// eat the next token
			_current++;

		}
	}

}