/*********************************************************/
/****  exprdef.h                                      ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains definitions for symbols   ****/
/****    and functions used various classes.          ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#ifndef _EXPRESSION_TYPES_H_
#define _EXPRESSION_TYPES_H_

//#include "CNode.h"
#include "CString.h"
class CNode;

#define MAX_STACK_SIZE 128
#define NOT     '~'
#define AND     '&'
#define OR      '|'
#define COND    '>'
#define XOR     '^'
#define BICOND  '='
#define NAND    '$'
#define NOR     '%'

class Operand
{
public:
	Operand() : m_cSy(' '), m_iVal(-1) {}
	Operand(char c) : m_cSy(c), m_iVal(-1) {}
	Operand(char c, int i) m_cSy(c), m_iVal(i) {}

	__declspec(property(get=GetSymbol,put=PutSymbol)) char Symbol;
	__declspec(property(get=GetValue,put=PutValue)) int Value;

	void PutSymbol(char c) { m_cSy=c; }
	void PutValue(int v) { m_iVal=v; }
	char GetSymbol() const { return m_cSy; }
	int  GetValue() const { return m_iVal; }
private:
	char m_cSy;
	int m_iVal;
}

struct OperandList
{
   char cOperand;
   int iValue;
   struct OperandList * pNext;
};

int OperandInsert(OperandList**, OperandList*);

struct ExpressionList
{ 
   CString strExpression; 
   struct ExpressionList * pNext; 
};

void ExpressionInsertTail(ExpressionList**, ExpressionList*);

struct ValueList
{ 
   int iValue; 
   struct ValueList * pNext; 
};

void ValueInsertTail(ValueList**, ValueList*);

struct PremiseList
{ 
   CNode* pPremise; 
   struct PremiseList * pNext; 
};

void PremiseInsertTail(PremiseList**, PremiseList*);

short isOperator(char);
short isOperand(char);
int iCalc(int, int, char);

#endif
