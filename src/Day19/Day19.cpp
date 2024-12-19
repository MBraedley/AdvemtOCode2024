// Day19.cpp : Source file for your target.
//

#include "Day19.h"
#include "Utils.h"

#include <ranges>
#include <regex>	//bleh, I really want to do this with ctre

int main()
{
	using std::operator""sv;
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day19_input.txt" );

	std::string towelsRegex = "(" + (input[0] | std::views::split( ", "sv ) | std::views::join_with( "|"sv ) | std::ranges::to<std::string>()) + ")+";

	std::regex re( towelsRegex );

	std::vector<std::string> towels = input | std::views::drop( 2 ) | std::ranges::to<std::vector<std::string>>();
	std::uint32_t validCount = 0;

	for( const auto& t : towels )
	{
		try
		{
			if( std::regex_match( t, re ) )
			{
				validCount++;
			}
		}
		catch( std::regex_error e )
		{
			std::cout << e.what() << "\n";
		}
	}

	utils::PrintResult( validCount, startTime );

	return 0;
}
