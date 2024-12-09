// Day09.cpp : Source file for your target.
//

#include "Day09.h"
#include "Utils.h"

#include <optional>
#include <deque>
#include <list>
#include <ranges>
#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::string inStr = utils::ReadInput( "../Day09_input.txt" )[0] + "0"; //"23331331214141314020";
	auto input = std::views::all( inStr )
		| std::views::transform( []( const char& c ) -> std::uint8_t { return c - '0'; } );
	
	assert( input.size() % 2 == 0 );

	//Part 1
	{
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

	//Part 2
	{
		auto files = std::views::zip(
			std::views::iota( 0 ) | std::views::transform( []( const auto& i ) -> std::optional<std::uint32_t> { return std::optional<std::uint32_t>( i ); } ),
			input | std::views::stride( 2 ),
			input | std::views::drop( 1 ) | std::views::stride( 2 ) );

		std::list<std::pair<std::optional<std::uint32_t>, std::uint8_t>> hdd;

		for( auto [fid, fs, freeSpace] : files )
		{
			hdd.emplace_back( fid, fs );
			hdd.emplace_back( std::nullopt, freeSpace );
		}

		hdd.pop_back();	//pop off the 0 size free space block

		assert( hdd.back().first.has_value() );

		auto fileId = hdd.back().first.value();

		for( auto id = fileId; id > 0; id-- )
		{
			auto moveBlock = std::find_if( hdd.begin(), hdd.end(), [&]( const std::pair<std::optional<std::uint32_t>, std::uint8_t>& val ) { return val.first.has_value() && val.first.value() == id; } );

			assert( moveBlock != hdd.end() );

			for( auto iter = hdd.begin(); iter != moveBlock; iter++ )
			{
				if( !iter->first.has_value() && iter->second >= moveBlock->second )
				{
					auto copiedBlock = *moveBlock;
					moveBlock->first = std::nullopt;
					iter->second -= copiedBlock.second;
					hdd.insert( iter, copiedBlock );

					break;
				}
			}
		}

		auto defragged = std::views::zip(
			std::views::iota( 0 ),
			std::views::all( hdd ) | std::views::transform( []( const auto& fileBlock ) { return std::views::repeat( fileBlock.first, fileBlock.second ); } ) | std::views::join );

		std::uint64_t checksum = 0;

		for( const auto&[index, fileId] : defragged )
		{
			if( fileId.has_value() )
			{
				checksum += index * fileId.value();
			}
		}

		utils::PrintResult( checksum, startTime );
	}

	return 0;
}
