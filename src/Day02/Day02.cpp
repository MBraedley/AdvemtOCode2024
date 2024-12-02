// Day02.cpp : Source file for your target.
//

#include "Day02.h"
#include "Utils.h"

#include "ctre.hpp"

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day02_input.txt");

	constexpr utils::RegexStr re{ R"((\d+) (\d+))" };

	std::vector<std::vector<std::string>> input = utils::ReadFormattedInput<re>(inputFile);

	return 0;
}
