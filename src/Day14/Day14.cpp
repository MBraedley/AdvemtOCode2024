// Day14.cpp : Source file for your target.
//

#include "Day14.h"
#include "Utils.h"

#include <ranges>
#include <numeric>
#include <algorithm>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadFormattedInput<R"(p=(\d+),(\d+) v=(-?\d+),(-?\d+))">("../Day14_input.txt");

	const int width = 101;
	const int height = 103;
	const utils::Pos extents(width, height);

	std::vector<std::pair<utils::Pos, utils::Pos>> bots;

	for ( const auto& line : input)
	{
		utils::Pos p(std::stoi(line[1]), std::stoi(line[2]));
		utils::Pos v(std::stoi(line[3]), std::stoi(line[4]));

		if (v.X < 0)
		{
			v.X += width;
		}

		if (v.Y < 0)
		{
			v.Y += height;
		}

		bots.emplace_back(p, v);
	}

	std::size_t topLeft = 0;
	std::size_t topRight = 0;
	std::size_t bottomLeft = 0;
	std::size_t bottomRight = 0;

	const std::int64_t timeSpan = 100;

	for (const auto& [p, v] : bots)
	{
		auto end = (p + v * timeSpan) % extents;

		if (end.X < width / 2 && end.Y < height / 2)
		{
			topLeft++;
		}
		else if (end.X > width / 2 && end.Y < height / 2)
		{
			topRight++;
		}
		else if (end.X < width / 2 && end.Y > height / 2)
		{
			bottomLeft++;
		}
		else if (end.X > width / 2 && end.Y > height / 2)
		{
			bottomRight++;
		}
	}

	utils::PrintResult(topLeft * topRight * bottomLeft * bottomRight, startTime);

	// Part 2

	constexpr std::int64_t p1 = width;
	constexpr std::int64_t p2 = height;
	constexpr std::int64_t period = std::lcm(p1, p2);

	auto printGrid = [&]( std::uint32_t elapsedTime )
		{
			auto grid = std::views::repeat(std::views::repeat('.', width), height) | std::ranges::to<std::vector<std::string>>();
			for (const auto& [p, v] : bots)
			{
				auto end = (p + v * elapsedTime) % extents;

				grid[end.Y][end.X] = '#';
			}

			std::cout << "After " << elapsedTime << " seconds:\n";
			utils::PrintGrid(grid);
 			std::cout << "\n\n";
		};

	printGrid(12);
	printGrid(113);
	printGrid(88);
	printGrid(191);

	for (int i = 1; i < period / p1; i++)
	{
		for (int j = 1; j < period / p2; j++)
		{
			if (p1 * i + 12 == p2 * j + 88)
			{
				printGrid(p1 * i + 12);
			}
		}
	}

	return 0;
}
