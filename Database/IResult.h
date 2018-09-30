#pragma once
using SetOfTestRuns = std::set < TestRun*, Comparator<TestRun> > ;

class IResult
{
public:
	// virtual functions from Result's Output Interface
	virtual std::string GetTestResult() const = 0;
	
	// inserts the test run record in the result
	void Insert(TestRun* test_run);

	// returns the number of test runs in the respective bucket
	SetOfTestRuns GetTestRuns() const { return test_runs_; }

	/*
	// Destructor shouldn't be here because set<TestRun*> is owned by DBTestRun
	~IResult()
	{
		for (auto a : test_runs_)
			if (a != nullptr) delete a;
	}
	*/

	virtual bool IsPass() const { return false; }
	virtual bool IsFail() const { return false; }

protected:
	SetOfTestRuns test_runs_;
};