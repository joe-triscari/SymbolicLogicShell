#ifndef __LOGICEXPRESSION_H__
#define __LOGICEXPRESSION_H__

#include "Operands.h"

class LogicExpressionFactory;
class ExprNode;

class LogicExpression
{
	friend class LogicExpressionFactory;
public:

	// Get the true/false value of expression.
	bool GetValue();
	//bool GetValue(long) const;
	//bool GetValue(const Operands&);

	// Logically compare two expressions.
	bool LogicallyImplies(const LogicExpression&);
	bool LogicallyEquivalent(const LogicExpression&);
	bool operator>(const LogicExpression& e)
	{ return LogicallyImplies(e); }
	bool operator==(const LogicExpression& e)
	{ return LogicallyEquivalent(e); }

private:
	// Disallow copy construction.
	LogicExpression(const LogicExpression&) {}
	// Disallow instantiation.
	LogicExpression();

	ExprNode* m_pExprTree;
	Operands m_ops;
};

#endif