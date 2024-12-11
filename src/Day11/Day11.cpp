// Day11.cpp : Source file for your target.
//

#include "Day11.h"
#include "Utils.h"

#include <list>
#include <functional>
#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();
	
	std::map<std::uint64_t, std::size_t> stones;

	std::filesystem::path inputFile("../Day11_input.txt");

	std::ifstream fileStrm(inputFile);
	std::uint64_t stone;
	while (fileStrm >> stone)
	{
		stones[stone]++;
	}

	auto shouldSplit = [](std::uint64_t stone) -> bool
		{
			return std::to_string(stone).size() % 2 == 0;
		};

	auto splitStone = [&]( std::uint64_t stone ) -> std::pair<std::uint64_t, std::uint64_t>
		{
			std::string stoneVal = std::to_string( stone );
			std::uint64_t first = std::stoull(stoneVal.substr(0, stoneVal.size() / 2));
			std::uint64_t second = std::stoull(stoneVal.substr(stoneVal.size() / 2));
			return std::make_pair( first, second );
		};

	std::map<std::uint64_t, std::size_t> nextStones;
	for (std::size_t i = 0; i < 75; i++)
	{
		for (auto [value, count] : stones )
		{
			if (value == 0)
			{
				nextStones[1] += count;
			}
			else if (shouldSplit(value))
			{
				auto split = splitStone(value);
				nextStones[split.first] += count;
				nextStones[split.second] += count;
			}
			else
			{
				nextStones[value * 2024] += count;
			}
		}
		std::swap( stones, nextStones );
		nextStones.clear();

		if( i == 24 )
		{
			auto totalStones = std::ranges::fold_left( std::views::values( std::views::all( stones ) ), 0, std::plus<std::size_t>() );
			utils::PrintResult( totalStones, startTime );
		}
	}

	//Part 2
	auto totalStones = std::ranges::fold_left( std::views::values( std::views::all( stones ) ), 0, std::plus<std::size_t>() );
	utils::PrintResult( totalStones, startTime);

	return 0;
}
