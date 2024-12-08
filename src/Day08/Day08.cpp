// Day08.cpp : Source file for your target.
//

#include "Day08.h"
#include "Utils.h"

#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto map = utils::ReadInput("../Day08_input.txt");
	//std::vector<std::string> map{
	//	"............",
	//	"........0...",
	//	".....0......",
	//	".......0....",
	//	"....0.......",
	//	"......A.....",
	//	"............",
	//	"............",
	//	"........A...",
	//	".........A..",
	//	"............",
	//	"............"
	//};

	std::map<char, std::vector<utils::Pos>> antennas;

	for (std::size_t y = 0; y < map.size(); y++)
	{
		for (std::size_t x = 0; x < map[y].size(); x++)
		{
			if (char c = map[y][x]; c != '.')
			{
				antennas[c].emplace_back(x, y);
			}
		}
	}

	auto inMap = [&](const utils::Pos& p) -> bool
		{
			return p.Y >= 0 && p.Y < map.size() && p.X >= 0 && p.X < map[p.Y].size();
		};

	//Part 1
	std::set<utils::Pos> antinodes;

	for (const auto& [_, ants] : antennas)
	{
		for (std::size_t i = 0; i < ants.size() - 1; i++)
		{
			for (std::size_t j = i + 1; j < ants.size(); j++)
			{
				utils::Pos diff = ants[j] - ants[i];
				antinodes.insert(ants[i] - diff);
				antinodes.insert(ants[j] + diff);
			}
		}
	}

	auto filteredAntinodes = std::views::all(antinodes) | std::views::filter(inMap);

	std::vector<utils::Pos> fa(filteredAntinodes.begin(), filteredAntinodes.end());

	utils::PrintResult(fa.size(), startTime);

	//Part 2
	antinodes.clear();

	for (const auto& [_, ants] : antennas)
	{
		for (std::size_t i = 0; i < ants.size() - 1; i++)
		{
			for (std::size_t j = i + 1; j < ants.size(); j++)
			{
				utils::Pos diff = ants[j] - ants[i];
				
				utils::Pos node1 = ants[i] - diff;
				while (inMap(node1))
				{
					antinodes.insert(node1);
					node1 = node1 - diff;
				}

				utils::Pos node2 = ants[j] + diff;
				while (inMap(node2))
				{
					antinodes.insert(node2);
					node2 = node2 + diff;
				}
			}
		}

		if (ants.size() > 1)
		{
			antinodes.insert(ants.begin(), ants.end());
		}
	}

	//for (const auto& p : antinodes)
	//{
	//	if (map[p.Y][p.X] == '.')
	//	{
	//		map[p.Y][p.X] = '#';
	//	}
	//}

	//utils::PrintGrid(map);

	utils::PrintResult(antinodes.size(), startTime);

	return 0;
}
