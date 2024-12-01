// Day01.cpp : Source file for your target.
//

#include "Day01.h"
#include "Utils.h"

#include <ranges>
#include <unordered_map>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::filesystem::path inputFile("../Day01_input.txt");

	std::vector<std::int32_t> left;
	std::vector<std::int32_t> right;

	std::int32_t x, y;

	std::ifstream fileStrm(inputFile);
	while (fileStrm >> x >> y)
	{
		left.push_back(x);
		right.push_back(y);
	}

	std::ranges::sort(left);
	std::ranges::sort(right);
	
	std::vector<std::int32_t> diffs;

	assert(left.size() == right.size());

	std::ranges::transform(left, right, std::back_inserter(diffs), [](const auto& lhs, const auto& rhs)
		{
			return std::abs(lhs - rhs);
		});

	//auto sum = std::views::take(diffs);
	std::uint32_t sum = 0;
	for (auto val : diffs)
	{
		sum += val;
	}

	utils::PrintResult(sum, startTime);

	//Part 2:
	std::set<std::int32_t> uniqueLeft{ left.begin(), left.end() };
	std::map<std::int32_t, std::size_t> rightCount;

	for (auto val : right)
	{
		rightCount[val]++;
	}

	std::size_t sim = 0;
	for (auto val : uniqueLeft)
	{
		sim += val * rightCount[val];
	}

	utils::PrintResult(sim, startTime);
	
	return 0;
}
