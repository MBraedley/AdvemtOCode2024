// Day06.cpp : Source file for your target.
//

#include "Day06.h"
#include "Utils.h"

#include <thread>
#include <future>
#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::set<utils::Pos> obstacles;
	utils::Pos guard;

	std::ifstream inStrm("../Day06_input.txt");
//	std::stringstream inStrm(
//R"(....#.....
//.........#
//..........
//..#.......
//.......#..
//..........
//.#..^.....
//........#.
//#.........
//......#...)" );
	std::string line;

	std::size_t row = 0;
	std::size_t col = 0;

	while (std::getline(inStrm, line))
	{
		for (col = 0; col < line.size(); col++)
		{
			if (line[col] == '#')
			{
				obstacles.emplace( static_cast<int>(col), static_cast<int>(row) );
			}
			else if (line[col] == '^')
			{
				guard.X = col;
				guard.Y = row;
			}
		}
		row++;
	}

	utils::Pos startPos = guard;

	utils::Pos dir(0, -1);

	auto turnRight = [&]()
		{
			std::swap(dir.X, dir.Y);
			dir.X *= -1;
		};

	std::set<utils::Pos> visited;

	auto onMap = [&]() -> bool
		{
			return guard.X >= 0 && guard.X < col && guard.Y >= 0 && guard.Y < row;
		};

	while (onMap())
	{
		if (!obstacles.contains(guard + dir))
		{
			visited.insert(guard);
			guard = guard + dir;
		}
		else
		{
			turnRight();
		}
	}

	utils::PrintResult(visited.size(), startTime);

	//Part 2

	auto doesLoop = [
		start = startPos,
		col = col,
		row = row]
		(std::set<utils::Pos> obs) -> bool
		{
			utils::Pos guard2 = start;
			utils::Pos dir2(0, -1);
			std::set<std::pair<utils::Pos, utils::Pos>> corners;

			while (guard2.X >= 0 && guard2.X < col && guard2.Y >= 0 && guard2.Y < row)
			{
				if (!obs.contains(guard2 + dir2))
				{
					guard2 = guard2 + dir2;
				}
				else if (corners.contains(std::make_pair(guard2, dir2)))
				{
					return true;
				}
				else
				{
					corners.insert(std::make_pair(guard2, dir2));
					std::swap(dir2.X, dir2.Y);
					dir2.X *= -1;
				}
			}
			return false;
		};

	std::vector<std::future<bool>> tests;
	tests.reserve(visited.size());

	std::size_t loopPoints = 0;
	for (auto p : visited)
	{
		if (p != startPos)
		{
			auto testObs = obstacles;
			testObs.insert(p);

			tests.emplace_back(std::async(doesLoop, testObs));
		}
	}

	for (auto& fut : tests)
	{
		if (fut.get())
		{
			loopPoints++;
		}
	}

	utils::PrintResult(loopPoints, startTime);

	return 0;
}
