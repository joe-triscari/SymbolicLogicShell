#ifndef __OPERANDS_H__
#define __OPERANDS_H__

#include <iostream.h>
#include <stdlib.h>
#include <math.h>

class Operand
{
public:
	// Constructors.
	Operand() : m_cSymbol(' '), m_bVal(false) {}
	Operand(char c) : m_cSymbol(c), m_bVal(false) {}
	Operand(char c, bool b) : m_cSymbol(c), m_bVal(b) {}

	// Methods.
	bool GetValue() const { return m_bVal; }
	void PutValue(bool b) { m_bVal=b; }
	char GetSymbol() const { return m_cSymbol; }
	void PutSymbol(char c) { m_cSymbol=c; }

	// Properties.
	__declspec(property(get=GetValue,put=PutValue)) bool Value;
	__declspec(property(get=GetSymbol,put=PutSymbol)) char Symbol;

private:
	char m_cSymbol;
	bool m_bVal;
};

class Operands
{
public:
	Operands();
	~Operands();
	int Add(const Operand&);
	bool ValueOf(char);
	void SetValueOf(char, bool);
	void SetValues(unsigned long);
	void Clear();
	int Size() const { return m_iOperandCount; }
	void Clone(Operands&) const;
	int Combine(const Operands&);

	Operand& operator[](int idx)
	{ return m_pElms[idx].operand; }
	Operand& operator[](int idx) const
	{ return m_pElms[idx].operand; }

private:
	Operands(const Operands&);
	struct Element
	{
		Operand operand;
	};
	Element* m_pElms;
	int m_iOperandCount;
	bool m_bSorted;

	struct Element* _Find(char);
	void _Sort();
	static int Operands::_ElmCmp(const void*, const void*);
};

#endif