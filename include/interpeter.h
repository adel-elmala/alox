#pragma once 

namespace alox
{

	struct Expr_value;
	struct Expr;

	class Interpeter
	{
	public:
		Interpeter();
		~Interpeter();

		Expr_value evalute(Expr* e);
	private:
		Expr_value evalLiteral(Expr* l);
		Expr_value evalUnary(Expr* u);
		Expr_value evalBinary(Expr* b);
		Expr_value evalGrouping(Expr* g);
	};
}