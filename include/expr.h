#pragma once 

#include <string>
#include <memory>
#include "tokens.h"

namespace alox
{
	enum VALUE_TYPE
	{
		STRING_VALUE,
		NUMBER_VALUE,
		BOOLEAN_VALUE,
		NIL_VALUE
	};

	enum EXPR_TYPE
	{
		LITERAL,
		UNARY,
		BINARY,
		GROUPING
	};

	struct Expr_value
	{
		VALUE_TYPE type;
		std::string str;
		double num;
		bool boolean;
		int nil;
	};

	/*	struct Expr
		{
			Expr() { memset(this, 0, sizeof(Expr)); }
			Expr(Expr& lhs)
			{
				this->type = lhs.type;

				switch (type)
				{
				case UNARY:
					this->unary.right = lhs.unary.right;
					this->unary.op = lhs.unary.op;
					break;
				case BINARY:
					this->binary.right = lhs.binary.right;
					this->binary.left = lhs.binary.left;
					this->binary.op = lhs.binary.op;
					break;
				case GROUPING:
					this->grouping.expression = lhs.grouping.expression;
					break;
				case LITERAL:
					this->literal.value.type = lhs.literal.value.type;
					switch (lhs.literal.value.type)
					{
					case STRING_VALUE:
						this->literal.value.str = lhs.literal.value.str;
						break;
					case NUMBER_VALUE:
						this->literal.value.num = lhs.literal.value.num;
						break;
					case BOOLEAN_VALUE:
						this->literal.value.boolean = lhs.literal.value.boolean;
						break;
					case NIL_VALUE:
						this->literal.value.nil = lhs.literal.value.nil;
						break;

					default:
						break;
					}
				default:
					break;
				}
			}
			~Expr()
			{
				switch (type)
				{
				case UNARY:
					delete unary.right;
					break;
				case BINARY:
					delete binary.left;
					delete binary.right;
					break;
				case GROUPING:
					delete grouping.expression;
					break;
				case LITERAL:
				default:
					break;
				}
			}

			EXPR_TYPE type;
			union
			{
				struct
				{
					Expr_value value;
				}literal;
				struct
				{
					Expr* right;
					Token op;
				}unary;
				struct
				{
					Expr* right;
					Expr* left;
					Token op;
				}binary;
				struct
				{
					Expr* expression;
				}grouping;

			};
		};*/

	struct Expr
	{
		Expr() { memset(this, 0, sizeof(Expr)); }
		Expr(Expr& lhs)
		{
			this->type = lhs.type;
			this->value = lhs.value;
			this->right = lhs.right;
			this->left = lhs.left;
			this->op = lhs.op;
		}
		~Expr()
		{
			switch (type)
			{
			case UNARY:
				delete right;
				break;
			case BINARY:
				delete left;
				delete right;
				break;
			case GROUPING:
				delete right;
				break;
			case LITERAL:
			default:
				break;
			}
		}

		EXPR_TYPE type;
		Expr* right;
		Expr* left;
		Token op;
		Expr_value value;

	};
};





