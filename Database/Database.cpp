// Database.cpp : Defines the entry point for the console application.
//
#include "stdafx.h"
#include "DatabaseManager.h"
#include <iostream>
using namespace std;

int _tmain()
{
	try
	{
		string FileFolder = "InputData1";
		//string FileFolder = "InputData2";

		string production_line_file = FileFolder + "\\ProductionLine.txt";
		string engine_info_file = FileFolder + "\\Engine.txt";
		DatabaseManager db_mgr(production_line_file, engine_info_file);
		db_mgr.PrintProductionLineInformation();

		// Number of Engines that have come down all the stations
		cout << "*****************************************************************\n";
		cout << "(a) Number of engines that have come down the line = " << db_mgr.NumberOfEnginesDownTheLine() << endl;
		cout << "*****************************************************************\n";

		// Number of engines that have come down the line in the last X minutes, where X is an integer
		int x = 5;
		cout << "*****************************************************************\n";
		cout << "(b) Number of engines that have come down the line in " << x << " minutes = ";
		cout << db_mgr.NumberOfEnginesDownTheLine(x) << endl;
		cout << "*****************************************************************\n";

		// Return all engine information collected at Station Y, where Station Y is a station on the line
		string station = "ColdTestStation";
		cout << "*****************************************************************\n";
		cout << "(c) All Engine Information at " << station << ":\n";
		AllInformation all_information = db_mgr.EngineInformationAtStation(station); // this object could be used in any API
		all_information.Print();
		cout << "*****************************************************************\n";

		//Given that the last result of a test is considered the Final value of the test, 
		// how many engines had a Final PASS at Station Z, where Station Z is a station on the line.
		cout << "*****************************************************************\n";
		station = "ColdTestStation";
		cout << "(d) Number of Engines with final PASS in Station " << station 
			<< " = " << db_mgr.EnginesWithFinalPass(station) << endl;
		cout << "*****************************************************************\n";

		// All engine information for the engines that had a FAIL on the second test run
		long num_run = 2;
		AllInformation information_fail = db_mgr.EngineInformationForFail(num_run);
		cout << "*****************************************************************\n";
		cout << "(e) Engine Information for FAIL at test result : " << num_run << endl;
		information_fail.Print();
		cout << "*****************************************************************\n";

		// All engine information that had a max between A and B, where A and B are integers.
		long A = 0;
		long B = 12;
		AllInformation information_max_in_range = db_mgr.EngineInformationMaxRange(A, B);
		cout << "*****************************************************************\n";
		cout << "(f) Engine Information for Max in range of (" << A << " and " << B << ")\n";
		information_max_in_range.Print();
		cout << "*****************************************************************\n";
	}
	catch (const std::exception& ex)
	{
		cout << ex.what() << endl;
	}

	cin.get();
    return 0;
}
