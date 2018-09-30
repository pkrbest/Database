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

IResult* DBResults::GetResult(std::string result_text)
{
	result_text = StringOperations::ConvertToUpperCase(result_text);
	if (result_text == "PASS")
		return pass_;
	else if (result_text == "FAIL")
		return fail_;
	else if (result_text == "NONE")
		return none_;
	else
		return nullptr;
}

TestRun* DBTestRuns::NewTestRun(Engine* engine, Station* station, Test* test, IResult* res, const AuxiliaryData& aux_data)
{
	TestRun* temp = new TestRun(unique_counter_++, engine, station, test, res, aux_data);
	auto it = test_runs_.insert(temp);
	if (it.first == test_runs_.end())
	{
		// The TestRun is already present
		throw "ERROR : Looks like a duplicate value of TestRun is attempted to be inserted.";
	}
	res->Insert(temp);
	engine->InsertTestRun(temp);
	test->InsertTestRun(temp);
	station->InsertTestRun(temp);
	return temp;
}

Test* DBTests::NewTest(Station* station, std::string test_name)
{
	Test* temp = new Test(test_name);
	auto it = test_.insert(temp);
	if (!it.second)
	{
		delete temp; // make sure to free the allocated memory
		temp = *(it.first);
	}
	temp->InsertStation(station);
	station->InsertTest(temp);
	return temp;
}

void DBProdLines::PrintInformation(const DBEngines& engines)
{
	for (auto engine : engines.GetEngines())
	{
		cout << "Engine Serial Number : " << engine->GetEngineSerialNumber() << endl;
		for (auto it : prod_lines_)
		{
			cout << "Production Line " << it->GetID() << ":\n";
			cout << "***********************************\n";
			for (auto it0 : prod_lines_[0]->GetStations())
			{
				for (auto it1 : it0->GetTests())
				{
					cout << it0->GetStationName() << "/";
					cout << it1->GetTestName() << ":";
					for (auto it2 : it1->GetTestRuns())
					{
						if (it2->GetEngine() == engine)
						{
							cout << it2->GetResult() << "(";
							it2->GetAuxiliaryData().Print();
							cout << "),";
						}
					}
					cout << endl;
				}
			}
			cout << "--- Engine Metadata ---";
			engine->GetMetaData()->Print();
			cout << "***********************************\n";
		}

	}
}

Station* DBStations::NewStation(ProdLine* prod_line, std::string station_name)
{
	Station* temp = new Station(station_name, prod_line);
	auto it = stations_.insert(temp);
	prod_line->InsertStation(temp);
	return temp;
}

Station* DBStations::FindStation(ProdLine* prod_line, std::string station_name) const
{
	Station* res;
	Station stat(station_name, prod_line);
	auto it = stations_.find(&stat);
	if (it != stations_.end())
	{	//Found
		res = *it;
	}
	else
	{	// Not Found
		res = nullptr;
	}
	return res;
}

SetOfTestRuns DBTestRuns::GetTestRun(Engine* engine, Test* test) const
{
	SetOfTestRuns result;
	for (auto test_runs : test_runs_)
	{
		if ((test_runs->GetEngine() == engine) && (test_runs->GetTest() == test))
			result.insert(test_runs);
	}
	return result;
}

SetOfTestRuns DBTestRuns::GetTestRunWithMaxRange(long range_min, long range_max) const
{
	SetOfTestRuns result;
	for (auto test_runs : test_runs_)
	{
		if ((test_runs->GetAuxiliaryData().GetMax() <= range_max) &&
			(test_runs->GetAuxiliaryData().GetMax() >= range_min))
		{
			result.insert(test_runs);
		}
	}
	return result;
}

SetOfTestRuns DBTestRuns::GetTestRunsForEngine(Engine* engine, SetOfTestRuns& test_runs)
{
	SetOfTestRuns test_runs_for_engine;
	for (auto run : test_runs)
	{
		if (run->GetEngine() == engine)
		{
			test_runs_for_engine.insert(run);
		}
	}
	return test_runs_for_engine;
}