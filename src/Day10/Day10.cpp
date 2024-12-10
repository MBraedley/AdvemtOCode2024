// Day10.cpp : Source file for your target.
//

#include "Day10.h"
#include "Utils.h"

#include <stack>
#include <ranges>
#include <functional>

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
			return std::views::keys(
				std::views::all( map )
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
					} ) )
				| std::ranges::to<std::set<utils::Pos>>();
		};

	auto trailHeads = std::views::keys( std::views::all( map )
		| std::views::filter( []( const std::pair<utils::Pos, std::int8_t>& pos ) -> bool { return pos.second == 0; } ) );

	std::uint32_t totalScore = 0;

	for( const auto& head : trailHeads )
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

	//Part 2

	std::uint32_t totalRating = 0;

	std::function<void( std::stack<utils::Pos>& )> findTrail;
	findTrail = [&]( std::stack<utils::Pos>& trail )
		{
			std::set<utils::Pos> points;
			points.insert( trail.top() );
			points = getNextStep( points, trail.size() );

			if( trail.size() == 9 )
			{
				totalRating += points.size();
			}
			else
			{
				for( const auto& p : points )
				{
					trail.push( p );
					findTrail( trail );
					trail.pop();
				}
			}
		};

	for( const auto& head : trailHeads )
	{
		std::stack<utils::Pos> trail;
		trail.push( head );

		findTrail( trail );
	}

	utils::PrintResult( totalRating, startTime );

	return 0;
}
