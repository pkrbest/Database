#pragma once
#include "Station.h"

class DBStations
{
public:
	DBStations() = default;
	~DBStations()
	{
		for (auto a : stations_)
			delete a;
	}

	Station* NewStation(ProdLine* prod_line, std::string station_name);
	Station* FindStation(ProdLine* prod_line, std::string station_name) const;
	SetOfStations GetStations() const { return stations_; }

private:
	SetOfStations stations_;
};
