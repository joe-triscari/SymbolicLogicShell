#include "Operands.h"

namespace Logic
{

Operands::Operands()
{
	Clear();
}

Operands::Operands(const Operands& copy)
{
	this->m_iOperandCount = copy.m_iOperandCount;
	std::copy(std::begin(copy.m_acOps), std::end(copy.m_acOps), std::begin(this->m_acOps));
}

Operands::~Operands() = default;

void Operands::Clear()
{
	m_iOperandCount = 0;
	for(int i=0; i < OPCOUNT; ++i) m_acOps[i]='\0';
}

int Operands::Add(const Operand& operand)
{
	char c = operand.Symbol;
	if(c < 'a' || c > 'z') exit(1);

	if(m_acOps[CHARTOIDX(c)] == '\0')
	{
		++m_iOperandCount;
		m_acOps[CHARTOIDX(c)] = (operand.Value ? '1' : '0');
	}

	return m_iOperandCount;
}

void Operands::SetValues(unsigned long lMask)
{
	long lNbrCombos = static_cast<long>(pow(2.0, static_cast<double>(m_iOperandCount)));
	int offset=1;
	for(int i=0; i < OPCOUNT; ++i)
	{
		if(m_acOps[i] != '\0')
			m_acOps[i] = ((lNbrCombos & (lMask << offset++)) ? '1' : '0');
	}
}

void Operands::Clone(Operands& op) const
{
	if(this != &op)
	{
		op.m_iOperandCount = m_iOperandCount;
		for(int i=0; i < OPCOUNT; ++i) op.m_acOps[i] = m_acOps[i];
	}
}

int Operands::Combine(const Operands& op)
{
	if(this != &op)
	{
		for(int i=0; i < OPCOUNT; ++i)
		{
			if(op.m_acOps[i] != '\0' && m_acOps[i] == '\0')
			{
				m_acOps[i] = op.m_acOps[i];
				++m_iOperandCount;
			}
		}
	}

	return m_iOperandCount;
}

} // End namespace Logic.