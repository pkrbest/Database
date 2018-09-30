#pragma once
#include "Test.h"

class DBTests
{
public:
	DBTests() = default;
	~DBTests()
	{
		for (auto a : test_)
			delete a;
	}

	Test* NewTest(Station* station, std::string test_name);
	Test* FindTest(Station* station, std::string test_name) const
	{
		Test temp(test_name);
		auto it = test_.find(&temp);
		if (it != test_.end())
		{
			// found
			return *it;
		}
		else
		{
			// Not found
			return nullptr;
		}

	}

	SetOfTests GetTests() const { return test_; }

private:
	SetOfTests test_;
};
