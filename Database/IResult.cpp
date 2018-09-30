#include "stdafx.h"
#include "TestRun.h"
#include "IResult.h"

void IResult::Insert(TestRun* test_run)
{
	test_runs_.insert(test_run);
}