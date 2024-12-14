// Day13.cpp : Source file for your target.
//

#include "Day13.h"
#include "Utils.h"

#include "ctre.hpp"

#include <Eigen/Dense>

#include <ranges>
#include <cassert>

struct Machine
{
	utils::Pos AButton;
	utils::Pos BButton;
	utils::Pos Prize;
};

int main()
{
	auto startTime = std::chrono::system_clock::now();

	auto input = utils::ReadInput( "../Day13_input.txt" );

	auto inputView = std::views::all( input )
		| std::views::filter( []( const std::string& line )->bool { return !line.empty(); } )
		| std::views::chunk( 3 );

	auto buttonMatcher = ctre::match<R"(Button [AB]: X\+(\d+), Y\+(\d+))">;
	auto prizeMatcher = ctre::match<R"(Prize: X=(\d+), Y=(\d+))">;

	std::vector<Machine> machines;

	for( auto machineDef : inputView )
	{
		Machine m;

		std::vector<std::string> machineDefArray = machineDef | std::ranges::to<std::vector<std::string>>();
		auto aRes = buttonMatcher( machineDefArray[0] );
		assert( aRes );
		m.AButton.X = aRes.get<1>().to_number();
		m.AButton.Y = aRes.get<2>().to_number();

		auto bRes = buttonMatcher( machineDefArray[1] );
		assert( bRes );
		m.BButton.X = bRes.get<1>().to_number();
		m.BButton.Y = bRes.get<2>().to_number();

		auto pRes = prizeMatcher( machineDefArray[2] );
		assert( pRes );
		m.Prize.X = pRes.get<1>().to_number();
		m.Prize.Y = pRes.get<2>().to_number();

		machines.push_back( m );
	}

	std::size_t totalCost = 0;

	for( const auto& m : machines )
	{
		Eigen::Matrix2d equations
		{
			{static_cast<double>(m.AButton.X), static_cast<double>(m.BButton.X)},
			{static_cast<double>(m.AButton.Y), static_cast<double>(m.BButton.Y)}
		};

		Eigen::Vector2d results{ static_cast<double>(m.Prize.X), static_cast<double>(m.Prize.Y) };

		if( equations.determinant() != 0 )
		{
			auto inverse = equations.inverse();
			auto presses = inverse * results;

			int aPresses = static_cast<int>(std::round( presses[0] ));
			int bPresses = static_cast<int>(std::round( presses[1] ));

			if( aPresses >= 0 && bPresses >= 0
				&& aPresses * m.AButton.X + bPresses * m.BButton.X == m.Prize.X
				&& aPresses * m.AButton.Y + bPresses * m.BButton.Y == m.Prize.Y )
			{
				totalCost += aPresses * 3 + bPresses;
			}
		}
	}

	utils::PrintResult( totalCost, startTime );

	//Part 2

	totalCost = 0;

	for( const auto& m : machines )
	{
		Eigen::Matrix2d equations
		{
			{static_cast<double>(m.AButton.X), static_cast<double>(m.BButton.X)},
			{static_cast<double>(m.AButton.Y), static_cast<double>(m.BButton.Y)}
		};

		Eigen::Vector2d results{ static_cast<double>(m.Prize.X + 10000000000000), static_cast<double>(m.Prize.Y + 10000000000000) };

		if( equations.determinant() != 0 )
		{
			auto inverse = equations.inverse();
			auto presses = inverse * results;

			std::uint64_t aPresses = static_cast<std::uint64_t>(std::round( presses[0] ));
			std::uint64_t bPresses = static_cast<std::uint64_t>(std::round( presses[1] ));

			if( aPresses >= 0 && bPresses >= 0
				&& aPresses * m.AButton.X + bPresses * m.BButton.X == m.Prize.X + 10000000000000
				&& aPresses * m.AButton.Y + bPresses * m.BButton.Y == m.Prize.Y + 10000000000000 )
			{
				totalCost += aPresses * 3 + bPresses;
			}
		}
	}

	utils::PrintResult( totalCost, startTime );

	return 0;
}
