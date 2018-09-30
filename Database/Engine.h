#pragma once
#include "TestRun.h"

class EngineMetaData
{
public:
	long time_;
	void Print() const;
};

class Engine
{
public:
	Engine() = delete;

	Engine(std::string s_n,long unique_id)
	{
		serial_number_ = s_n;
		id_ = unique_id;
	}

	void InsertTestRun(TestRun* test_run)
	{
		auto it = test_runs_.insert(test_run);
		if (it.first == test_runs_.end())
		{
			// The TestRun is already present
			throw "ERROR : Looks like a duplicate value of Production Line is attempted to be inserted";
		}
	}

	void InsertMetadata(const EngineMetaData& meta_data) { meta_data_ = meta_data; }
	EngineMetaData GetMetaData() const { return meta_data_; }
	EngineMetaData* GetMetaData() { return &meta_data_; }
	void SetMetaData(const EngineMetaData& in) { meta_data_ = in; }

	SetOfTestRuns GetTestRuns() const { return test_runs_; }
	std::string GetEngineSerialNumber() { return serial_number_; }

	bool operator< (const Engine& rhs) const { return id_ < rhs.id_; }
private:
	long id_ = 0;
	std::string serial_number_;
	SetOfTestRuns test_runs_;
	EngineMetaData meta_data_;
};