// Day20.cpp : Source file for your target.
//

#include "Day20.h"
#include "Utils.h"

#include <ranges>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("../Day20_input.txt");
	//std::vector<std::string> input
	//{
	//	"###############",
	//	"#...#...#.....#",
	//	"#.#.#.#.#.###.#",
	//	"#S#...#.#.#...#",
	//	"#######.#.#.###",
	//	"#######.#.#...#",
	//	"#######.#.###.#",
	//	"###..E#...#...#",
	//	"###.#######.###",
	//	"#...###...#...#",
	//	"#.#####.#.###.#",
	//	"#.#...#.#.#...#",
	//	"#.#.#.#.#.#.###",
	//	"#...#...#...###",
	//	"###############",
	//};

	utils::Pos start;
	utils::Pos end;
	std::set<utils::Pos> walls;

	for (std::size_t y = 0; y < input.size(); y++)
	{
		for (std::size_t x = 0; x < input[y].size(); x++)
		{
			if (input[y][x] == '#')
			{
				walls.emplace(x, y);
			}
			else if (input[y][x] == 'S')
			{
				start.X = x;
				start.Y = y;
			}
			else if (input[y][x] == 'E')
			{
				end.X = x;
				end.Y = y;
			}
		}
	}

	std::map<utils::Pos, std::int32_t> pathCost;

	auto traversePath = [&](const utils::Pos& currentPos) -> utils::Pos
		{
			for (const utils::Pos& neighbour : currentPos.GetNeighbours(input, false))
			{
				if (!walls.contains(neighbour) && !pathCost.contains(neighbour))
				{
					pathCost[neighbour] = pathCost[currentPos] + 1;
					return neighbour;
				}
			}
			assert(false);
			return utils::Pos();
		};

	utils::Pos currentPos = start;
	while (currentPos != end)
	{
		currentPos = traversePath(currentPos);
	}

	const std::vector<utils::Pos> shortcuts
	{
		{-2,0},
		{2,0},
		{0,-2},
		{0,2},
	};

	std::map<std::int32_t, std::int32_t> shortcutCosts;

	for (const auto& [p, cost] : pathCost)
	{
		for (const auto& s : shortcuts)
		{
			if (pathCost.contains(p + s) && pathCost[p + s] > cost + 2)
			{
				shortcutCosts[pathCost[p + s] - cost - 2]++;
			}
		}
	}

	//for (const auto& [cost, count] : shortcutCosts)
	//{
	//	std::cout << cost << ":\t" << count << "\n";
	//}

	std::int32_t goodShortcuts = std::ranges::fold_left(
		std::views::values(
			std::views::all(shortcutCosts)
			| std::views::drop_while([](const std::pair<std::int32_t, std::int32_t>& val) { return val.first < 100; })),
		0, std::plus());

	utils::PrintResult(goodShortcuts, startTime);

	//Part 2
	shortcutCosts.clear();

	for (const auto& [ps, cs] : pathCost)
	{
		for (const auto& [pe, ce] : pathCost)
		{
			auto manDist = ps.GetManDistance(pe);
			assert(manDist == pe.GetManDistance(ps));
			if (manDist != 0 && manDist <= 20 && ce - cs > manDist)
			{
				shortcutCosts[ce - cs - manDist]++;
			}
		}
	}

	//for (const auto& [cost, count] : shortcutCosts)
	//{
	//	std::cout << cost << ":\t" << count << "\n";
	//}
	
	goodShortcuts = std::ranges::fold_left(
		std::views::values(
			std::views::all(shortcutCosts)
			| std::views::drop_while([](const std::pair<std::int32_t, std::int32_t>& val) { return val.first < 100; })),
		0, std::plus());

	utils::PrintResult(goodShortcuts, startTime);

	return 0;
}
