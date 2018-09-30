#pragma once
#include <string>
#include <fstream>

class Parser
{
public:
	Parser(std::string file_name);
	~Parser()	{ CloseFile(); }
	bool OpenFile();
	void CloseFile();

	std::ifstream in_file_;
	std::string file_name_;
};