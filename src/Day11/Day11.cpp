// Day11.cpp : Source file for your target.
//

#include "Day11.h"
#include "Utils.h"

#include <list>
#include <functional>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::list<std::uint64_t> stones;

	std::filesystem::path inputFile("../Day11_input.txt");

	std::ifstream fileStrm(inputFile);
	std::uint64_t stone;
	while (fileStrm >> stone)
	{
		stones.push_back(stone);
	}

	auto shouldSplit = [](std::uint64_t stone) -> bool
		{
			return std::to_string(stone).size() % 2 == 0;
		};

	auto splitStone = [&](std::list<std::uint64_t>::iterator iter)
		{
			std::string stoneVal = std::to_string(*iter);
			std::uint64_t first = std::stoull(stoneVal.substr(0, stoneVal.size() / 2));
			std::uint64_t second = std::stoull(stoneVal.substr(stoneVal.size() / 2));
			*iter = second;
			stones.insert(iter, first);
		};

	for (std::size_t i = 0; i < 25; i++)
	{
		for (auto iter = stones.begin(); iter != stones.end(); iter++)
		{
			if (*iter == 0)
			{
				*iter = 1;
			}
			else if (shouldSplit(*iter))
			{
				splitStone(iter);
			}
			else
			{
				*iter *= 2024;
			}
		}
	}

	utils::PrintResult(stones.size(), startTime);

	//Part 2
	for (std::size_t i = 25; i < 75; i++)
	{
		for (auto iter = stones.begin(); iter != stones.end(); iter++)
		{
			if (*iter == 0)
			{
				*iter = 1;
			}
			else if (shouldSplit(*iter))
			{
				splitStone(iter);
			}
			else
			{
				*iter *= 2024;
			}
		}
	}

	utils::PrintResult(stones.size(), startTime);

	return 0;
}
