// Day10.cpp : Source file for your target.
//

#include "Day10.h"
#include "Utils.h"

#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day10_input.txt" );

	std::map<utils::Pos, std::int8_t> map;
	
	for( int y = 0; y < input.size(); y++ )
	{
		for( int x = 0; x < input[y].size(); x++ )
		{
			map.emplace( utils::Pos{ x, y }, input[y][x] - '0' );
		}
	}

	auto getNextStep = [&]( const std::set<utils::Pos>& points, std::int8_t nextVal ) -> std::set<utils::Pos>
		{
			auto neighbours = std::views::all( map )
				| std::views::filter( [nextVal]( const std::pair<utils::Pos, std::int8_t>& pos ) -> bool
					{
						return pos.second == nextVal;
					} )
				| std::views::filter( [&]( const std::pair<utils::Pos, std::int8_t>& pos ) -> bool
					{
						for( const auto& p : points )
						{
							if( p.GetManDistance( pos.first ) == 1 )
							{
								return true;
							}
						}

						return false;
					} )
				| std::ranges::to<std::map<utils::Pos, std::int8_t>>();

			return std::views::keys( neighbours ) | std::ranges::to<std::set<utils::Pos>>();
		};

	auto trailHeads = std::views::all( map )
		| std::views::filter( []( const std::pair<utils::Pos, std::int8_t>& pos ) -> bool { return pos.second == 0; } )
		| std::ranges::to<std::map<utils::Pos, std::int8_t>>();

	std::uint32_t totalScore = 0;

	for( const auto& [head, _] : trailHeads )
	{
		std::set<utils::Pos> points;
		points.insert( head );
		for( std::int8_t i = 1; i <= 9; i++ )
		{
			if( !points.empty() )
			{
				points = getNextStep( points, i );
			}
		}

		totalScore += points.size();
	}

	utils::PrintResult( totalScore, startTime );

	return 0;
}
