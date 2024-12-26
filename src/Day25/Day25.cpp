// Day25.cpp : Source file for your target.
//

#include "Day25.h"
#include "Utils.h"

#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("../Day25_input.txt") | std::views::split("") | std::ranges::to<std::vector<std::vector<std::string>>>();
	//std::vector<std::vector<std::string>> input
	//{
	//	{
	//	"#####",
	//	".####",
	//	".####",
	//	".####",
	//	".#.#.",
	//	".#...",
	//	".....",
	//	},
	//	{
	//		"#####",
	//		"##.##",
	//		".#.##",
	//		"...##",
	//		"...#.",
	//		"...#.",
	//		".....",
	//	},
	//	{
	//		".....",
	//		"#....",
	//		"#....",
	//		"#...#",
	//		"#.#.#",
	//		"#.###",
	//		"#####",
	//	},
	//	{
	//		".....",
	//		".....",
	//		"#.#..",
	//		"###..",
	//		"###.#",
	//		"###.#",
	//		"#####",
	//	},
	//	{
	//		".....",
	//		".....",
	//		".....",
	//		"#....",
	//		"#.#..",
	//		"#.#.#",
	//		"#####",
	//	}
	//};

	std::vector<std::array<std::uint8_t, 5>> keys;
	std::vector<std::array<std::uint8_t, 5>> locks;

	for (const auto& profile : input)
	{
		std::vector<std::string> transposed = utils::Transpose(profile);
		std::array<std::uint8_t, 5> lockKey;

		if (transposed[0].starts_with("#")) //key
		{
			for (std::size_t i = 0; i < transposed.size(); i++)
			{
				lockKey[i] = transposed[i].find_last_of('#');
			}
			keys.push_back(lockKey);
		}
		else
		{
			for (std::size_t i = 0; i < transposed.size(); i++)
			{
				lockKey[i] = 5 - transposed[i].find_last_of('.');
			}
			locks.push_back(lockKey);
		}
	}

	const std::uint8_t maxCut = 5;

	std::uint32_t workingPairs = 0;

	for (const auto& lock : locks)
	{
		for (const auto& key : keys)
		{
			auto overlaps = std::ranges::count_if( std::views::zip(lock, key)
				| std::views::transform([](const std::tuple<std::uint8_t, std::uint8_t>& pin)
					{
						return std::get<0>(pin) + std::get<1>(pin);
					}),
				[&](const std::uint8_t& val)
					{
						return val > maxCut;
					});

			if (overlaps == 0)
			{
				workingPairs++;
			}
		}
	}

	utils::PrintResult(workingPairs, startTime);

	return 0;
}
