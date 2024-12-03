// Day03.cpp : Source file for your target.
//

#include "Day03.h"
#include "Utils.h"

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto regex = ctre::range<R"(mul\((\d{1,3}),(\d{1,3})\))">;

	auto input = utils::ReadInput("../Day03_input.txt");

	std::uint64_t sum = 0;
	for (std::string line : input)
	{
		for (auto re: regex(line))
		{
			sum += re.get<1>().to_number(10) * re.get<2>().to_number();
		}
	}

	utils::PrintResult(sum, startTime);

	return 0;
}
