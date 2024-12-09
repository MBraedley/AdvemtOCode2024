// Day09.cpp : Source file for your target.
//

#include "Day09.h"
#include "Utils.h"

#include <optional>
#include <deque>
#include <ranges>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::string inStr = utils::ReadInput( "../Day09_input.txt" )[0] + "0";
	auto input = std::views::all( inStr )
		| std::views::transform( []( const char& c ) -> std::uint8_t { return c - '0'; } );
	
	assert( input.size() % 2 == 0 );

	auto files = std::views::zip( input | std::views::stride( 2 ), input | std::views::drop( 1 ) | std::views::stride( 2 ) );

	std::vector<std::vector<std::optional<std::uint32_t>>> hdd;
	std::uint32_t fileId = 0;
	for( const auto& [fileSize, freeSpace] : files )
	{
		hdd.emplace_back( fileSize, fileId );
		hdd.emplace_back( freeSpace, std::nullopt );
		fileId++;
	}

	auto jv = std::views::all( hdd ) | std::views::join;

	//Part 1
	{
		std::deque<std::optional<std::uint32_t>> blocks{ jv.begin(), jv.end() };
		std::vector<std::uint32_t> collapsedBlocks;
		collapsedBlocks.reserve( blocks.size() );

		while( !blocks.empty() )
		{
			auto blockId = blocks.front();
			if( blockId.has_value() )
			{
				collapsedBlocks.push_back( *blockId );
			}
			else
			{
				while( !blocks.empty() && !blocks.back().has_value() )
				{
					blocks.pop_back();
				}

				if( !blocks.empty() )
				{
					assert( blocks.back().has_value() );
					collapsedBlocks.push_back( *blocks.back() );
					blocks.pop_back();
				}
			}

			if( !blocks.empty() )
			{
				blocks.pop_front();
			}
		}

		std::uint64_t checksum = 0;

		for( std::size_t i = 0; i < collapsedBlocks.size(); i++ )
		{
			checksum += collapsedBlocks[i] * i;
		}

		utils::PrintResult( checksum, startTime );
	}

	return 0;
}
