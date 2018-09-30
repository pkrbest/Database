// stdafx.cpp : source file that includes just the standard includes
// Database.pch will be the pre-compiled header
// stdafx.obj will contain the pre-compiled type information

#include "stdafx.h"
#include "StringOperations.h"
#include "Test.h"
#include "TestRun.h"
#include "Station.h"
#include "ProdLine.h"
#include "Engine.h"
#include <iostream>
using namespace std;

AuxiliaryData::AuxiliaryData(vector<string> data)
{
	for (auto it : data)
		data_.push_back(StringOperations::ConvertToDouble(it));
}

void AuxiliaryData::Print()
{
	for (auto it : data_)
		cout << it << ";";
}

TestRunInformation::TestRunInformation(TestRun* test_run)
	: test_aux_data(test_run->GetAuxiliaryData())
{
	Engine* engine = test_run->GetEngine();
	Test* test = test_run->GetTest();
	Station* station = test_run->GetStation();
	ProdLine* prod_line = station->GetProductionLine();

	// Save the information
	engine_serial_number = engine->GetEngineSerialNumber();
	production_line_id = prod_line->GetID();
	station_name = station->GetStationName();
	test_name = test->GetTestName();
	test_result = test_run->GetResult();
}

void TestRunInformation::Print()
{
	cout << engine_serial_number << "\t\t" << production_line_id << "\t" <<
		station_name << "\t" << test_name <<
		"\t\t" << test_result << "\t\t";
	test_aux_data.Print();
	cout << endl;
}

void AllInformation::Print()
{
	cout << "Engine\tProductionLine\tStation\t\tTestName\tTestResult\tAuxiliaryData\n";
	for (auto a : information)
	{
		a.Print();
	}
}