#pragma once

#include "Parser.h"
class DBProdLines;
class DBStations;
class DBTests;

class ProductionLineParser : private Parser
{
public:
	ProductionLineParser() = delete;
	ProductionLineParser(std::string file_name) : Parser(file_name){}
	void Parse(DBProdLines& prod_line, DBStations& stations, DBTests& tests);
};