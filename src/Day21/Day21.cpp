// Day21.cpp : Source file for your target.
//

#include "Day21.h"
#include "Utils.h"

#include <ranges>
#include <optional>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("../Day21_input.txt");
	//std::vector<std::string> input
	//{
	//	"029A",
	//	"980A",
	//	"179A",
	//	"456A",
	//	"379A",
	//};

	const std::map<std::pair<char, char>, std::string> doorKeypad
	{
		{{'A', 'A'}, "A"},
		{{'A', '0'}, "<A"},
		{{'A', '1'}, "^<<A"},
		{{'A', '2'}, "<^A"},
		{{'A', '3'}, "^A"},
		{{'A', '4'}, "^^<<A"},
		{{'A', '5'}, "<^^A"},
		{{'A', '6'}, "^^A"},
		{{'A', '7'}, "^^^<<A"},
		{{'A', '8'}, "<^^^A"},
		{{'A', '9'}, "^^^A"},

		{{'0', 'A'}, ">A"},
		{{'0', '0'}, "A"},
		{{'0', '1'}, "<^A"},
		{{'0', '2'}, "^A"},
		{{'0', '3'}, ">^A"},
		{{'0', '4'}, "<^^A"},
		{{'0', '5'}, "^^A"},
		{{'0', '6'}, ">^^A"},
		{{'0', '7'}, "<^^^A"},
		{{'0', '8'}, "^^^A"},
		{{'0', '9'}, ">^^^A"},

		{{'1', 'A'}, ">>vA"},
		{{'1', '0'}, ">vA"},
		{{'1', '1'}, "A"},
		{{'1', '2'}, ">A"},
		{{'1', '3'}, ">>A"},
		{{'1', '4'}, "^A"},
		{{'1', '5'}, ">^A"},
		{{'1', '6'}, "^>>A"},
		{{'1', '7'}, "^^A"},
		{{'1', '8'}, ">^^A"},
		{{'1', '9'}, ">>^^A"},

		{{'2', 'A'}, "v>A"},
		{{'2', '0'}, "vA"},
		{{'2', '1'}, "<A"},
		{{'2', '2'}, "A"},
		{{'2', '3'}, ">A"},
		{{'2', '4'}, "<^A"},
		{{'2', '5'}, "^A"},
		{{'2', '6'}, ">^A"},
		{{'2', '7'}, "<^^A"},
		{{'2', '8'}, "^^A"},
		{{'2', '9'}, ">^^A"},

		{{'3', 'A'}, "vA"},
		{{'3', '0'}, "<vA"},
		{{'3', '1'}, "<<A"},
		{{'3', '2'}, "<A"},
		{{'3', '3'}, "A"},
		{{'3', '4'}, "<<^A"},
		{{'3', '5'}, "<^A"},
		{{'3', '6'}, "^A"},
		{{'3', '7'}, "<<^^A"},
		{{'3', '8'}, "<^^A"},
		{{'3', '9'}, "^^A"},

		{{'4', 'A'}, ">>vvA"},
		{{'4', '0'}, ">vvA"},
		{{'4', '1'}, "vA"},
		{{'4', '2'}, "v>A"},
		{{'4', '3'}, "v>>A"},
		{{'4', '4'}, "A"},
		{{'4', '5'}, ">A"},
		{{'4', '6'}, ">>A"},
		{{'4', '7'}, "^A"},
		{{'4', '8'}, ">^A"},
		{{'4', '9'}, ">>^A"},

		{{'5', 'A'}, ">vvA"},
		{{'5', '0'}, "vvA"},
		{{'5', '1'}, "<vA"},
		{{'5', '2'}, "vA"},
		{{'5', '3'}, "v>A"},
		{{'5', '4'}, "<A"},
		{{'5', '5'}, "A"},
		{{'5', '6'}, ">A"},
		{{'5', '7'}, "<^A"},
		{{'5', '8'}, "^A"},
		{{'5', '9'}, ">^A"},

		{{'6', 'A'}, "vvA"},
		{{'6', '0'}, "<vvA"},
		{{'6', '1'}, "<<vA"},
		{{'6', '2'}, "<vA"},
		{{'6', '3'}, "vA"},
		{{'6', '4'}, "<<A"},
		{{'6', '5'}, "<A"},
		{{'6', '6'}, "A"},
		{{'6', '7'}, "<<^A"},
		{{'6', '8'}, "<^A"},
		{{'6', '9'}, "^A"},

		{{'7', 'A'}, "vvv>>A"},
		{{'7', '0'}, "vvv>A"},
		{{'7', '1'}, "vvA"},
		{{'7', '2'}, "vv>A"},
		{{'7', '3'}, "vv>>A"},
		{{'7', '4'}, "vA"},
		{{'7', '5'}, "v>A"},
		{{'7', '6'}, "v>>A"},
		{{'7', '7'}, "A"},
		{{'7', '8'}, ">A"},
		{{'7', '9'}, ">>A"},

		{{'8', 'A'}, ">vvvA"},
		{{'8', '0'}, "vvvA"},
		{{'8', '1'}, "vv<A"},
		{{'8', '2'}, "vvA"},
		{{'8', '3'}, "vv>A"},
		{{'8', '4'}, "v<A"},
		{{'8', '5'}, "vA"},
		{{'8', '6'}, "v>A"},
		{{'8', '7'}, "<A"},
		{{'8', '8'}, "A"},
		{{'8', '9'}, ">A"},

		{{'9', 'A'}, "vvvA"},
		{{'9', '0'}, "<vvvA"},
		{{'9', '1'}, "<<vvA"},
		{{'9', '2'}, "vv<A"},
		{{'9', '3'}, "vvA"},
		{{'9', '4'}, "v<<A"},
		{{'9', '5'}, "v<A"},
		{{'9', '6'}, "vA"},
		{{'9', '7'}, "<<A"},
		{{'9', '8'}, "<A"},
		{{'9', '9'}, "A"},
	};

	const std::map<std::pair<char, char>, std::string> controllerKeypad
	{
		{{'A', 'A'}, "A"},
		{{'A', '^'}, "<A"},
		{{'A', '>'}, "vA"},
		{{'A', 'v'}, "<vA"},
		{{'A', '<'}, "v<<A"},

		{{'^', 'A'}, ">A"},
		{{'^', '^'}, "A"},
		{{'^', '>'}, "v>A"},
		{{'^', 'v'}, "vA"},
		{{'^', '<'}, "v<A"},

		{{'>', 'A'}, "^A"},
		{{'>', '^'}, "<^A"},
		{{'>', '>'}, "A"},
		{{'>', 'v'}, "<A"},
		{{'>', '<'}, "<<A"},

		{{'v', 'A'}, ">^A"},
		{{'v', '^'}, "^A"},
		{{'v', '>'}, ">A"},
		{{'v', 'v'}, "A"},
		{{'v', '<'}, "<A"},

		{{'<', 'A'}, ">>^A"},
		{{'<', '^'}, ">^A"},
		{{'<', '>'}, ">>A"},
		{{'<', 'v'}, ">A"},
		{{'<', '<'}, "A"},
	};

	auto instructionalize = [](const std::string& keyPresses)->std::vector<std::pair<char, char>>
		{
			return std::views::zip(
				std::views::all(keyPresses) | std::views::take(keyPresses.size() - 1),
				std::views::all(keyPresses) | std::views::drop(1))
				| std::ranges::to<std::vector<std::pair<char, char>>>();
		};

	std::uint64_t complexity = 0;

	for (const std::string& code : input)
	{
		std::stringstream bot1;
		for (const auto& inst : instructionalize( "A" + code))
		{
			bot1 << doorKeypad.at(inst);
		}

		std::stringstream bot2;
		for (const auto& inst : instructionalize("A" + bot1.str()))
		{
			bot2 << controllerKeypad.at(inst);
		}

		std::stringstream bot3;
		for (const auto& inst : instructionalize("A" + bot2.str()))
		{
			bot3 << controllerKeypad.at(inst);
		}

		std::cout << bot3.str() << "\n"
			<< bot2.str() << "\n"
			<< bot1.str() << "\n"
			<< code << "\n\n";

		std::uint64_t codeVal = std::stoull(code.substr(0, 3));
		complexity += codeVal * bot3.str().size();
	}

	utils::PrintResult(complexity, startTime);

	//Part 2

	complexity = 0;

	for (const std::string& code : input)
	{
		std::stringstream bot1;
		for (const auto& inst : instructionalize("A" + code))
		{
			bot1 << doorKeypad.at(inst);
		}

		std::string botn = bot1.str();
		for (int n = 0; n < 25; n++)
		{
			std::stringstream botStrm;
			for (const auto& inst : instructionalize("A" + botn))
			{
				botStrm << controllerKeypad.at(inst);
			}
			botn = botStrm.str();
		}
		
		std::uint64_t codeVal = std::stoull(code.substr(0, 3));
		complexity += codeVal * botn.size();
	}

	utils::PrintResult(complexity, startTime);

	return 0;
}
