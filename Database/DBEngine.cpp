#include"stdafx.h"
#include "DBTestRuns.h"
#include "DBTests.h"
#include "DBStations.h"
#include "DBResults.h"
#include "DBProdLines.h"
#include "DBEngines.h"
#include "StringOperations.h"
#include <iostream>
using namespace std;


// Returns the engine that goes down all the prod_lines
// Not necessarily all the tests are performed
// But all the stations in the prod_lines are visited
std::vector<Engine*> DBEngines::EnginesDownTheLine(const DBStations* stations)
{
	std::vector<Engine*> result;
	SetOfStations all_stations_in_prod_line = stations->GetStations();
	
	for (auto engine : engines_)
	{
		CheckIfEngineHasVisitedAllStations(engine, result, all_stations_in_prod_line.size());
	}
	return result;
}

// Returns the engine that goes down all the prod_lines in last x minutes
// Not necessarily all the tests are performed
// But all the stations in the prod_lines are visited
// The metadata time is used as the data indicating number of minutes before which the test was run
std::vector<Engine*> DBEngines::EnginesDownTheLine(const DBStations* stations, long time)
{
	std::vector<Engine*> result;
	SetOfStations all_stations_in_prod_line = stations->GetStations();

	for (auto engine : engines_)
	{
		long curr_time = engine->GetMetaData()->time_;
		if (curr_time <= time)
		{
			CheckIfEngineHasVisitedAllStations(engine, result, all_stations_in_prod_line.size());
		}
	}
	return result;
}

// Find and insert the engines in "result" vector if it visited all the stations
void DBEngines::CheckIfEngineHasVisitedAllStations(Engine* engine, std::vector<Engine*>& result, size_t size_of_prod_line )
{
	SetOfStations curr_stations;
	for (auto test_run : engine->GetTestRuns())
	{
		Station* station = test_run->GetStation();
		curr_stations.insert(station);
	}
	if (curr_stations.size() == size_of_prod_line)
		result.push_back(engine);
}