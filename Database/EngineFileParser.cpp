#include "stdafx.h"

#include "EngineFileParser.h"

#include "DBEngines.h"
#include "DBProdLines.h"
#include "DBStations.h"
#include "DBTests.h"
#include "DBResults.h"
#include "DBTestRuns.h"
#include <iostream>
#include <fstream>
#include "StringOperations.h"
using namespace std;

bool EngineFileParser::IsNewEngine(std::string line, std::string& engine_serial_number)
{
	string pre_header = "SERIAL NUMBER";
	string line2 = StringOperations::ConvertToUpperCase(line);

	auto pos = line2.find(pre_header);
	if (pos == string::npos)
		return false;

	auto new_pos = pos + pre_header.length() + 1;
	engine_serial_number = line.substr(new_pos, line.length() - new_pos);
	StringOperations::RemoveWhitespaces(engine_serial_number);
	return true;
}

// Returns the string of next engine's serial number
std::string EngineFileParser::ParseEngine(std::string engine_serial_number, const DBProdLines& prod_line, const DBStations& stations,
	const DBTests& tests, DBEngines& engines, DBTestRuns& test_runs, DBResults& results)
{
	Engine* my_engine = engines.NewEngine(engine_serial_number, engine_id_++);
	
	string line;
	string next_engine;
	while (getline(in_file_, line))
	{
		if (IsNewEngine(line, next_engine))
			return next_engine;

		// separate the station information from the rest of the string
		vector<string> separate_station = StringOperations::ExtractDataOutOfDemimeter(line, "/");
		if (separate_station.size() != 2)
		{
			// check if this is Metadata
			string meta_info = StringOperations::ConvertToUpperCase(separate_station[0]);
			if (meta_info == "METADATA" || meta_info == "META DATA")
			{
				// break the loop because the metadata is handled below in a different loop
				break;
			}
			else
			{
				// Ignore the line
				continue;
			}
		}
		string station_name = separate_station[0];

		// separate the test information from the rest of the string
		vector<string> separate_test = StringOperations::ExtractDataOutOfDemimeter(separate_station[1], ":");
		if (separate_test.size() != 2)
		{
			throw "Invalid Engine Test Result format. Should be in the format \"StationName/TestName:Result1(Min;Max;Avg),Result2(Min;Max;Avg),...\"";
		}
		string test_name = separate_test[0];

		// Find the test, station and production_line information
		ProdLine* my_prod_line = prod_line.CurrProdLine();
		if (my_prod_line == nullptr)
		{
			throw "ERROR : Production Line not setup correctly.";
			continue;
		}
		Station* my_station = stations.FindStation(my_prod_line, station_name);
		if (my_station == nullptr)
		{
			string error = "Invalid Input: " + station_name + " is not defined as a station.";
			throw error;
			continue;
		}
		else if (my_station->GetProductionLine() != my_prod_line)
		{
			string error = "Invalid Input: Station " + station_name + " is not defined as a part of the Production Line";
			throw error;
			continue;
		}
		Test* my_test = tests.FindTest(my_station, test_name);
		if (my_test == nullptr)
		{
			string error = "Invalid Input: " + test_name + " is not defined as a test.";
			throw error;
			continue;
		}
		
		auto stations = my_test->GetStations();
		auto it = stations.find(my_station);
		auto it2 = stations.end();
		if (it == stations.end())
		{
			string error = "Invalid Input: Test " + test_name + " is not defined as a part of the Station : " + station_name;
			throw error;
			continue;
		}

		// separate the test results from the rest of the string
		vector<string> separate_results = StringOperations::ExtractDataOutOfDemimeter(separate_test[1], ",");
		// For each results, get and store the results and auxiliary data
		for (auto it : separate_results)
		{

			vector<string> my_test_results = StringOperations::FindTestResultsAndAuxiliaryData(it);

			// insert the auxiliary data
			AuxiliaryData aux_data(vector<string>(my_test_results.begin() + 1, my_test_results.end()));
			IResult* my_result = results.GetResult(my_test_results[0]);

			TestRun* my_test_run = test_runs.NewTestRun(my_engine, my_station, my_test, my_result, aux_data);
		}
	}


	// Handle for the Engine Metadata
	// We know that the current line had "METADATA" text. Starting from the next line, we'll have meta data information
	EngineMetaData* my_meta_data = my_engine->GetMetaData();
	while (getline(in_file_, line))
	{
		if (IsNewEngine(line, next_engine))
			return next_engine;

		vector<string> meta_data = StringOperations::ExtractDataOutOfDemimeter(line, ":");
		string title = StringOperations::ConvertToUpperCase(meta_data[0]);
		if (title == "TIME")
			my_meta_data->time_ = StringOperations::ConvertToLong(meta_data[1]);
		else
			continue;
	}
	return "";
}



void EngineFileParser::Parse(const DBProdLines& prod_line, const DBStations& stations, const DBTests& tests,
	DBEngines& engines, DBTestRuns& test_runs, DBResults& results)
{
	if (!OpenFile())
		return;

	string line, next_engine;
	while (getline(in_file_, line))
	{
		if (IsNewEngine(line, next_engine))
			break; // first engine information found
	}

	while (!next_engine.empty())
	{
		next_engine = ParseEngine(next_engine, prod_line, stations, tests, engines, test_runs, results);
	}

	if (!in_file_.eof())
	{
		throw "ERROR: Somehow, the parsing stopped before all the information from file was read.";
	}
	CloseFile();
}