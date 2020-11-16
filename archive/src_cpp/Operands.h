#ifndef __OPERANDS_H__
#define __OPERANDS_H__

#include <iostream>
#include <stdlib.h>

namespace Logic
{

	class Operand
	{
	public:
		// Constructors.
		Operand() : m_cSymbol(' '), m_bVal(false) {}
		Operand(char c) : m_cSymbol(c), m_bVal(false) {}
		Operand(char c, bool b) : m_cSymbol(c), m_bVal(b) {}

		// Methods.
		bool GetValue() const { return m_bVal; }
		void PutValue(bool b) { m_bVal = b; }
		char GetSymbol() const { return m_cSymbol; }
		void PutSymbol(char c) { m_cSymbol = c; }

		// Properties.
		__declspec(property(get = GetValue, put = PutValue)) bool Value;
		__declspec(property(get = GetSymbol, put = PutSymbol)) char Symbol;

	private:
		char m_cSymbol;
		bool m_bVal;
	};


#define CHARTOIDX(c) ((c) - 'a')
#define OPCOUNT 26

	class Operands
	{
	public:
		Operands();
		Operands(const Operands&);
		~Operands();
		int Add(const Operand&);
		bool ValueOf(char) const;
		void SetValueOf(char, bool);
		void SetValues(unsigned long);
		void Clear();
		int Size() const { return m_iOperandCount; }
		void Clone(Operands&) const;
		int Combine(const Operands&);

	private:		

		int m_iOperandCount{};
		char m_acOps[OPCOUNT]{};
	};

	inline bool Operands::ValueOf(char c) const
	{
		if (c == '1' || c == 'T') return true;
		if (c == '0' || c == 'F') return false;
		return m_acOps[CHARTOIDX(c)] == '1' ? true : false;
	}

	inline void Operands::SetValueOf(char c, bool b)
	{
		m_acOps[CHARTOIDX(c)] = (b ? '1' : '0');
	}

}

#endif