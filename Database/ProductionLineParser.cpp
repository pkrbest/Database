#include "stdafx.h"
#include "ProductionLineParser.h"
#include "DBProdLines.h"
#include "DBStations.h"
#include "DBTests.h"
#include <iostream>
#include <fstream>
#include "StringOperations.h"
using namespace std;

void ProductionLineParser::Parse(DBProdLines& prod_line, DBStations& stations, DBTests& tests)
{
	if (!OpenFile())
		return;

	ProdLine* my_prod_line = prod_line.NewProdLine();
	
	string res;
	while (getline(in_file_, res))
	{
		StringOperations::RemoveWhitespaces(res);
		if (res.empty())
			continue;

		vector<string> my_values = StringOperations::ExtractDataOutOfDemimeter(res, "/");
		if (my_values.size() != 2)
		{
			throw "Invalid format. Production Line File Format should be : \"Station Name1 / TestName1\"";
		}

		Station* my_station = stations.FindStation(my_prod_line, my_values[0]);
		if (my_station == nullptr)
		{
			my_station = stations.NewStation(my_prod_line, my_values[0]);
		}
			
		Test* test = tests.NewTest(my_station, my_values[1]);
	}

	CloseFile();
}