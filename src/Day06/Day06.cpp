// Day06.cpp : Source file for your target.
//

#include "Day06.h"
#include "Utils.h"

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::set<utils::Pos> obstacles;
	utils::Pos guard;

	std::ifstream inStrm( "../Day06_input.txt" );
//	std::stringstream inStrm(
//		R"(....#.....
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

	while( std::getline( inStrm, line ) )
	{
		for( col = 0 ; col < line.size(); col++ )
		{
			if( line[col] == '#' )
			{
				obstacles.emplace( col, row );
			}
			else if( line[col] == '^' )
			{
				guard.X = col;
				guard.Y = row;
			}
		}
		row++;
	}

	utils::Pos dir( 0, -1 );

	auto turnRight = [&]()
		{
			std::swap( dir.X, dir.Y );
			dir.X *= -1;
		};

	std::set<utils::Pos> visited;

	auto onMap = [&]() -> bool
		{
			return guard.X >= 0 && guard.X < col && guard.Y >= 0 && guard.Y < row;
		};

	while( onMap() )
	{
		if( !obstacles.contains( guard + dir ) )
		{
			visited.insert( guard );
			guard = guard + dir;
		}
		else
		{
			turnRight();
		}
	}

	utils::PrintResult( visited.size(), startTime );

	return 0;
}
