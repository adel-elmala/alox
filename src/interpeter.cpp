#include "../include/interpeter.h"
#include "../include/expr.h"


namespace alox
{

	Interpeter::Interpeter()
	{
	}

	Interpeter::~Interpeter()
	{
	}
	Expr_value Interpeter::evalute(Expr* l)
	{
		switch (l->type)
		{

		case LITERAL:
			return evalLiteral(l);
		case UNARY:
			return evalUnary(l);
		case BINARY:
			return evalBinary(l);
		case GROUPING:
			return evalGrouping(l);
		}
	}
	Expr_value Interpeter::evalLiteral(Expr* l)
	{
		return l->value;
	}
	Expr_value Interpeter::evalUnary(Expr* u)
	{
		auto value = evalute(u->left);

		switch (u->op.type)
		{
		case MINUS:// TODO[adel]: add error checking 
			// if value is a number
			value.num = -(value.num);
			return value;
		case BANG:
			// TODO[adel]: support more than boolean (e.g !(10.2) -> !(true) -> false and also for string...)
			value.boolean = !(value.boolean);
			return value;
		}
	}
	Expr_value Interpeter::evalBinary(Expr* b)
	{
		auto leftValue = evalute(b->left);
		auto rightValue = evalute(b->right);
		auto answer = rightValue;

		switch (b->op.type)
		{
		case MINUS:
			answer.num = leftValue.num - (rightValue.num);
			return answer;
		case STAR:
			answer.num = leftValue.num * (rightValue.num);
			return answer;
		case SLASH:
			answer.num = leftValue.num / (rightValue.num); // check for 0 div ? IEEE results
			return answer;
		case PLUS:
			if (leftValue.type == STRING_VALUE && rightValue.type == STRING_VALUE)
				answer.str = leftValue.str + rightValue.str;

			else if (leftValue.type == NUMBER_VALUE && rightValue.type == NUMBER_VALUE)
				answer.num = leftValue.num + rightValue.num;
			return answer;
		}

	}
	Expr_value Interpeter::evalGrouping(Expr* g)
	{
		return evalute(g->left);
	}
}