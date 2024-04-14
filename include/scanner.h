#pragma once
#include <string>
#include <vector>
#include <map>

#include "tokens.h"

namespace alox
{


	class Scanner
	{
	public:
		Scanner();
		~Scanner();
		void addSource(std::string source);
		std::vector<Token> scanTokens();

	private:
		void _scanTokens();
		void _consumeTkn();
		void _addTkn(TokenType tknT);
		bool _match(std::string lhs);
		std::string _peek(int nChars);
		void _scanString();
		void _scanNumber();
		void _scanIdentifier();
		bool isDigit(char c);
		bool isAlpha(char c);
		bool isAlphaNumeric(char c);

		__forceinline bool isEnd() { return _current > (_source.length()); }

		std::string _source;
		std::vector<Token> _tkns;
		std::map<std::string, TokenType> _keywords_map;
		int _atLine;
		// offsets into the source
		int _start;
		int _current;
	};
}