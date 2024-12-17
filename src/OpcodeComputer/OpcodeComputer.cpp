#include "OpcodeComputer.h"

#include <ranges>
#include <stdexcept>
#include <cassert>
#include <iostream>

OpcodeComputer::OpcodeComputer( const std::vector<std::uint8_t>& program, std::uint64_t a /*= 0*/, std::uint64_t b /*= 0*/, std::uint64_t c /*= 0*/ ) :
	m_RegisterA(a),
	m_RegisterB(b),
	m_RegisterC(c),
	m_Program(program)
{}

const std::string& OpcodeComputer::Run()
{
	while( m_IP < m_Program.size() - 1 )
	{
		auto inst = m_Program[m_IP];
		auto operand = m_Program[m_IP + 1];
		std::int64_t opValue = 0;
		switch( operand )
		{
			case 0:
			case 1:
			case 2:
			case 3:
			opValue = static_cast<std::int64_t>(operand);
			break;
			case 4:
			opValue = m_RegisterA;
			break;
			case 5:
			opValue = m_RegisterB;
			break;
			case 6:
			opValue = m_RegisterC;
			break;
			case 7:
			default:
			if( inst != 4 )
			{
				throw std::invalid_argument( "Invalid operand" );
			}
			break;
		}

		switch( inst )
		{
			case 0:	//adv
			assert( opValue <= 63 );
			m_RegisterA = m_RegisterA >> opValue;
			m_IP += 2;
			break;
			case 1:	//bxl
			m_RegisterB = m_RegisterB ^ opValue;
			m_IP += 2;
			break;
			case 2:	//bst
			m_RegisterB = opValue % 8;
			m_IP += 2;
			break;
			case 3:	//jnz
			if( m_RegisterA == 0 )
			{
				m_IP += 2;
			}
			else
			{
				m_IP = opValue;
			}
			break;
			case 4:	//bxc
			m_RegisterB = m_RegisterB ^ m_RegisterC;
			m_IP += 2;
			break;
			case 5:	//out
			if( !m_Output.empty() )
			{
				m_Output += ",";
			}
			m_Output += std::to_string( opValue % 8 );
			m_IP += 2;
			break;
			case 6:	//bdv
			assert( opValue <= 63 );
			m_RegisterB = m_RegisterA >> opValue;
			m_IP += 2;
			break;
			case 7:	//cdv
			assert( opValue <= 63 );
			m_RegisterC = m_RegisterA >> opValue;
			m_IP += 2;
			break;
			default:
			break;
		}
	}

	return m_Output;
}

