#include <iostream>
#include <string>

#include "../include/alox.h"


int main(int argc, char* argv[])
{
	if (argc > 2)
	{
		std::cout <<
			R"""( Welcome to alox [Adel's lox interpeter :D]

        Usage: .\alox [script path])""" << std::endl;
		return EXIT_FAILURE;
	}
	{

	alox::alox interp;
	if (argc == 2)
		interp.runFile(argv[1]);
	else
		interp.runPrompt();

	}
	return 0;
}


