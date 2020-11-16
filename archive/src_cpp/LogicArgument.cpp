#include "LogicExpressionFactory.h"

namespace Logic
{

LogicArgument::LogicArgument() : m_iPremCount(0), _hasConclusion(false), _validityIndicator(-1)
{}

LogicArgument::~LogicArgument() = default;

void LogicArgument::Reset()
{
	m_iPremCount = 0;
	_hasConclusion = false;
}

void LogicArgument::AddPremise(const LogicExpression& pExpr)
{
	m_paPrem[m_iPremCount++] = pExpr;
	_validityIndicator = -1;
}

void LogicArgument::AddPremise(const std::string& exprStr)
{
	AddPremise(LogicExpression(exprStr));
}

void LogicArgument::SetConclusion(const LogicExpression& pConc)
{	
	m_pConc = pConc;	
	_hasConclusion = true;
	_validityIndicator = -1;
}

bool LogicArgument::IsValid() const
{	
	bool isTautology;

	if(_validityIndicator != -1)
		return _validityIndicator == 1 ? true : false;

	try
	{
		const LogicExpression expr(ToString());
		isTautology = expr.IsTautology();
	}
	catch(const LogicException& ex)
	{
		throw LogicException("LogicArgument is not constructed properly, cannot test for validity. A conclusion and at least one premise must be set.");
	}
	
	_validityIndicator = isTautology ? 1 : 0;

	return isTautology;
}

std::string LogicArgument::ToString() const
{
	if(m_iPremCount == 0)
		throw LogicException("Cannot convert LogicArgument to String because no premises have been added.");

	if(!_hasConclusion)
		throw LogicException("Cannot convert LogicArgument to String because no conclusion has been set.");

	std::string sAnt;
	for(int i=0; i < m_iPremCount; ++i)
	{
		if(i == 0)
			sAnt = m_paPrem[i].ToString();
		else
			sAnt = "(" + sAnt + "&" + m_paPrem[i].ToString() + ")";
	}

	return "(" + sAnt + ">" + m_pConc.ToString() + ")";
}


}

