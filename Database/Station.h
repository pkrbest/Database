#pragma once
#include <set>
#include "Test.h"

// pre-declaration
class ProdLine;

class Station
{
public: 
	Station() = delete;

	Station(std::string name, ProdLine* prod_line)
	{
		station_name_ = name;
		prod_line_ = prod_line;
	}

	void InsertTest(Test* test)
	{
		tests_.insert(test);
	}

	void InsertTestRun(TestRun* test_run)
	{
		auto it = test_runs_.insert(test_run);
		if (!it.second)
		{
			std::string error = "ERROR : Duplicate record of test run is attempted to be inserted in Station.";
			throw error;
		}
	}


	ProdLine* GetProductionLine() const { return prod_line_; }
	SetOfTests GetTests() const { return tests_; }
	SetOfTestRuns GetTestRuns() const { return test_runs_; }
	std::string GetStationName() const { return station_name_; }
	SetOfTestRuns GetTestRuns(Test* test, Engine* engine) const
	{
		SetOfTestRuns result;
		for (auto a : test_runs_)
		{
			if (a->GetTest() == test && a->GetEngine() == engine)
				result.insert(a);
		}
		return result;
	}

	bool operator< (const Station& rhs) const { return station_name_ < rhs.station_name_; }
	
private:
	std::string station_name_;
	ProdLine* prod_line_;
	SetOfTestRuns test_runs_;
	SetOfTests tests_;
};

using SetOfStations = std::set < Station*, Comparator<Station> > ;