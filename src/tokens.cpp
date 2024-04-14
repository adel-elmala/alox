#include "../include/tokens.h"

namespace alox
{
	Token& Token::operator=(Token& lhs)
	{
		this->str = std::string(lhs.str);
		this->line = lhs.line;
		this->type = lhs.type;
		return *this;
	}
}