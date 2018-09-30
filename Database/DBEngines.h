#pragma once
#include "Engine.h"

class DBEngines
{
public:
	DBEngines() = default;
	~DBEngines()
	{
		for (auto a : engines_)
			delete a;
	}

	Engine* NewEngine(std::string s_n, long unique_id)
	{
		Engine* temp = new Engine(s_n, unique_id);
		engines_.push_back(temp);
		return temp;
	}

	std::vector<Engine*> GetEngines() const { return engines_; }

	void PrintEngineInformation();
	
	// API Functions

	// Returns the engine that goes down all the prod_lines
	std::vector<Engine*> EnginesDownTheLine(const DBStations* stations);
	std::vector<Engine*> EnginesDownTheLine(const DBStations* stations, long time);
private:
	void CheckIfEngineHasVisitedAllStations(Engine* engine, std::vector<Engine*>& result, size_t size_of_prod_line);

	std::vector<Engine*> engines_;
};
