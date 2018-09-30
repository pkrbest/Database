#pragma once
#include "TestRun.h"
#include <set>

class IResult;
class Engine;

class DBTestRuns
{
public:
	DBTestRuns() = default;
	~DBTestRuns()
	{
		for (auto a : test_runs_)
			delete a;
	}

	TestRun* NewTestRun(Engine* engine, Station* station, Test* test, IResult* res, const AuxiliaryData& aux_data);
	SetOfTestRuns GetTestRun(Engine* engine, Test* test) const;
	SetOfTestRuns GetTestRunWithMaxRange(long range_min, long range_max) const;
	static SetOfTestRuns GetTestRunsForEngine(Engine* engine, SetOfTestRuns& test_runs);
		
private:
	SetOfTestRuns test_runs_;
	int unique_counter_ = 0;
};
