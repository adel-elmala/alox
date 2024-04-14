#include <iostream>
#include <fstream>
#include <ios>
#include <cstdlib>

#include "../include/alox.h"

namespace alox
{

	bool alox::hasError = false;


	alox::alox()
	{
		_interpeter = new Interpeter;
		_scanner = new Scanner();
		_parser = new Parser();
	}

	alox::~alox()
	{
		delete _scanner;
		delete _interpeter;
	}

	static std::string readFile(std::string path)
	{
		std::fstream file(path, std::ios_base::in);

		if (!file.is_open())
		{
			std::cerr << "Failed to open: " << path << "\n";
			return std::string();
		}

		// find the file size
		auto file_size = file.tellg();
		file.seekg(0, std::ios_base::end);
		file_size = file.tellg() - file_size;
		file.seekg(0, std::ios_base::beg);

		// read the file content 
		char* fileBuffer = new char[(unsigned int)file_size + 1];

		memset(fileBuffer, 0, (unsigned int)file_size + 1);
		file.read(fileBuffer, file_size);

		// copy into a string
		std::string fileContent(fileBuffer, file_size);

		// free resources
		delete[] fileBuffer;
		file.close();

		return fileContent;
	}


	void alox::runFile(std::string script_path)
	{
		std::string source = readFile(script_path);
		// run the file
		run(source);

	}

	void alox::runPrompt()
	{
		std::string line;
		for (;;)
		{
			std::cout << "alox>";
			std::getline(std::cin, line);
			if (line.empty())
				break;
			run(line);
		}
	}

	void alox::run(std::string source)
	{
		_scanner->addSource(source);

		auto tkns = _scanner->scanTokens();
		for (auto tkn : tkns)
			std::cout << tkn.str << " at line: " << tkn.line << std::endl;

		_parser->addTkns(tkns);

		Expr* e = _parser->parse();

		auto value = _interpeter->evalute(e);

		delete e;
	}

}