// Utils.h : Header file for your target.

#pragma once

#include "ctre.hpp"

#include <chrono>
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <filesystem>
#include <fstream>
#include <set>
#include <map>
#include <algorithm>
#include <numeric>
#include <deque>
#include <queue>
#include <compare>

namespace utils
{
	struct Connections;
}

bool operator==(const utils::Connections& lhs, const utils::Connections& rhs);
utils::Connections operator|(const utils::Connections& lhs, const utils::Connections& rhs);
utils::Connections operator&(const utils::Connections& lhs, const utils::Connections& rhs);

namespace utils
{
	template<std::size_t N>
	using RegexStr = ctll::fixed_string<N>;

	namespace detail
	{
		template<std::size_t... indices>
		constexpr auto GetMatchesHelper( auto matchResults, std::index_sequence<indices...> ) -> std::array<std::string_view, sizeof...(indices)>
		{
			return { { matchResults.get<indices>().view()...}};
		}

		template<std::size_t count>
		constexpr std::array<std::string_view, count> GetMatches( auto matchResults )
		{
			return GetMatchesHelper( matchResults, std::make_index_sequence<count>{} );
		}
	}

	std::vector<std::string> ReadInput(const std::filesystem::path& input);

	[[deprecated]]
	std::vector<std::vector<std::string>> ReadFormattedInput(const std::filesystem::path& input, const std::regex& format);

	template<ctll::fixed_string Regex>
	constexpr std::vector<std::vector<std::string>> ReadFormattedInput(const std::filesystem::path& input)
	{
		auto matcher = ctre::match<Regex>;
		
		std::vector<std::vector<std::string>> ret;
		std::ifstream istrm(input);
		std::string line;
		while (std::getline(istrm, line))
		{
			auto results = matcher(line);
			if ( results )
			{
				auto matches = detail::GetMatches<results.count()>(results);
				ret.emplace_back( matches.begin(), matches.end() );
			}
		}

		return ret;
	}

	std::vector<std::string> Tokenize(std::string str, char delim);

	std::vector<std::string> Transpose(const std::vector<std::string>& grid);

	void PrintGrid(const std::vector<std::string>& grid);

	template<typename T>
	void PrintResult(const T& val, std::chrono::system_clock::time_point startTime)
	{
		std::cout << val << "\n";
		std::cout << "Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - startTime) << "\n";
	}

	struct Connections
	{
		bool north = false;
		bool south = false;
		bool east = false;
		bool west = false;

		std::size_t Count() const
		{
			std::size_t count = 0;
			if (north) count++;
			if (south) count++;
			if (east) count++;
			if (west) count++;

			return count;
		}

		Connections& operator|=(const Connections& rhs)
		{
			*this = *this | rhs;
			return *this;
		}

		Connections& operator&=(const Connections& rhs)
		{
			*this = (*this & rhs);
			return *this;
		}

		explicit operator bool() const
		{
			return north || south || east || west;
		}
	};

	class Pos
	{
	public:
		Pos(int x, int y) :
			X(x), Y(y)
		{}

		int X;
		int Y;

		std::set<Pos> GetUnboundedNeighbours(bool includeDiagonals = true);
		std::set<Pos> GetNeighbours(const std::vector<std::string>& map, bool includeDiagonals = true);
		std::set<Pos> GetNeighbours(const Connections& connections, const std::vector<std::string>& map);
		int GetManDistance(const Pos& other);

		std::strong_ordering operator<=>(const utils::Pos& rhs) const
		{
			if (X == rhs.X)
			{
				return Y <=> rhs.Y;
			}
			else
			{
				return X <=> rhs.X;
			}
		}

		bool operator==(const utils::Pos& rhs) const
		{
			return X == rhs.X && Y == rhs.Y;
		}

		bool operator!=(const utils::Pos& rhs) const
		{
			return !(*this == rhs);
		}
	};
}

utils::Pos operator+(const utils::Pos& lhs, const utils::Pos& rhs);
utils::Pos operator-(const utils::Pos& lhs, const utils::Pos& rhs);
