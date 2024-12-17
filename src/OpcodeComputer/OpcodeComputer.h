#pragma once

#include <vector>
#include <string>

class OpcodeComputer
{
public:
	OpcodeComputer( const std::vector<std::uint8_t>& program, std::uint64_t a = 0, std::uint64_t b = 0, std::uint64_t c = 0 );
	~OpcodeComputer() = default;

	const std::string& Run();

private:
	std::uint64_t m_RegisterA = 0;
	std::uint64_t m_RegisterB = 0;
	std::uint64_t m_RegisterC = 0;

	std::vector<std::uint8_t> m_Program;

	std::size_t m_IP = 0;

	std::string m_Output;
};
