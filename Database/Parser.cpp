#include"stdafx.h"
#include "Parser.h"
#include "StringOperations.h"
using namespace std;

Parser::Parser(std::string file_name)
{
	StringOperations::RemoveWhitespaces(file_name);
	file_name_ = file_name;
}

bool Parser::OpenFile()
{
	in_file_.open(file_name_);
	if (!in_file_.is_open())
	{
		std::string error = "ERROR : File " + file_name_ + " cannot be opened.";
		throw error;
		return false;
	}
	return true;
}

void Parser::CloseFile()
{
	if (in_file_.is_open())
		in_file_.close();
}