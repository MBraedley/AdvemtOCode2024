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

	positionCosts.emplace(std::make_pair(startPos, utils::Pos(1, 0)), 0);
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

	auto endPosVals = std::views::all(positionCosts)
		| std::views::filter([&](const std::pair<std::pair<utils::Pos, utils::Pos>, std::size_t>& p) { return p.first.first == endPos; })
		| std::ranges::to<std::vector<std::pair<std::pair<utils::Pos, utils::Pos>, std::size_t>>>();

	auto bestEnd = *std::min_element(endPosVals.begin(), endPosVals.end(), [](const auto& lhs, const auto& rhs) {return lhs.second < rhs.second; });

	utils::PrintResult( bestEnd.second, startTime);

	//for (const auto& [pd, c] : endPosVals)
	//{
	//	std::cout << pd.second << ": " << c << "\n";
	//}

	//Part 2

	std::set<utils::Pos> onPath;
	std::queue<positionCost> pathFinding;

	auto addToQueue2 = [&](const positionCost& currentPos)
		{
			const auto& [pos, dir, cost] = currentPos;
			auto takeStep = pos - dir;
			if (input[takeStep.Y][takeStep.X] != '#')
			{
				pathFinding.push({ takeStep, dir, cost - 1 });
			}

			auto lhs = turnLeft(dir);
			takeStep = pos - lhs;
			if (input[takeStep.Y][takeStep.X] != '#')
			{
				pathFinding.push({ pos, lhs, cost - 1000 });
			}

			auto rhs = turnRight(dir);
			takeStep = pos - rhs;
			if (input[takeStep.Y][takeStep.X] != '#')
			{
				pathFinding.push({ pos, rhs, cost - 1000 });
			}
		};

	onPath.insert(bestEnd.first.first);
	addToQueue2({ bestEnd.first.first, bestEnd.first.second, bestEnd.second });

	while (!pathFinding.empty())
	{
		auto [p, d, c] = pathFinding.front();
		pathFinding.pop();

		if (positionCosts.contains(std::make_pair(p, d)) && positionCosts[std::make_pair(p, d)] == c)
		{
			onPath.emplace(p);
			addToQueue2({ p, d, c });
		}
	}

	utils::PrintResult(onPath.size(), startTime);

	return 0;
}
