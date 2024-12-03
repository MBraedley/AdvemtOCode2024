// Day03.cpp : Source file for your target.
//

#include "Day03.h"
#include "Utils.h"

#include <cassert>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	constexpr ctll::fixed_string regex{ R"(mul\((\d{1,3}),(\d{1,3})\))" };

	auto input = utils::ReadInput( "../Day03_input.txt" );

	std::uint64_t sum = 0;
	for( const std::string& line : input )
	{
		for( auto re : ctre::range<regex>( line ) )
		{
			sum += re.get<1>().to_number() * re.get<2>().to_number();
		}
	}

	utils::PrintResult( sum, startTime );

	//Part 2
	sum = 0;

	constexpr ctll::fixed_string regex2{ R"(do\(\)|don't\(\)|mul\(\d{1,3},\d{1,3}\))" };
	bool isDo = true;
	for( const std::string& line : input )
	{
		for( auto re : ctre::range<regex2>( line ) )
		{
			std::string inst = re.get<0>().str();
			if( inst == "do()" )
			{
				isDo = true;
			}
			else if( inst == "don't()" )
			{
				isDo = false;
			}
			else if( isDo && inst.starts_with( "mul" ) )
			{
				if( auto re2 = ctre::match<regex>( inst ); re2 )
				{
					sum += re2.get<1>().to_number( 10 ) * re2.get<2>().to_number( 10 );
				}
			}
		}
	}

	utils::PrintResult( sum, startTime );

	return 0;
}
