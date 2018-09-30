#include "stdafx.h"
#include "DatabaseManager.h"

#include "DBTestRuns.h"
#include "DBResults.h"
#include "DBTests.h"
#include "DBStations.h"
#include "DBProdLines.h"
#include "DBEngines.h"
#include "ProductionLineParser.h"
#include "EngineFileParser.h"
#include <iostream>
using namespace std;

DatabaseManager::DatabaseManager(std::string prod_line_file_name, std::string engine_file_name)
{
	prod_line_file_name_ = prod_line_file_name;
	engine_file_name_ = engine_file_name;

	InitializeDatabase();
	PopulateDatabase();
}

DatabaseManager::~DatabaseManager()
{
	if (db_engines_ != nullptr) delete db_engines_;
	if (db_results_ != nullptr) delete db_results_;
	if (db_test_runs_ != nullptr) delete db_test_runs_;
	if (db_tests_ != nullptr) delete db_tests_;
	if (db_stations_ != nullptr) delete db_stations_;
	if (db_prod_lines_ != nullptr) delete db_prod_lines_;

}

void DatabaseManager::InitializeDatabase()
{
	if (db_engines_ == nullptr) 
		db_engines_ = new DBEngines();
	if (db_results_ == nullptr) 
		db_results_ = new DBResults();
	if (db_test_runs_ == nullptr) 
		db_test_runs_ = new DBTestRuns();
	if (db_tests_ == nullptr) 
		db_tests_ = new DBTests();
	if (db_stations_ == nullptr) 
		db_stations_ = new DBStations();
	if (db_prod_lines_ == nullptr) 
		db_prod_lines_ = new DBProdLines();
}

void DatabaseManager::PopulateDatabase()
{
	ProductionLineParser input_parser(prod_line_file_name_);
	EngineFileParser output_parser(engine_file_name_);

	// Read from the file
	input_parser.Parse(*db_prod_lines_, *db_stations_, *db_tests_);
	output_parser.Parse(*db_prod_lines_, *db_stations_, *db_tests_, *db_engines_, *db_test_runs_, *db_results_);

}

void DatabaseManager::PrintProductionLineInformation() const
{
	return db_prod_lines_->PrintInformation(*db_engines_);
}


////////

size_t DatabaseManager::NumberOfEnginesDownTheLine() const
{
	vector<Engine*> stations = db_engines_->EnginesDownTheLine(db_stations_);
	return stations.size();
}

size_t DatabaseManager::NumberOfEnginesDownTheLine(long minutes) const
{
	vector<Engine*> stations = db_engines_->EnginesDownTheLine(db_stations_,minutes);
	return stations.size();
}

AllInformation DatabaseManager::EngineInformationAtStation(std::string station_y) const
{
	AllInformation res;
	Station* my_station = db_stations_->FindStation(nullptr, station_y);
	if (my_station == nullptr)
	{
		string error = "ERROR: The station " + station_y + " is not found";
		throw error;
		return res;
	}

	for (auto test_run : my_station->GetTestRuns())
	{
		res.information.push_back(TestRunInformation(test_run));
	}

	return res;
}

size_t DatabaseManager::EnginesWithFinalPass(std::string station_y) const
{
	AllInformation res;
	Station* my_station = db_stations_->FindStation(nullptr, station_y);
	if (my_station == nullptr)
	{
		string error = "ERROR: The station " + station_y + " is not found";
		throw error;
		return 0;
	}

	set<Engine*> my_engines;
	for (auto engine : db_engines_->GetEngines())
	{
		for (auto test : my_station->GetTests())
		{
			SetOfTestRuns test_runs_per_station_test_engine = my_station->GetTestRuns(test, engine);
			if (test_runs_per_station_test_engine.empty())
				continue;

			TestRun* last_test_run = *(test_runs_per_station_test_engine.rbegin());
			// Check if the last test_run is PASS
			if (last_test_run->IsPass())
			{
				my_engines.insert(engine);
				break;
			}
		}
	}

	// Print the engines with final test pass
	/*
	for (auto en : my_engines)
		cout << en->GetEngineSerialNumber() << " ";
	cout << endl;
	*/

	return my_engines.size();
}

AllInformation DatabaseManager::EngineInformationForFail(long num_runs) const 
{
	DBTests* all_tests = AllTests();
	DBEngines* all_engines = AllEngines();
	
	AllInformation my_results;

	for (auto en : all_engines->GetEngines())
	{
		for (auto test : all_tests->GetTests())
		{
			auto test_runs = test->GetTestRuns();
			if (test_runs.size() < num_runs) continue;

			// Find the n-th test run for the engine
			TestRun* n_th_test_run = nullptr;
			int counter = 0;
			for (auto test_run : test_runs)
			{
				if ((test_run->GetEngine() == en) && (++counter == num_runs))
				{
					// Only then, find the n-th test run
					n_th_test_run = test_run;
					break;
				}
			}

			if (n_th_test_run == nullptr)
				continue;
			
			// we have the n-th test run
			// if the n-th test result is Fail
			if (n_th_test_run->IsFail())
			{
				// Have the information saved!
				// We know the n-th test run. We need to know all the test runs
				auto related_test_runs = AllTestRuns()->GetTestRun(en, test);
				for (auto runs : related_test_runs){
					my_results.information.push_back(TestRunInformation(runs));
				}
			}
		}
	}
	
	return my_results;
}

AllInformation DatabaseManager::EngineInformationMaxRange(long range_min, long range_max) const
{
	AllInformation result;
	DBTestRuns* test_runs = AllTestRuns();
	auto test_run_in_range = test_runs->GetTestRunWithMaxRange(range_min, range_max);
	for (auto run : test_run_in_range)
	{
		result.information.push_back(TestRunInformation(run));
	}
	return result;
}