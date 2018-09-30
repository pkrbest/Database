#include "stdafx.h"
#include "TestRun.h"
#include "IResult.h"
#include "Station.h"
#include "StringOperations.h"
#include <iostream>
using namespace std;

TestRun::TestRun(long unique_id, Engine* engine, Station* station, Test* test, IResult* res, const AuxiliaryData& aux_data) :
aux_(aux_data)
{
	id_ = unique_id;
	test_ = test;
	result_ = res;
	engine_ = engine;
	station_ = station;
}

std::string TestRun::GetResult() const { 
	return result_->GetTestResult(); 
}

bool TestRun::IsPass() const 
{ 
	return result_->IsPass(); 
}

bool TestRun::IsFail() const 
{ 
	return result_->IsFail(); 
}

bool TestRun::operator< (const TestRun& rhs) const {

/*	if (engine_ != rhs.engine_)
		return engine_ < rhs.engine_;

	if (station_->GetProductionLine() != rhs.station_->GetProductionLine())
		return station_->GetProductionLine() < station_->GetProductionLine();

	if (station_ != rhs.station_)
		return station_ < rhs.station_;

	if (test_ != rhs.test_)
		return test_ < rhs.test_;
		*/
	return id_ < rhs.id_;
}