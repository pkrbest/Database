#pragma once

#include <string>
#include <fstream>
#include "Parser.h"
class DBProdLines;
class DBStations;
class DBTests;
class DBEngines;
class DBTestRuns;
class DBResults;

class EngineFileParser : private Parser
{
public:
	EngineFileParser() = delete;
	EngineFileParser(std::string file_name) : Parser(file_name){}

	void Parse(const DBProdLines& prod_line, const DBStations& stations, const DBTests& tests, 
		DBEngines& engines, DBTestRuns& test_runs, DBResults& results );

private:
	std::string ParseEngine(std::string engine_serial_number, const DBProdLines& prod_line, const DBStations& stations,
		const DBTests& tests, DBEngines& engines, DBTestRuns& test_runs, DBResults& results);
	bool IsNewEngine(std::string line, std::string& engine_serial_number);
	long engine_id_ = 0;
};