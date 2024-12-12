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

	const utils::Pos dirTopLeft( -1, -1 );
	const utils::Pos dirTop( 0, -1 );
	const utils::Pos dirTopRight( 1, -1 );
	const utils::Pos dirRight( 1, 0 );
	const utils::Pos dirBottomRight( 1, 1 );
	const utils::Pos dirBottom( 0, 1 );
	const utils::Pos dirBottomLeft( -1, 1 );
	const utils::Pos dirLeft( -1, 0 );

	for( auto region : regions )
	{
		std::uint64_t corners = 0;

		for( const auto& p : region )
		{
			bool tl = region.contains( p + dirTopLeft );
			bool t = region.contains( p + dirTop );
			bool tr = region.contains( p + dirTopRight );
			bool r = region.contains( p + dirRight );
			bool br = region.contains( p + dirBottomRight );
			bool b = region.contains( p + dirBottom );
			bool bl = region.contains( p + dirBottomLeft );
			bool l = region.contains( p + dirLeft );

			if( !l && !t )
			{
				corners++;
			}
			else if( l && t && !tl )
			{
				corners++;
			}

			if( !r && !t )
			{
				corners++;
			}
			else if( r && t && !tr )
			{
				corners++;
			}

			if( !l && !b )
			{
				corners++;
			}
			else if( l && b && !bl )
			{
				corners++;
			}

			if( !r && !b )
			{
				corners++;
			}
			else if( r && b && !br )
			{
				corners++;
			}
		}

		totalCost += corners * region.size();
	}

	utils::PrintResult( totalCost, startTime );

	return 0;
}
