#pragma once

#include "Pass.h"
#include "Fail.h"
#include "None.h"

class DBResults
{
public:
	DBResults()
	{
		pass_ = new Pass();
		fail_ = new Fail();
		none_ = new None();
	}

	~DBResults()
	{
		delete pass_;
		delete fail_;
		delete none_;
	}

	IResult* GetResult(std::string result_text);

	Pass* GetPass() const { return pass_; }
	Fail* GetFail() const { return fail_; }
	None* GetNone() const { return none_; }

private:
	Pass* pass_;
	Fail* fail_;
	None* none_;

};