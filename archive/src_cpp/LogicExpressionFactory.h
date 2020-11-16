#ifndef __EXPR_H__
#define __EXPR_H__

#include "Operands.h"
#include "LogicException.h"

#define NOT     '!'
#define AND     '&'
#define OR      '|'
#define COND    '>'
#define XOR     '^'
#define BICOND  '='
#define NAND    '$'
#define NOR     '%'

namespace Logic
{

class LogicExpression;
class ExprNode;
class OperatorNode;
class OperandNode;

//////////////////////////////////////////////////////////////////////
class ExpressionFactory
//////////////////////////////////////////////////////////////////////
{
public:
	static bool Init(const std::string&, LogicExpression&);
	static void DestroyTree(ExprNode*);

	static bool IsOperator(char);
	static bool IsOperand(char);
	static bool Evaluate(bool, bool, char);

private:
	static bool check_expression(Operands& operands, const std::string&);
	static ExprNode* parse_expression(const std::string&);
	static bool valid_char(char);
	static void destroy_tree(ExprNode*);
};

//////////////////////////////////////////////////////////////////////
class LogicExpression
//////////////////////////////////////////////////////////////////////
{
	friend class ExpressionFactory;
	friend class LogicArgument;
public:
	LogicExpression(const std::string&);
	LogicExpression(const LogicExpression&);
	~LogicExpression();

	bool IsInitialized() const { return m_pExprTree != nullptr; }

	// Get the true/false value of expression.
	bool GetTruthValue() const;
	bool GetTruthValue(unsigned long) const;
	bool GetTruthValue(const Operands&) const;

	// Logically compare two expressions.
	bool LogicallyImplies(const LogicExpression&) const;
	bool LogicallyEquivalent(const LogicExpression&) const;
	bool operator>(const LogicExpression& e) const 	{ return LogicallyImplies(e); }
	bool operator==(const LogicExpression& e) const { return LogicallyEquivalent(e); }

	LogicExpression& operator=(const LogicExpression&);

	LogicExpression operator&(const LogicExpression& e) const { return Conjunction(e); }
	LogicExpression Conjunction(const LogicExpression&) const;
	LogicExpression operator|(const LogicExpression& e) const { return Disjunction(e); }
	LogicExpression Disjunction(const LogicExpression&) const;

	LogicExpression operator!() const { return Negation(); }
	LogicExpression Negation() const;

	std::string ToString() const { return m_strExpr; }
	int GetOperandCount() const { return m_ops.Size(); }

	// Properties.
	__declspec(property(get=GetOperands)) Operands* Ops;
	Operands* GetOperands() const { return &m_ops; }

	bool IsTautology() const;
	bool IsContradiction() const;
	bool IsContingency() const { return !IsTautology() && !IsContradiction(); }

private:
	LogicExpression();
	bool init(const std::string&);

	ExprNode* m_pExprTree;
	mutable Operands m_ops;

	std::string m_strExpr;
};

inline bool LogicExpression::GetTruthValue(unsigned long l) const
{
	m_ops.SetValues(l);
	return GetTruthValue();
}

inline LogicExpression LogicExpression::Conjunction(const LogicExpression& e) const
{
	return LogicExpression("(" + ToString() + "&" + e.ToString() + ")");
}

inline LogicExpression LogicExpression::Disjunction(const LogicExpression& e) const
{
	return LogicExpression("(" + ToString() + "|" + e.ToString() + ")");
}

inline LogicExpression LogicExpression::Negation() const
{
	return LogicExpression("(!" + ToString() + ")");
}

//////////////////////////////////////////////////////////////////////
class ExprNode
//////////////////////////////////////////////////////////////////////
{
public:
	ExprNode(char c) : m_pLeftChild(nullptr), m_pRightChild(nullptr), m_cSymbol(c) {}

	virtual ~ExprNode() = default;

	virtual bool GetValue(const Operands& operands) const = 0;	
	virtual char GetSymbol() const { return m_cSymbol; }

	void PutRightChild(ExprNode* p) { m_pRightChild=p; }
	ExprNode* GetRightChild() const { return m_pRightChild; }	
	ExprNode* GetLeftChild() const { return m_pLeftChild; }
	void PutLeftChild(ExprNode* p) { m_pLeftChild=p; }

	__declspec(property(get = GetSymbol)) char Symbol;
	__declspec(property(get = GetRightChild, put = PutRightChild)) ExprNode* RightChild;
	__declspec(property(get=GetLeftChild,put=PutLeftChild)) ExprNode* LeftChild;

protected:
   ExprNode* m_pLeftChild;
   ExprNode* m_pRightChild;
   char m_cSymbol;
};

//////////////////////////////////////////////////////////////////////
class OperandNode : public ExprNode
//////////////////////////////////////////////////////////////////////
{
public:
	OperandNode(char c) : ExprNode(c) {}

	bool GetValue(const Operands& operands) const override
	{ 
		return operands.ValueOf(m_cSymbol);
	}
};

//////////////////////////////////////////////////////////////////////
class OperatorNode : public ExprNode
//////////////////////////////////////////////////////////////////////
{
public:
	OperatorNode(char c) : ExprNode(c) {}
	~OperatorNode() = default;
	bool GetValue(const Operands& operands) const override { return tree_eval(this, operands); }
private:

	static bool tree_eval(const ExprNode* pNode, const Operands& operands)
	{
		bool bOp1, bVal;
		if(pNode->RightChild)  
		{
			if(pNode->LeftChild)  
			{
				bOp1 = tree_eval(pNode->LeftChild, operands);
				const bool bOp2 = tree_eval(pNode->RightChild, operands);
				bVal = ExpressionFactory::Evaluate(bOp1, bOp2, pNode->Symbol);
			}
			else
			{
				bOp1 = tree_eval(pNode->RightChild, operands);
				bVal = ExpressionFactory::Evaluate(bOp1, false, pNode->Symbol);
			}
		}
		else bVal = pNode->GetValue(operands);

		return bVal;
	}
};

//////////////////////////////////////////////////////////////////////
class LogicArgument
//////////////////////////////////////////////////////////////////////
{
public:
	LogicArgument();
	~LogicArgument();
	void AddPremise(const LogicExpression&);
	void AddPremise(const std::string&);
	void SetConclusion(const LogicExpression&);
	LogicExpression GetConclusion() const { return m_pConc; }
	bool IsValid() const;
	void Reset();
	std::string ToString() const;
	LogicExpression GetExpression() const { return LogicExpression(ToString()); }

	// Properties.
	__declspec(property(put=SetConclusion,get=GetConclusion)) LogicExpression Conclusion;
	__declspec(property(get=GetExpression)) LogicExpression Expression;

private:
	LogicExpression m_paPrem[128];
	LogicExpression m_pConc;
	int m_iPremCount;
	bool _hasConclusion;
	mutable short _validityIndicator;
		// -1 means unknown
		//  0 means not valid
	    //  1 means valid
};


} // End Namespace

#endif