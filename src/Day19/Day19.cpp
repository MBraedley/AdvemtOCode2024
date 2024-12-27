// Day19.cpp : Source file for your target.
//

#include "Day19.h"
#include "Utils.h"

#include <ranges>
#include <functional>

int main()
{
	using std::operator""sv;
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day19_input.txt" );

	auto unsortedPatterns = input[0]
		| std::views::split( ", "sv )
		| std::ranges::to<std::vector<std::string>>();
	std::sort( unsortedPatterns.begin(), unsortedPatterns.end() );

	std::multimap<char, std::string> subPatterns = unsortedPatterns
		| std::views::transform( []( const std::string& s ) { return std::make_pair( s[0], s ); })
		| std::ranges::to<std::multimap<char, std::string>>();

	std::map<std::string, std::uint64_t> towels = std::views::zip(
		input | std::views::drop( 2 ),
		std::views::repeat( 0, input.size() - 2 ) )
		| std::ranges::to<std::map<std::string, std::uint64_t>>();

	std::map<std::string, std::uint64_t> memoPad;

	std::function<std::uint64_t( const std::string_view, std::map<std::string, std::uint64_t>& )> findPattern;
	findPattern = [&]( const std::string_view tStack, std::map<std::string, std::uint64_t>& memoPad ) -> std::uint64_t
		{
			if (memoPad.contains(tStack.data()))
			{
				return memoPad[tStack.data()];
			}

			std::uint64_t count = 0;
			const auto [begin, end] = subPatterns.equal_range( tStack[0] );
			for( auto iter = begin; iter != end; iter++ )
			{
				if( tStack == iter->second )
				{
					count++;
				}
				else if( tStack.starts_with( iter->second ) )
				{
					count += findPattern(tStack.data() + iter->second.size(), memoPad);
				}
			}

			memoPad[tStack.data()] = count;
			return count;
		};

	for( auto& [towel, count] : towels )
	{
		count = findPattern( towel, memoPad );
	}

	std::uint64_t anyMatch = std::count_if( towels.begin(), towels.end(), []( const std::pair<std::string, std::uint64_t>& t ) { return t.second > 0; } );
	utils::PrintResult( anyMatch, startTime );

	//Part 2
	std::uint64_t allMatch = std::ranges::fold_left( std::views::values( towels ), 0, std::plus() );
	utils::PrintResult( allMatch, startTime );

	return 0;
}
