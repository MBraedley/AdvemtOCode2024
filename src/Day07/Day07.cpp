// Day07.cpp : Source file for your target.
//

#include "Day07.h"
#include "Utils.h"

#include "BS_thread_pool.hpp"

#include <ranges>
#include <future>

bool RunCalc(std::uint64_t target, std::deque<std::uint64_t> components, bool part2 = false)
{
	if (components.size() == 1)
	{
		return components.front() == target;
	}

	auto lhs = components.front();
	components.pop_front();
	auto rhs = components.front();
	components.pop_front();

	components.push_front(lhs * rhs);
	if (RunCalc(target, components, part2))
	{
		return true;
	}
	components.pop_front();
	components.push_front(lhs + rhs);
	if (RunCalc(target, components, part2))
	{
		return true;
	}

	if (part2)
	{
		std::uint64_t val = std::stoll(std::to_string(lhs) + std::to_string(rhs));
		components.pop_front();
		components.push_front(val);
		if (RunCalc(target, components, part2))
		{
			return true;
		}
	}

	return false;
}

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto rawInput = utils::ReadInput("../Day07_input.txt");

	std::vector<std::pair<std::uint64_t, std::deque<std::uint64_t>>> testCases;

	for (const auto& line : rawInput)
	{
		auto vals = utils::Tokenize(line, ' ');
		std::uint64_t target = std::stoll(vals[0]);
		auto components = std::views::all(vals) | std::views::drop(1) | std::views::transform([](const std::string& val) { return std::stoll(val); });
		testCases.emplace_back(target, std::deque<std::uint64_t>(components.begin(), components.end()));
	}

	std::uint64_t validTargetSum = 0;
	std::uint64_t validTargetSum2 = 0;
	std::vector<std::future<void>> futs;

	BS::thread_pool pool;

	for (const auto& [target, components] : testCases)
	{
		futs.emplace_back(pool.submit_task( [&]()
			{
				if (RunCalc(target, components, false))
				{
					validTargetSum += target;
					validTargetSum2 += target;
				}
				else
				{
					if (RunCalc(target, components, true))
					{
						validTargetSum2 += target;
					}
				}
			}));
	}

	for (auto& fut : futs)
	{
		fut.get();
	}

	utils::PrintResult(validTargetSum, startTime);
	utils::PrintResult(validTargetSum2, startTime);

	return 0;
}
