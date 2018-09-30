#pragma once
#include <string>
#include <vector>

struct StringOperations
{

	static std::string ConvertToUpperCase(std::string input_string);
	
	// Removes the beginning and trailing whitespaces
	static void RemoveWhitespaces(std::string& input_string);
	
	static double ConvertToDouble(std::string a);
	static long ConvertToLong(std::string a);
	
	static std::vector<std::string> ExtractDataOutOfDemimeter(std::string input_string, std::string delimiter);
	static std::vector<std::string> FindTestResultsAndAuxiliaryData(std::string input_string);

};