// Utils.cpp : Source file for your target.
//

#include "Utils.h"

#include <sstream>

std::vector<std::string> utils::ReadInput(const std::filesystem::path& input)
{
	std::vector<std::string> ret;
	std::ifstream istrm(input);
	std::string line;
	while ( std::getline(istrm, line))
	{
		ret.push_back(line);
	}

	return ret;
}

std::vector<std::vector<std::string>> utils::ReadFormattedInput(const std::filesystem::path& input, const std::regex& format)
{
	std::vector<std::vector<std::string>> ret;
	std::ifstream istrm(input);
	std::string line;
	while (std::getline(istrm, line))
	{
		std::smatch m;
		std::regex_match(line, m, format);
		ret.emplace_back(m.begin(), m.end());
	}

	return ret;
}

std::vector<std::string> utils::Tokenize(const std::string& str, char delim)
{
	std::stringstream sstrm(str);
	std::vector<std::string> ret;

	std::string token;
	while (std::getline(sstrm, token, delim))
	{
		if (!token.empty())
		{
			ret.push_back(token);
		}
	}

	return ret;
}

std::vector<std::string> utils::Transpose(const std::vector<std::string>& grid)
{
	std::vector<std::string> ret;

	for (std::size_t x = 0; x < grid[0].size(); x++)
	{
		std::string s;
		for (std::size_t y = 0; y < grid.size(); y++)
		{
			s.push_back(grid[y][x]);
		}
		ret.push_back(s);
	}

	return ret;
}

void utils::PrintGrid(const std::vector<std::string>& grid)
{
	for (const auto& line : grid)
	{
		std::cout << line << "\n";
	}

	std::cout << "\n";
}

std::set<utils::Pos> utils::Pos::GetUnboundedNeighbours(bool includeDiagonals) const
{
	std::set<Pos> ret;
	ret.insert(*this + Pos(0, -1));
	ret.insert(*this + Pos(1, 0));
	ret.insert(*this + Pos(0, 1));
	ret.insert(*this + Pos(-1, 0));

	if (includeDiagonals)
	{
		ret.insert(*this + Pos(1, -1));
		ret.insert(*this + Pos(1, 1));
		ret.insert(*this + Pos(-1, 1));
		ret.insert(*this + Pos(-1, -1));
	}

	return ret;
}

std::set<utils::Pos> utils::Pos::GetNeighbours(const std::vector<std::string>& map, bool includeDiagonals ) const
{
	std::set<Pos> ret;
	auto addPoint = [&](const Pos& p)
		{
			if (p.X >= 0 && p.X < map[0].size() &&
				p.Y >= 0 && p.Y < map.size())
			{
				ret.insert(p);
			}
		};

	addPoint(*this + Pos(0, -1));
	addPoint(*this + Pos(1, 0));
	addPoint(*this + Pos(0, 1));
	addPoint(*this + Pos(-1, 0));
	
	if (includeDiagonals)
	{
		addPoint(*this + Pos(1, -1));
		addPoint(*this + Pos(1, 1));
		addPoint(*this + Pos(-1, 1));
		addPoint(*this + Pos(-1, -1));
	}

	return ret;
}

std::set<utils::Pos> utils::Pos::GetNeighbours(const utils::Connections& connections, const std::vector<std::string>& map) const
{
	std::set<Pos> ret;
	auto addPoint = [&](const Pos& p)
		{
			if (p.X >= 0 && p.X < map[0].size() &&
				p.Y >= 0 && p.Y < map.size())
			{
				ret.insert(p);
			}
		};

	if (connections.north)
	{
		addPoint(*this + Pos(0, -1));
	}

	if (connections.east)
	{
		addPoint(*this + Pos(1, 0));
	}

	if (connections.south)
	{
		addPoint(*this + Pos(0, 1));
	}

	if (connections.west)
	{
		addPoint(*this + Pos(-1, 0));
	}

	return ret;
}

bool operator==(const utils::Connections& lhs, const utils::Connections& rhs)
{
	return lhs.north == rhs.north
		&& lhs.south == rhs.south
		&& lhs.east == rhs.east
		&& lhs.west == rhs.west;
}

utils::Connections operator|(const utils::Connections& lhs, const utils::Connections& rhs)
{
	utils::Connections ret;
	ret.north = lhs.north || rhs.north;
	ret.south = lhs.south || rhs.south;
	ret.east = lhs.east || rhs.east;
	ret.west = lhs.west || rhs.west;

	return ret;
}

utils::Connections operator&(const utils::Connections& lhs, const utils::Connections& rhs)
{
	utils::Connections ret;
	ret.north = lhs.north && rhs.north;
	ret.south = lhs.south && rhs.south;
	ret.east = lhs.east && rhs.east;
	ret.west = lhs.west && rhs.west;

	return ret;
}

std::ostream& operator<<( std::ostream& os, const utils::Pos& p )
{
	return os << p.X << "," << p.Y;
}
