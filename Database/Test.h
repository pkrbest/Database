#pragma once
#include "TestRun.h"

class Test 
{
public:
	Test() = delete;
	
	Test(std::string name)	{ test_name_ = name; }

	void InsertStation(Station* station);
	void InsertTestRun(TestRun* test_run);
	std::set<Station*> GetStations() const  { return stations_; }
	SetOfTestRuns GetTestRuns() const  { return test_runs_; }
	std::string GetTestName() const { return test_name_; }

	// returns the final value of the test
	// given that the last result of the test is considered the final value of the test
	std::string GetFinalTestResult() const;
	bool FinalTestResultIsPass() const;

	// comparison operator
	bool operator< (const Test& rhs) const { return test_name_ < rhs.test_name_; }

private:
	SetOfTestRuns test_runs_;
	std::set<Station*> stations_;
	std::string test_name_;
};

using SetOfTests = std::set<Test*, Comparator<Test >>;