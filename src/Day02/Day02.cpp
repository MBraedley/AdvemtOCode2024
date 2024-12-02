// Day02.cpp : Source file for your target.
//

#include "Day02.h"
#include "Utils.h"

#include "ctre.hpp"

#include <ranges>

bool CheckReport(const std::vector<int>& levels)
{
	std::vector<int> diffs;
	std::adjacent_difference(levels.begin(), levels.end(), std::back_inserter(diffs));

	auto [minIt, maxIt] = std::minmax_element(std::next(diffs.begin()), diffs.end());
	return *minIt >= 1 && *maxIt <= 3;
}

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day02_input.txt");
	auto lines = utils::ReadInput(inputFile);

	std::vector<std::vector<int>> report;
	for (const std::string& line : lines)
	{
		std::stringstream sstrm(line);
		int i;
		std::vector<int> levels;
		while (sstrm >> i)
		{
			levels.push_back(i);
		}

		report.emplace_back(levels);
		report.emplace_back(levels.rbegin(), levels.rend());
	}

	std::size_t count1 = 0;
	std::size_t count2 = 0;

	for (const auto& levels : report)
	{
		if (CheckReport(levels))
		{
			count1++;
			count2++;
		}
		else
		{
			for (std::size_t i = 0; i < levels.size(); i++)
			{
				std::vector<int> levelsCopy = levels;
				levelsCopy.erase(levelsCopy.begin() + i);
				if (CheckReport(levelsCopy))
				{
					count2++;
					break;
				}
			}
		}
	}

	utils::PrintResult(count1, startTime);
	utils::PrintResult(count2, startTime);

	return 0;
}
