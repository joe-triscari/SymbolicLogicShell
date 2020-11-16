#include "Operands.h"

Operands::Operands() : m_iOperandCount(0), m_pElms(NULL), m_bSorted(false)
{
}

Operands::~Operands()
{
	Clear();
}

void Operands::Clear()
{
	if(m_pElms) delete [] m_pElms;
	m_pElms = NULL;
	m_iOperandCount = 0;
	m_bSorted = false;
}

int Operands::Add(const Operand& operand)
{
	if(_Find(operand.Symbol)) return m_iOperandCount;

	struct Operands::Element* pTmp = new 
		Operands::Element[++m_iOperandCount];
	if(!pTmp) { cerr << "Out of memory!" << endl; exit(1); }

	int i=0;
	for(; i < m_iOperandCount-1; ++i)
	{
		pTmp[i].operand = m_pElms[i].operand;
	}
	pTmp[i].operand = operand;

	if(m_pElms) delete [] m_pElms;
	m_pElms = pTmp;

	//if(m_iOperandCount > 1)
	//{
	//	qsort((void*)&m_pElms[0], (size_t)m_iOperandCount,
	//		sizeof(struct Operands::Element), _ElmCmp);
	//}
	m_bSorted = false;

	return m_iOperandCount;
}

bool Operands::ValueOf(char c)
{
	if(c == '1' || c == 'T') return true;
	if(c == '0' || c == 'F') return false;
	return _Find(c)->operand.Value;
}

void Operands::SetValueOf(char c, bool b)
{
	_Find(c)->operand.Value = b;
}

void Operands::SetValues(unsigned long lMask)
{
	long lNbrCombos = (long)pow(2.0, (double)m_iOperandCount);
	if(!m_bSorted) _Sort();
	for(long i=0; i < m_iOperandCount; ++i)
    {
		m_pElms[i].operand.Value = 
			((lNbrCombos & (lMask << (i+1))) ? true : false);
    }
}

void Operands::Clone(Operands& op) const
{
	if(this != &op)
	{
		op.Clear();
		if(m_iOperandCount > 0)
		{
			op.m_bSorted = m_bSorted;
			op.m_iOperandCount = m_iOperandCount;
			op.m_pElms = new struct Operands::Element[m_iOperandCount];
			for(int i=0; i < m_iOperandCount; ++i) 
			{
				op.m_pElms[i] = m_pElms[i];
			}
		}
	}
}

int Operands::Combine(const Operands& op)
{
	if(this != &op)
	{
		int iSize=op.Size();
		for(int i=0; i < iSize; i++)
		{
			this->Add(op[i]);
		}
	}

	return Size();
}

//
// Private Functions.
//
struct Operands::Element* Operands::_Find(char c)
{

	if(m_iOperandCount == 0)
		return NULL;
	else
	{
		int iLow=0, iHigh=m_iOperandCount-1, iMiddle=0;

		if(!m_bSorted) _Sort();

		// Binary search.
		while(iLow <= iHigh)
		{
			iMiddle = (iLow + iHigh) / 2;

			if(m_pElms[iMiddle].operand.Symbol == c)
				return &m_pElms[iMiddle];
			else if(m_pElms[iMiddle].operand.Symbol > c)
				iHigh = iMiddle - 1;
			else
				iLow = iMiddle + 1;
		}
	}

	return NULL;
}

void Operands::_Sort()
{
	if(m_iOperandCount > 1)
	{
		qsort((void*)&m_pElms[0], (size_t)m_iOperandCount,
			sizeof(struct Operands::Element), _ElmCmp);
	}
	m_bSorted = true;
}

int Operands::_ElmCmp(const void* el1, const void* el2)
{
	char op1 = (((struct Operands::Element*)el1)->operand).Symbol;
	char op2 = (((struct Operands::Element*)el2)->operand).Symbol;
	return (op1<op2) ? -1 : (op1>op2) ? 1 : 0;
}

