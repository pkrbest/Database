#pragma once
#include "ProdLine.h"

//pre declaration
class DBEngines;

class DBProdLines
{
public:
	DBProdLines() = default;
	~DBProdLines()
	{
		for (auto a : prod_lines_)
			delete a;
	}

	ProdLine* NewProdLine()
	{
		ProdLine* temp = new ProdLine(unique_cntr++);
		prod_lines_.push_back(temp);
		return temp;
	}

	ProdLine* CurrProdLine() const
	{
		return prod_lines_[0]; // Assuming we have only one production line - this can be changed with the data set
	}

	void PrintInformation(const DBEngines& engines);

private:
	std::vector<ProdLine*> prod_lines_;
	long unique_cntr = 0;
};
