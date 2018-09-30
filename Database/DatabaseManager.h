#pragma once

class DatabaseManager
{
public:
	DatabaseManager() = delete;
	DatabaseManager(std::string prod_line_file_name, std::string engine_file_name);
	~DatabaseManager();

	// Initialize and Populates the databases from the input file
	void InitializeDatabase();
	void PopulateDatabase();

	// Getters
	DBResults* AllResults() const { return db_results_; }
	DBTestRuns* AllTestRuns() const { return db_test_runs_;}
	DBTests* AllTests() const { return db_tests_;}
	DBStations* AllStations() const { return db_stations_; }
	DBProdLines* AllProdLines() const { return db_prod_lines_; }
	DBEngines* AllEngines() const { return db_engines_; }

	// Delegators
	void PrintProductionLineInformation() const;

	//--------------------------------------------------------------------------------------------------
	// API Functions
	//---------------------------------------------------------------------------------------------------
	// Number of engines that have come down the line
	size_t NumberOfEnginesDownTheLine() const;
	
	// Number of engines that have come down the line in the last X minutes, where X is an integer
	size_t NumberOfEnginesDownTheLine(long minutes) const;
	
	// Return all engine information collected at Station Y, where Station Y is a station on the line
	AllInformation EngineInformationAtStation(std::string station_y) const;

	//Given that the last result of a test is considered the Final value of the test, 
	// how many engines had a Final PASS at Station Z, where Station Z is a station on the line.
	size_t EnginesWithFinalPass(std::string station_y) const;

	// All engine information for the engines that had a FAIL on the second test run
	AllInformation EngineInformationForFail(long num_runs) const;

	// All engine information that has a max between A and B, where A and B are integers.
	// Here, range_min = A, range_max = B
	AllInformation EngineInformationMaxRange(long range_min, long range_max) const;

private:
	// The databases
	DBResults* db_results_ = nullptr;
	DBTestRuns* db_test_runs_ = nullptr;
	DBTests* db_tests_ = nullptr;
	DBStations* db_stations_ = nullptr;
	DBProdLines* db_prod_lines_ = nullptr;
	DBEngines* db_engines_ = nullptr;

	// Filenames
	std::string prod_line_file_name_;
	std::string engine_file_name_;

};