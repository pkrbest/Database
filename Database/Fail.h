#pragma once

#include "IResult.h"

class Fail : public IResult
{
public:
	Fail() = default;
	virtual std::string GetTestResult() const final { return "FAIL"; }
	virtual bool IsFail() const final{ return true; }
};

