// Day04.cpp : Source file for your target.
//

#include "Day04.h"
#include "Utils.h"

#include <array>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day04_input.txt" );

	auto withinGrid = [&]( const utils::Pos& pos ) -> bool
		{
			return pos.Y >= 0 && pos.Y < input.size() && pos.X >= 0 && pos.X < input[pos.Y].size();
		};

	auto checkForXmas = [&]( const utils::Pos& startPos, const utils::Pos& direction ) -> bool
		{
			auto XPos = startPos;
			auto MPos = XPos + direction;
			auto APos = MPos + direction;
			auto SPos = APos + direction;

			return withinGrid( XPos ) && input[XPos.Y][XPos.X] == 'X'
				&& withinGrid( MPos ) && input[MPos.Y][MPos.X] == 'M'
				&& withinGrid( APos ) && input[APos.Y][APos.X] == 'A'
				&& withinGrid( SPos ) && input[SPos.Y][SPos.X] == 'S';
		};

	constexpr std::array<utils::Pos, 8> directions =
	{
		utils::Pos{0, 1},
		utils::Pos{1, 1},
		utils::Pos{1, 0},
		utils::Pos{1, -1},
		utils::Pos{0, -1},
		utils::Pos{-1, -1},
		utils::Pos{-1, 0},
		utils::Pos{-1, 1}
	};

	std::size_t count = 0;

	for( std::size_t y = 0; y < input.size(); y++ )
	{
		for( std::size_t x = 0; x < input[y].size(); x++ )
		{
			for( const auto& dir : directions )
			{
				if( checkForXmas( utils::Pos( x, y ), dir ) )
				{
					count++;
				}
			}
		}
	}

	utils::PrintResult( count, startTime );

	//Part 2
	utils::Pos topLeft( -1, -1 );
	utils::Pos topRight( 1, -1 );
	utils::Pos bottomLeft( -1, 1 );
	utils::Pos bottomRight( 1, 1 );

	auto checkForX_MAS = [&]( const utils::Pos& startPos ) -> bool
		{
			if( withinGrid( startPos ) && input[startPos.Y][startPos.X] == 'A'
				&& withinGrid(startPos + topLeft)
				&& withinGrid(startPos + topRight)
				&& withinGrid(startPos + bottomLeft)
				&& withinGrid(startPos + bottomRight) )
			{
				auto tl = startPos + topLeft;
				auto tr = startPos + topRight;
				auto bl = startPos + bottomLeft;
				auto br = startPos + bottomRight;
				return
					((input[tl.Y][tl.X] == 'M' && input[br.Y][br.X] == 'S') || (input[tl.Y][tl.X] == 'S' && input[br.Y][br.X] == 'M')) &&
					((input[tr.Y][tr.X] == 'M' && input[bl.Y][bl.X] == 'S') || (input[tr.Y][tr.X] == 'S' && input[bl.Y][bl.X] == 'M'));
			}
			else
			{
				return false;
			}
		};

	count = 0;

	for( std::size_t y = 0; y < input.size(); y++ )
	{
		for( std::size_t x = 0; x < input[y].size(); x++ )
		{
			if( checkForX_MAS( utils::Pos( x, y ) ) )
			{
				count++;
			}
		}
	}

	utils::PrintResult( count, startTime );

	return 0;
}
