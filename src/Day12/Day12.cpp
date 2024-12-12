// Day12.cpp : Source file for your target.
//

#include "Day12.h"
#include "Utils.h"

#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day12_input.txt" );
	//std::vector<std::string> input{
	//	"AAAAAA",
	//	"AAABBA",
	//	"AAABBA",
	//	"ABBAAA",
	//	"ABBAAA",
	//	"AAAAAA",
	//};

	std::map<utils::Pos, char> map;

	for( int y = 0; y < input.size(); y++ )
	{
		for( int x = 0; x < input[y].size(); x++ )
		{
			map.emplace( utils::Pos{ x, y }, input[y][x] );
		}
	}

	std::map<utils::Pos, char> backup = map;
	std::vector<std::set<utils::Pos>> regions;

	while( !map.empty() )
	{
		auto [plot, name] = *map.begin();
		map.erase( plot );

		std::set<utils::Pos> region;

		region.insert( plot );

		std::queue<utils::Pos> nextPlots;

		auto flood = [&]( const utils::Pos& p )
			{
				auto possibleNeighbours = p.GetNeighbours( input, false );
				for( auto neighbour : possibleNeighbours )
				{
					if( map.contains( neighbour ) && map[neighbour] == name )
					{
						nextPlots.push( neighbour );
						map.erase( neighbour );
					}
				}
			};

		flood( plot );

		while( !nextPlots.empty() )
		{
			region.insert( nextPlots.front() );
			flood( nextPlots.front() );
			nextPlots.pop();
		}

		regions.push_back( region );
	}

	std::size_t totalCost = 0;

	for( auto region : regions )
	{
		std::size_t fenceCount = 0;
		std::size_t area = region.size();

		for( auto plot : region )
		{
			auto neighbours = plot.GetUnboundedNeighbours( false );
			for( auto neighbour : neighbours )
			{
				if( !region.contains( neighbour ) )
				{
					fenceCount++;
				}
			}
		}

		totalCost += area * fenceCount;
	}

	utils::PrintResult( totalCost, startTime );

	//Part 2

	totalCost = 0;
	for( auto region : regions )
	{
		auto start = *region.begin();	//Due to sorting, this is guarenteed to be where there's a fence corner in the top left

		//Use left hand rule for solving a maze to map the perimeter.  Every time we make a turn, we have a new side.
		utils::Pos facing( 1, 0 );
		utils::Pos leftHand( 0, -1 );
		std::size_t corners = 0;

		bool isExterior = false;
		std::set<char> borderTypes;

		auto turnRight = [&]()
			{
				std::swap( facing.X, facing.Y );
				facing.X *= -1;
				std::swap( leftHand.X, leftHand.Y );
				leftHand.X *= -1;
				corners++;
			};
		auto turnLeft = [&]()
			{
				std::swap( facing.X, facing.Y );
				facing.Y *= -1;
				std::swap( leftHand.X, leftHand.Y );
				leftHand.Y *= -1;
				corners++;
			};

		auto p = start;
		do
		{
			if( !isExterior && !backup.contains( p + leftHand ) )
			{
				isExterior = true;
			}

			if( !isExterior && !region.contains( p + leftHand ) && backup.contains( p + leftHand ) )
			{
				borderTypes.insert( backup[p + leftHand] );
			}

			if( region.contains( p + leftHand ) )
			{
				turnLeft();
				p = p + facing;
			}
			else if( region.contains( p + facing ) )
			{
				p = p + facing;
			}
			else
			{
				turnRight();
			}
		} while( !( p == start && facing == utils::Pos(1, 0) ) );

		std::size_t fenceCost = region.size() * corners;

		if( !isExterior && borderTypes.size() == 1 )
		{
			assert( false );
		}

		totalCost += fenceCost;
	}

	utils::PrintResult( totalCost, startTime );

	return 0;
}
