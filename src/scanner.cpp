#include "../include/scanner.h"
#include "../include/alox.h"
namespace alox
{

	Scanner::Scanner() : _atLine(1), _start(0), _current(0)
	{
		_keywords_map = {
		{ "and", AND},
		{ "class", CLASS },
		{ "else", ELSE },
		{ "false", FALSE },
		{ "for", FOR },
		{ "fun", FUN },
		{ "if", IF },
		{ "nil", NIL },
		{ "or", OR },
		{ "print", PRINT },
		{ "return", RETURN },
		{ "super", SUPER },
		{ "this", THIS },
		{ "true", TRUE },
		{ "var", VAR },
		{ "while", WHILE }
		};
	}

	Scanner::~Scanner()
	{
	}
	void Scanner::addSource(std::string source)
	{
		_source = source;
	}
	std::vector<Token> Scanner::scanTokens()
	{
		_scanTokens();
		return _tkns;
	}

	void Scanner::_scanTokens()
	{
		while (!isEnd())
		{
			_start = _current;
			_consumeTkn();
		}
		_tkns.push_back(Token{ _EOF,"",_atLine });
	}

	void Scanner::_addTkn(TokenType tknT)
	{
		_tkns.push_back(Token{ tknT,_source.substr(_start,_current - _start),_atLine });
	}

	void Scanner::_consumeTkn()
	{
		char cursor = _source[_current++]; // advance cursor
		switch (cursor)
		{
		case '(': _addTkn(LEFT_PAREN); break;
		case ')': _addTkn(RIGHT_PAREN); break;
		case '{': _addTkn(LEFT_BRACE); break;
		case '}': _addTkn(RIGHT_BRACE); break;
		case ',': _addTkn(COMMA); break;
		case '.': _addTkn(DOT); break;
		case '-': _addTkn(MINUS); break;
		case '+': _addTkn(PLUS); break;
		case ';': _addTkn(SEMICOLON); break;
		case '*': _addTkn(STAR); break;
		case '!':
			_addTkn(_match("=") ? BANG_EQUAL : BANG);
			break;
		case '=':
			_addTkn(_match("=") ? EQUAL_EQUAL : EQUAL);
			break;
		case '<':
			_addTkn(_match("=") ? LESS_EQUAL : LESS);
			break;
		case '>':
			_addTkn(_match("=") ? GREATER_EQUAL : GREATER);
			break;
		case '/':
		{
			if (_match("/"))
			{
				while (_peek(1) != "\n" && !isEnd()) _current++;
			}
			else
				_addTkn(SLASH);
		}break;
		// Ignore whitespace.
		case ' ':
		case '\r':
		case '\t':
			break;

		case '\n':
			_atLine++;
			break;
		case'"':
			_scanString();
			break;
		case 0:break; //EOF
		default:
			if (isDigit(cursor))
				_scanNumber();
			else if (isAlpha(cursor))
				_scanIdentifier();
			else
				alox::_error(_atLine, "Unexpected character.");
			break;
		}
	}

	// advance only if the next string matches lhs, updating _current cursor
	bool Scanner::_match(std::string lhs)
	{
		if (isEnd()) return false;
		if (lhs != _source.substr(_current, lhs.length())) return false;
		_current++;
		return true;
	}

	// cursors stand still
	std::string Scanner::_peek(int nChars)
	{
		if (isEnd()) return std::string();
		return _source.substr(_current, nChars);
	}


	void Scanner::_scanString()
	{
		std::string tmp;

		while (tmp = _peek(1), (tmp != std::string({ '"' })) && !isEnd())
		{
			if (tmp == "\n")
				++_atLine;
			_current++;
		}
		if (isEnd())
		{
			alox::_error(_atLine, "ending Quote \" is missing");
			return;
		}
		_current++;
		_tkns.push_back(Token{ STRING,_source.substr(_start + 1 , _current - _start - 2),_atLine });
	}



	void Scanner::_scanNumber()
	{
		std::string tmp;

		while (tmp = _peek(1), isDigit(tmp[0]) && !isEnd())
			_current++;
		if (tmp = _peek(2), (tmp[0] == '.') && (isDigit(tmp[1])))
		{
			_current++;
			while (isDigit(_peek(1)[0]))
			{
				_current++;
			}
		}

		_tkns.push_back(Token{ NUMBER,_source.substr(_start , _current - _start),_atLine });
	}

	void Scanner::_scanIdentifier()
	{
		while (isAlphaNumeric(_peek(1)[0]))
			_current++;

		auto type = IDENTIFIER;

		auto id = _source.substr(_start, _current - _start);
		auto itr = _keywords_map.find(id);

		if (itr != _keywords_map.end())
			type = itr->second;

		_addTkn(type);
	}

	__forceinline bool Scanner::isDigit(char c)
	{
		return (c >= '0') && (c <= '9');
	}
	bool Scanner::isAlpha(char c)
	{
		return	((c >= 'a') && (c <= 'z')) ||
			((c >= 'A') && (c <= 'Z')) ||
			(c == '_');
	}
	bool Scanner::isAlphaNumeric(char c)
	{
		return isAlpha(c) || isDigit(c);
	}
}