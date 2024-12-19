// Day18.cpp : Source file for your target.
//

#include "Day18.h"
#include "Utils.h"

#include <ranges>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadFormattedInput<R"((\d+),(\d+))">( "../Day18_input.txt" )
		| std::views::transform( []( const std::vector<std::string>& line ) -> utils::Pos { return utils::Pos( std::stoi( line[1] ), std::stoi( line[2] ) ); } )
		| std::ranges::to<std::deque<utils::Pos>>();

	std::set<utils::Pos> corruption;

	for( std::uint32_t i = 0; i < 1024; i++ )
	{
		assert( !corruption.contains( input.front() ) );
		corruption.emplace( input.front() );
		input.pop_front();
	}

	const utils::Pos start( 0, 0 );
	const utils::Pos end( 70, 70 );

	//Part 1
	std::map<utils::Pos, std::uint32_t> stepsTaken;
	std::deque<utils::Pos> nextSteps;

	auto inGrid = [&]( const utils::Pos& p ) -> bool
		{
			return p.X >= start.X && p.Y >= start.Y && p.X <= end.X && p.Y <= end.Y;
		};

	auto takeStep = [&]( const utils::Pos& p )
		{
			if( p == end )
			{
				return;
			}

			std::uint32_t s = stepsTaken[p] + 1;

			auto adjacents = p.GetUnboundedNeighbours( false );

			for( const auto& adjacent : adjacents )
			{
				if( inGrid( adjacent ) && !corruption.contains( adjacent ) )
				{
					if( !stepsTaken.contains( adjacent ) )
					{
						stepsTaken[adjacent] = s;
						if( adjacent == end )
						{
							nextSteps.push_front( adjacent );
						}
						else
						{
							nextSteps.push_back( adjacent );
						}
					}
					else
					{
						assert( stepsTaken[adjacent] <= s );
					}
				}
			}
		};

	stepsTaken.emplace( start, 0 );
	nextSteps.push_back( start );

	while( !nextSteps.empty() && nextSteps.front() != end )
	{
		takeStep( nextSteps.front() );
		nextSteps.pop_front();
	}

	utils::PrintResult( stepsTaken[end], startTime );

	//Part 2

	utils::Pos lastCorruption;
	while( stepsTaken[end] != 0 )
	{
		lastCorruption = input.front();
		assert( !corruption.contains( input.front() ) );
		corruption.emplace( input.front() );
		input.pop_front();

		stepsTaken.clear();
		nextSteps.clear();

		stepsTaken.emplace( start, 0 );
		nextSteps.push_back( start );

		while( !nextSteps.empty() && nextSteps.front() != end )
		{
			takeStep( nextSteps.front() );
			nextSteps.pop_front();
		}
	}

	utils::PrintResult( lastCorruption, startTime );

	return 0;
}
