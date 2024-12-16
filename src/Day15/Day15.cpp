// Day15.cpp : Source file for your target.
//

#include "Day15.h"
#include "Utils.h"

#include <ranges>
#include <functional>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput("../Day15_input.txt");
	//std::vector<std::string> input
	//{
	//	"##########",
	//	"#..O..O.O#",
	//	"#......O.#",
	//	"#.OO..O.O#",
	//	"#..O@..O.#",
	//	"#O#..O...#",
	//	"#O..O..O.#",
	//	"#.OO.O.OO#",
	//	"#....O...#",
	//	"##########",
	//	"",
	//	"<vv>^<v^>v>^vv^v>v<>v^v<v<^vv<<<^><<><>>v<vvv<>^v^>^<<<><<v<<<v^vv^v>^",
	//	"vvv<<^>^v^^><<>>><>^<<><^vv^^<>vvv<>><^^v>^>vv<>v<<<<v<^v>^<^^>>>^<v<v",
	//	"><>vv>v^v^<>><>>>><^^>vv>v<^^^>>v^v^<^^>v^^>v^<^v>v<>>v^v^<v>v^^<^^vv<",
	//	"<<v<^>>^^^^>>>v^<>vvv^><v<<<>^^^vv^<vvv>^>v<^^^^v<>^>vvvv><>>v^<<^^^^^",
	//	"^><^><>>><>^^<<^^v>>><^<v>^<vv>>v>>>^v><>^v><<<<v>>v<v<v>vvv>^<><<>^><",
	//	"^>><>^v<><^vvv<^^<><v<<<<<><^v<<<><<<^^<v<^^^><^>>^<v^><<<^>>^v<v^v<v^",
	//	">^>>^v>vv>^<<^v<>><<><<v<<v><>v<^vv<<<>^^v^>^^>>><<^v>>v^v><^^>>^<>vv^",
	//	"<><^^>^^^<><vvvvv^v<v<<>^v<v>v<<^><<><<><<<^^<<<^<<>><<><^^^>^^<>^>v<>",
	//	"^^>vv<^v^v<vv>^<><v<^v>^^^>>>^^vvv^>vvv<>>>^<^>>>>>^<<^v>^vvv<>^<><<v>",
	//	"v^^>>><<^^<>>^v^<v^vv<>v^<<>^<^v^v><^<<<><<^<v><v<>vv>>v><v^<vv<>v^<<^",
	//};

	std::vector<std::string> warehouse = std::views::all(input) | std::views::take_while([](const std::string& line) {return !line.empty(); }) | std::ranges::to<std::vector<std::string>>();
	std::string instructions = std::views::join(std::views::all(input) | std::views::drop(warehouse.size() + 1)) | std::ranges::to<std::string>();

	std::set<utils::Pos> walls;
	std::set<utils::Pos> boxes;
	utils::Pos robot;

	for (int y = 0; y < warehouse.size(); y++)
	{
		for (int x = 0; x < warehouse[y].size(); x++)
		{
			if (warehouse[y][x] == '#')
			{
				walls.emplace(x, y);
			}
			else if (warehouse[y][x] == 'O')
			{
				boxes.emplace(x, y);
			}
			else if (warehouse[y][x] == '@')
			{
				robot.X = x;
				robot.Y = y;
			}
		}
	}

	std::function<void(utils::Pos, utils::Pos)> tryPush;
	tryPush = [&](utils::Pos pushPoint, utils::Pos dir)
		{
			if (walls.contains(pushPoint + dir))
			{
				return;
			}
			else if (boxes.contains(pushPoint + dir))
			{
				tryPush(pushPoint + dir, dir);
			}
			else
			{
				boxes.emplace(pushPoint + dir);
				robot = robot + dir;
				boxes.erase(robot);
			}
		};

	const std::map<char, utils::Pos> dirs
	{
		{'^', {0, -1}},
		{'v', {0, 1}},
		{'<', {-1, 0}},
		{'>', {1, 0}},
	};

	auto printGrid = [&]()
		{
			auto grid = std::views::repeat(std::views::repeat('.', warehouse[0].size()), warehouse.size()) | std::ranges::to<std::vector<std::string>>();
			for (const auto& wall : walls)
			{
				grid[wall.Y][wall.X] = '#';
			}

			for (const auto& box : boxes)
			{
				grid[box.Y][box.X] = 'O';
			}

			grid[robot.Y][robot.X] = '@';

			utils::PrintGrid(grid);
			std::cout << "\n\n";
		};

	for (char dir : instructions)
	{
		if (!walls.contains(robot + dirs.at(dir)) && !boxes.contains(robot + dirs.at(dir)))
		{
			robot = robot + dirs.at(dir);
		}
		else
		{
			tryPush(robot, dirs.at(dir));
		}

		//printGrid();
	}

	std::uint32_t gpsCoords = std::ranges::fold_left(std::views::all(boxes) | std::views::transform([](const utils::Pos& p) { return p.X + p.Y * 100; }), 0, std::plus<std::uint32_t>());

	utils::PrintResult(gpsCoords, startTime);

	//Part 2

	return 0;
}
