// Day16.cpp : Source file for your target.
//

#include "Day16.h"
#include "Utils.h"

#include <queue>
#include <stack>
#include <ranges>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day16_input.txt" );

	using positionCost = std::tuple<utils::Pos, utils::Pos, std::size_t>;

	auto costComp = []( const positionCost& lhs, const positionCost& rhs ) -> bool { return std::get<std::size_t>( lhs ) > std::get<std::size_t>( rhs ); };
	std::priority_queue<positionCost, std::vector<positionCost>, decltype(costComp)> moveQueue( costComp );

	std::map<std::pair<utils::Pos, utils::Pos>, std::size_t> positionCosts;

	std::size_t height = input.size();
	std::size_t width = input[0].size();

	utils::Pos startPos( 1, height - 2 );
	utils::Pos endPos( width - 2, 1 );

	assert( input[startPos.Y][startPos.X] == 'S' );
	assert( input[endPos.Y][endPos.X] == 'E' );

	//utils::Pos pos = startPos;
	//utils::Pos dir( 1, 0 );

	auto turnRight = [&]( utils::Pos dir ) -> utils::Pos
		{
			std::swap( dir.X, dir.Y );
			dir.X *= -1;
			return dir;
		};

	auto turnLeft = [&]( utils::Pos dir ) -> utils::Pos
		{
			std::swap( dir.X, dir.Y );
			dir.Y *= -1;
			return dir;
		};

	auto addToQueue = [&]( const positionCost& currentPos )
		{
			const auto& [pos, dir, cost] = currentPos;
			auto takeStep = pos + dir;
			if( input[takeStep.Y][takeStep.X] != '#' )
			{
				moveQueue.push( { takeStep, dir, cost + 1 } );
			}

			auto lhs = turnLeft( dir );
			takeStep = pos + lhs;
			if( input[takeStep.Y][takeStep.X] != '#' )
			{
				moveQueue.push( { pos, lhs, cost + 1000 } );
			}

			auto rhs = turnRight( dir );
			takeStep = pos + rhs;
			if( input[takeStep.Y][takeStep.X] != '#' )
			{
				moveQueue.push( { pos, rhs, cost + 1000 } );
			}
		};

	addToQueue( { startPos, utils::Pos( 1, 0 ), 0 } );

	while( !moveQueue.empty() )
	{
		auto [p, d, c] = moveQueue.top();
		moveQueue.pop();

		if( !positionCosts.contains( std::make_pair( p, d ) ) )
		{
			positionCosts.emplace( std::make_pair( p, d ), c );
			addToQueue( { p, d, c } );
		}
		else if ( c < positionCosts[std::make_pair(p, d)] )
		{
			positionCosts[std::make_pair( p, d )] = c;
			addToQueue( { p, d, c } );
		}
	}

	auto endPosVals = std::views::values( std::views::all( positionCosts ) | std::views::filter( [&]( const std::pair<std::pair<utils::Pos, utils::Pos>, std::size_t>& p ) { return p.first.first == endPos; } ) );

	std::ranges::for_each( endPosVals, [&]( const std::size_t& val )
		{
			utils::PrintResult( val, startTime );
		} );

	//Part 2

	std::set<utils::Pos> goodStands;

	std::stack<std::queue<utils::Pos>> fastestRoutes;
	fastestRoutes.push( std::queue<utils::Pos>{} );

	addToQueue( { startPos, utils::Pos( 1, 0 ), 0 } );

	while( !moveQueue.empty() )
	{
		auto [p, d, c] = moveQueue.top();
		moveQueue.pop();

		assert( positionCosts.contains( std::make_pair( p, d ) ) );

		if( positionCosts[std::make_pair( p, d )] == c )
		{
			for( const auto& n : p.GetNeighbours( input, false ) )
			{
				if( input[n.Y][n.X] == '#' )
				{
					goodStands.insert( n );
				}
			}

			addToQueue( { p,d,c } );
		}
	}

	utils::PrintResult( goodStands.size(), startTime );

	return 0;
}
