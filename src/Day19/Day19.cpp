// Day19.cpp : Source file for your target.
//

#include "Day19.h"
#include "Utils.h"

#include <ranges>
#include <functional>
//#include <regex>	//bleh, I really want to do this with ctre

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

	std::map<std::string, std::uint32_t> towels = std::views::zip(
		input | std::views::drop( 2 ),
		std::views::repeat( 0, input.size() - 2 ) )
		| std::ranges::to<std::map<std::string, std::uint32_t>>();

	std::function<std::uint32_t( const std::string_view )> findPattern;
	findPattern = [&]( const std::string_view tStack ) -> std::uint32_t
		{
			std::uint32_t count = 0;
			const auto [begin, end] = subPatterns.equal_range( tStack[0] );
			for( auto iter = begin; iter != end; iter++ )
			{
				if( tStack == iter->second )
				{
					count++;
				}
				else if( tStack.starts_with( iter->second ) )
				{
					count += findPattern(tStack.data() + iter->second.size());
				}
			}

			return count;
		};

	for( auto& [towel, count] : towels )
	{
		count = findPattern( towel );
	}

	std::uint32_t anyMatch = std::count_if( towels.begin(), towels.end(), []( const std::pair<std::string, std::uint32_t>& t ) { return t.second > 0; } );
	utils::PrintResult( anyMatch, startTime );

	//Part 2
	std::uint32_t allMatch = std::ranges::fold_left( std::views::values( towels ), 0, std::plus() );
	utils::PrintResult( allMatch, startTime );

	//std::string towelsRegex = "(" + (input[0] | std::views::split( ", "sv ) | std::views::join_with( "|"sv ) | std::ranges::to<std::string>()) + ")+";

	//std::regex re( towelsRegex );

	//std::uint32_t validCount = 0;

	//for( const auto& t : towels )
	//{
	//	try
	//	{
	//		if( std::regex_match( t, re ) )
	//		{
	//			validCount++;
	//		}
	//	}
	//	catch( std::regex_error e )
	//	{
	//		std::cout << e.what() << "\n";
	//	}
	//}

	//utils::PrintResult( validCount, startTime );

	return 0;
}
