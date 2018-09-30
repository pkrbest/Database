#include "stdafx.h"
#include "StringOperations.h"
#include <vector>
#include <sstream>
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <ctime>

using namespace std;

string StringOperations::ConvertToUpperCase(std::string input_string)
{
	std::transform(input_string.begin(), input_string.end(), input_string.begin(), toupper);
	return input_string;
}

void StringOperations::RemoveWhitespaces(std::string& input_string)
{
	size_t first_pos = input_string.find_first_not_of(" \t");
	input_string.erase(0, first_pos);

	size_t last_pos = input_string.find_last_not_of(" \t");
	if (std::string::npos != last_pos)
		input_string.erase(last_pos + 1);
}

long StringOperations::ConvertToLong(std::string a)
{
	long d;
	std::istringstream iss(a);
	iss >> d;
	return d;
}

double StringOperations::ConvertToDouble(std::string a)
{
	double d;
	std::istringstream iss(a);
	iss >> d;
	return d;
}
std::vector<std::string> StringOperations::ExtractDataOutOfDemimeter(std::string input_string, std::string delimiter)
{
	std::vector<std::string> result;
	size_t pos = 0;
	while ((pos = input_string.find(delimiter)) != std::string::npos) {
		std::string current = input_string.substr(0, pos);
		RemoveWhitespaces(current);
		result.push_back(current);
		input_string.erase(0, pos + delimiter.length());
	}
	std::string current = input_string.substr(0, pos);
	RemoveWhitespaces(current);
	result.push_back(current);
	return result;
}

std::vector<std::string> StringOperations::FindTestResultsAndAuxiliaryData(std::string input_string)
{
	auto pos1 = input_string.find("(");
	auto pos2 = input_string.find(")");
	std::vector<std::string> result;
	std::string curr;
	std::vector<std::string> aux_data;
	if (pos1 == std::string::npos || pos2 == std::string::npos)
	{
		throw "Invalid Engine Test Result format.Should be in the format \"StationName/TestName:Result1(Min;Max;Avg),Result2(Min;Max;Avg),...\"";
	}
	else
	{
		// The auxiliary data is inputted in the input file itself
		curr = input_string.substr(0, pos1);
		std::string auxiliary_data = input_string.substr(pos1 + 1, (pos2 - pos1 - 1)); // This should be in the fomat xx;yy;zz

		// Extract the data within the delimiter ";"
		aux_data = ExtractDataOutOfDemimeter(auxiliary_data, ";");
		if (aux_data.size() < 3)
			throw "Invalid Test Result format. Should be in the format \"Result(Min;Max;Avg)\"";

	}

	RemoveWhitespaces(curr);
	result.push_back(curr); // Test Result in the first position

	// Insert all the data in the same container
	result.insert(result.end(), aux_data.begin(), aux_data.end());

	return result;
}