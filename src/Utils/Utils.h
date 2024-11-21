// Utils.h : Header file for your target.

#pragma once

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

namespace utils
{
	struct Connections;
}

bool operator==(const utils::Connections& lhs, const utils::Connections& rhs);
utils::Connections operator|(const utils::Connections& lhs, const utils::Connections& rhs);
utils::Connections operator&(const utils::Connections& lhs, const utils::Connections& rhs);

namespace utils
{
	std::vector<std::string> ReadInput(const std::filesystem::path& input);

	std::vector<std::vector<std::string>> ReadFormattedInput(const std::filesystem::path& input, const std::regex& format);

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
