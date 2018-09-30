#pragma once
#include "IResult.h"

class None : public IResult
{
public:
	None() = default;
	virtual std::string GetTestResult() const final { return "NONE"; }
};

