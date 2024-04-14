#pragma once 

#include <iostream>
#include <string>

#include "scanner.h"
#include "parser.h"
#include "interpeter.h"

namespace alox
{


	class alox
	{
	public:
		alox();
		~alox();

		void runFile(std::string script_path);
		void runPrompt();
		void run(std::string source);

		static __forceinline void _error(int line, std::string message)
		{
			std::cerr << "[Line:" << line << "] Error: " << " : " << message << "\n";
			hasError = true;
		}

	private:
		static bool hasError;
		std::string filePath;
		Interpeter* _interpeter;
		Scanner* _scanner;
		Parser* _parser;

	};

}