// Day17.cpp : Source file for your target.
//

#include "Day17.h"
#include "Utils.h"
#include "OpcodeComputer.h"

#include <ranges>
#include <cassert>
#include <functional>

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day17_input.txt" );

	auto regMatcher = ctre::match<R"(Register [ABC]: (\d+))">;
	auto progMatcher = ctre::match<R"(Program: (.+))">;

	std::int64_t regA = regMatcher( input[0] ).get<1>().to_number<std::int64_t>();
	std::int64_t regB = regMatcher( input[1] ).get<1>().to_number<std::int64_t>();
	std::int64_t regC = regMatcher( input[2] ).get<1>().to_number<std::int64_t>();

	std::string progStr = progMatcher( input[4] ).get<1>().str();

	auto program = std::views::all( utils::Tokenize( progStr, ',' ) )
		| std::views::transform( []( const std::string& str ) -> std::uint8_t { return std::stoi( str ); } )
		| std::ranges::to<std::vector<std::uint8_t>>();

	OpcodeComputer comp( program, regA, regB, regC );

	utils::PrintResult( comp.Run(), startTime );

	//Part 2

	std::function<void( std::uint64_t )> checkVal;
	checkVal = [&]( std::uint64_t regA )
		{
			for( std::size_t j = 0; j < 8; j++ )
			{
				OpcodeComputer comp2( program, regA + j, regB, regC );
				std::string s = comp2.Run();
				if( s == progStr )
				{
					utils::PrintResult( regA + j, startTime );
					return;
				}
				else if( progStr.ends_with( s ) )
				{
					checkVal( (regA + j) << 3 );
				}

			}
		};

	checkVal( 0 );
	
	return 0;
}
