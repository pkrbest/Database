#pragma once

class TestRun
{
public:
	TestRun() = delete;
	TestRun(long unique_id, Engine* engine, Station* station, Test* test, IResult* res, const AuxiliaryData& aux_data);
	Test* GetTest() const { return test_; }
	Station* GetStation() const { return station_; }
	std::string GetResult() const;
	AuxiliaryData GetAuxiliaryData() const { return aux_; }
	Engine* GetEngine() const { return engine_; }
	bool IsPass() const;
	bool IsFail() const;
	bool operator< (const TestRun& rhs) const;

	// No Destructor needed
private:
	long id_;
	Test* test_;
	Engine* engine_;
	Station* station_;
	IResult* result_;
	AuxiliaryData aux_;
};

using SetOfTestRuns = std::set < TestRun*, Comparator<TestRun> >;