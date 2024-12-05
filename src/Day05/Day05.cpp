// Day05.cpp : Source file for your target.
//

#include "Day05.h"
#include "Utils.h"

#include <cassert>
#include <ranges>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	std::vector<std::pair<int, int>> rules;
	std::vector<std::vector<int>> prints;

	std::ifstream inStrm( "../Day05_input.txt" );
	std::string line;

	auto matcher = ctre::match<R"((\d+)\|(\d+))">;
	while( std::getline( inStrm, line ) && !line.empty() )
	{
		auto result = matcher( line );
		assert( result );

		rules.emplace_back( result.get<1>().to_number(), result.get<2>().to_number() );
	}

	while( std::getline( inStrm, line ) && !line.empty() )
	{
		auto tokens = utils::Tokenize( line, ',' );
		auto v = std::views::all( tokens ) | std::views::transform( []( const std::string& val ) { return std::stoi( val ); } );
		prints.emplace_back( v.begin(), v.end() );
	}


	return 0;
}
