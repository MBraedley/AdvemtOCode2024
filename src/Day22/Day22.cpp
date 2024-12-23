// Day22.cpp : Source file for your target.
//

#include "Day22.h"
#include "Utils.h"

#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	//auto input = std::views::all(utils::ReadInput("../Day22_input.txt")) | std::views::transform([](const std::string& s) {return std::stoull(s); }) | std::ranges::to<std::vector<std::uint64_t>>();

	std::vector<std::uint64_t> input
	{
		1,
		10,
		100,
		2024,
	};

	auto mix = [](const std::uint64_t& lhs, const std::uint64_t& rhs) -> std::uint64_t
		{
			return lhs ^ rhs;
		};

	static_assert(mix(42, 15) == 37);

	auto prune = [](const std::uint64_t& num) -> std::uint64_t
		{
			return num % 16777216;
		};

	static_assert(prune(100000000) == 16113920);

	auto step1 = [&](const std::uint64_t& num) -> std::uint64_t
		{
			std::uint64_t ret = num * 64;
			ret = mix(num, ret);
			ret = prune(ret);
			return ret;
		};

	auto step2 = [&](const std::uint64_t& num) -> std::uint64_t
		{
			std::uint32_t ret = num / 32;
			ret = mix(num, ret);
			ret = prune(ret);
			return ret;
		};

	auto step3 = [&](const std::uint64_t& num) -> std::uint64_t
		{
			std::uint32_t ret = num * 2048;
			ret = mix(num, ret);
			ret = prune(ret);
			return ret;
		};

	auto permute = [&](std::uint64_t& num)
		{
			num = step1(num);
			num = step2(num);
			num = step3(num);
		};

	//std::uint64_t test = 123;

	//for (std::size_t i = 0; i < 10; i++)
	//{
	//	permute(test);

	//	std::cout << test << "\n";
	//}

	for (auto& num : input)
	{
		for (std::size_t i = 0; i < 2000; i++)
		{
			permute(num);
		}
	}

	std::uint64_t sum = std::ranges::fold_left(std::views::all(input), 0, std::plus());
	utils::PrintResult(sum, startTime);

	return 0;
}
