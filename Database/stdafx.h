// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>

#include <vector>
#include <string>
#include <set>

//Pre-declaration
class TestRun;
class Test;
class IResult;
class Engine;
class Station;
class ProdLine;
class DBResults;
class DBTestRuns;
class DBTests;
class DBStations;
class DBProdLines;
class DBEngines;

// Data containers
class AuxiliaryData
{
public:
	AuxiliaryData() = delete;
	AuxiliaryData(std::vector<std::string> data);
	double GetMin() { return data_[0]; }
	double GetMax() { return data_[1]; }
	double GetAvg() { return data_[2]; }
	void Print();
private:
	std::vector<double> data_; // data_[0] = min, data_[1] = max, data_[2] = avg
};

// container containing the test run information
struct TestRunInformation
{
	std::string engine_serial_number;
	long production_line_id;
	std::string station_name;
	std::string test_name;
	std::string test_result;
	AuxiliaryData test_aux_data;
	TestRunInformation(TestRun* test_run);
	void Print();
};

struct AllInformation
{
	std::vector<TestRunInformation> information;
	void Print();
};

// Comparators
template<typename T>
struct Comparator
{
	bool operator()(const T* lhs, const T* rhs)
	{
		return *lhs < *rhs;
	}
};