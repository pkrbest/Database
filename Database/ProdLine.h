#pragma once
#include <deque>

// pre-declaration
class Station;

class ProdLine
{
public:
	ProdLine() = delete;

	ProdLine(long id)
	{
		id_ = id;
	}

	void InsertStation(Station* station)
	{
		stations_.push_back(station);
	}

	std::deque<Station*> GetStations() const { return stations_; }
	long GetID() const { return id_; }
	bool operator< (const ProdLine& rhs) const { return id_ < rhs.id_; }
	bool operator== (const ProdLine& rhs) const { return id_ == rhs.id_; }

private:
	long id_;
	std::deque<Station*> stations_;
};