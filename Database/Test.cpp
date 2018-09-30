#include "stdafx.h"
#include "Test.h"
#include "TestRun.h"
#include <iostream>
using namespace std;

void Test::InsertStation(Station* station)
{
	auto it = stations_.insert(station);
	if (it.first == stations_.end())
	{
		// The TestRun is already present
		throw "ERROR : Looks like a duplicate value of Station is attempted to be inserted in the same Test";
	}
}

void Test::InsertTestRun(TestRun* test_run)
{
	auto it = test_runs_.insert(test_run);
	if (it.first == test_runs_.end())
	{
		// The TestRun is already present
		throw "ERROR : Looks like a duplicate value of Test Run is attempted to be inserted in the same Test";
	}
}

std::string Test::GetFinalTestResult() const
{
	auto final_test_run = *(test_runs_.rbegin());
	return final_test_run->GetResult();
}

bool Test::FinalTestResultIsPass() const
{
	auto final_test_run = *(test_runs_.rbegin());
	return final_test_run->IsPass();
}