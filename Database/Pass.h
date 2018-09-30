#pragma once

#include "IResult.h"

class Pass : public IResult
{
public:
	Pass() = default;
	virtual std::string GetTestResult() const final { return "PASS"; }
	virtual bool IsPass() const final{ return true; }
};
