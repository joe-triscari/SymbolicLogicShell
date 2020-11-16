#include "LogicExpressionFactory.h"

namespace Logic
{

LogicExpression::LogicExpression() : m_pExprTree(nullptr)
{
}

LogicExpression::LogicExpression(const std::string& exprString) : m_pExprTree(nullptr)
{
	init(exprString);
}

LogicExpression::LogicExpression(const LogicExpression& e) : m_pExprTree(nullptr)
{
	init(e.ToString());
}
	
LogicExpression::~LogicExpression()
{
	ExpressionFactory::DestroyTree(this->m_pExprTree);
}

bool LogicExpression::init(const std::string& exprStr)
{
	if (!ExpressionFactory::Init(exprStr, *this))
	{
		throw LogicException("Expression is not valid");
	}
	
	return true;
}

LogicExpression& LogicExpression::operator=(const LogicExpression& e)
{
	if(this != &e)
	{
		init(e.ToString());
	}
	return *this;
}

bool LogicExpression::GetTruthValue() const
{
	return this->m_pExprTree->GetValue(this->m_ops);
}

bool LogicExpression::GetTruthValue(const Operands& p_ops) const
{
	return this->m_pExprTree->GetValue(p_ops);
}

bool LogicExpression::LogicallyEquivalent(const LogicExpression& exp) const
{
	Operands ops;

	this->m_ops.Clone(ops);
	ops.Combine(exp.m_ops);

	const auto n = static_cast<unsigned long>(pow(2.0, static_cast<double>(ops.Size())));
	for(unsigned long l=0; l < n; ++l)
	{
		ops.SetValues(l);
		if(GetTruthValue(ops) != exp.GetTruthValue(ops))
			return false;
	}

	return true;
}

bool LogicExpression::LogicallyImplies(const LogicExpression& exp) const
{
	Operands ops;

	this->m_ops.Clone(ops);
	ops.Combine(exp.m_ops);

	const auto n = static_cast<unsigned long>(pow(2.0, static_cast<double>(ops.Size())));
	for(unsigned long l=0; l < n; ++l)
	{
		ops.SetValues(l);
		if(GetTruthValue(ops) && !exp.GetTruthValue(ops))
			return false;
	}

	return true;
}

bool LogicExpression::IsTautology() const
{
	const auto n = static_cast<unsigned long>(pow(2.0, static_cast<double>(m_ops.Size())));
	for(unsigned long l=0; l < n; ++l)
	{
		if(!GetTruthValue(l)) return false;
	}
	return true;
}

bool LogicExpression::IsContradiction() const
{
	const auto n = static_cast<unsigned long>(pow(2.0, static_cast<double>(m_ops.Size())));
	for(auto l=n-1; l > 0; l--)
	{
		if(GetTruthValue(l)) return false;
	}
	return true;
}


}