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

	auto checkPrint = [&]( const std::set<int>& previousPages, int currentPage ) -> bool
		{
			if( previousPages.empty() )
			{
				return true;
			}

			for( const auto& [x, y] : rules )
			{
				if( currentPage == x && previousPages.contains( y ) )
				{
					return false;
				}
			}

			return true;
		};

	auto checkPagesInPrint = [&]( const std::vector<int>& printJob ) -> bool
		{
			std::set<int> previousPages;
			for( int page : printJob )
			{
				if( !checkPrint( previousPages, page ) )
				{
					return false;
				}
				previousPages.insert( page );
			}
			return true;
		};

	int sum = 0;
	std::vector<std::vector<int>> badJobs;
	for( const auto& printJob : prints )
	{
		if( checkPagesInPrint( printJob ) )
		{
			assert( printJob.size() % 2 == 1 );
			sum += printJob[printJob.size() / 2];
		}
		else
		{
			badJobs.emplace_back( printJob );
		}
	}

	utils::PrintResult( sum, startTime );

	//Part2

	auto printOrderLess = [&]( const int& lhs, const int& rhs ) -> bool
		{
			for( const auto& [x, y] : rules )
			{
				if( lhs == x && rhs == y )
				{
					return true;
				}
			}

			return false;
		};

	sum = 0;
	for( auto job : badJobs )
	{
		std::sort( job.begin(), job.end(), printOrderLess );
		assert( checkPagesInPrint( job ) );
		assert( job.size() % 2 == 1 );
		sum += job[job.size() / 2];
	}

	utils::PrintResult( sum, startTime );

	return 0;
}
