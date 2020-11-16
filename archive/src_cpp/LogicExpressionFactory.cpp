#include "LogicExpressionFactory.h"

namespace Logic
{
	bool ExpressionFactory::Init(const std::string& str_expr, LogicExpression& logic_expr)
	{
		Operands operands;

		bool isValid = check_expression(operands, str_expr);
		if (isValid)
		{
			ExprNode* treeNode = parse_expression(str_expr);
			if (treeNode == nullptr)
			{
				isValid = false;
			}
			else
			{
				destroy_tree(logic_expr.m_pExprTree);

				logic_expr.m_pExprTree = treeNode;
				logic_expr.m_strExpr = str_expr;
				logic_expr.m_ops.Clone(operands);
			}
		}

		return isValid;
	}

	void ExpressionFactory::DestroyTree(ExprNode* node)
	{
		destroy_tree(node);
	}

	void ExpressionFactory::destroy_tree(ExprNode* p_node)
	{
		if (p_node)
		{
			destroy_tree(p_node->LeftChild);
			destroy_tree(p_node->RightChild);
			delete p_node;
		}
	}


	bool ExpressionFactory::IsOperator(char c)
	{
		static const char aczTok[] = "=|!$%^&>";
		return strchr(aczTok, c) != nullptr;
	}

	bool ExpressionFactory::IsOperand(char c)
	{
		return c >= 'a' && c <= 'z';
	}

	bool ExpressionFactory::Evaluate(const bool bOp1, const bool bOp2, const char cOperator)
	{
		switch (cOperator)
		{
		case AND:
			return bOp1 && bOp2;
		case NAND:
			return !(bOp1 && bOp2);
		case OR:
			return bOp1 || bOp2;
		case NOR:
			return !(bOp1 || bOp2);
		case NOT:
			return !bOp1;
		case COND:
		{
			if (bOp1 && !bOp2) return false;
			return true;
		}
		case XOR:
		{
			if (!bOp1 && !bOp2 || bOp1 && bOp2) return false;
			return true;
		}
		case BICOND:
		{
			if (bOp1 && bOp2 || !bOp1 && !bOp2) return true;
			return false;
		}
		default:
			return false;
		}

	}

	bool ExpressionFactory::check_expression(Operands& operands, const std::string& sExpr)
	{
		const unsigned int len = sExpr.length();
		int iLeftPar = 0, iRightPar = 0;
		bool bOperLast = false;

		for (unsigned int i = 0; i < len; ++i)
		{
			const char c = sExpr[i];

			if (valid_char(c))
			{
				if (IsOperand(c))
				{
					operands.Add(Operand(c));
					bOperLast = false;
				}
				else if (IsOperator(c))
				{
					if (bOperLast) return false;
					bOperLast = true;
				}
				else if (c == '(')
				{
					bOperLast = false;
					++iLeftPar;
				}
				else if (c == ')')
				{
					bOperLast = false;
					++iRightPar;
				}
			}
			else
			{
				return false;
			}
		}

		if (iLeftPar != iRightPar) return false;

		return true;
	}

	ExprNode* ExpressionFactory::parse_expression(const std::string& sExpr)
	{
		int iLeftParCount = 0;
		ExprNode* pNode = nullptr;

		class CharTypeStack
		{
		public:
			CharTypeStack() : _index(-1) {}
			void push(char c) { _cells[++_index] = c; }
			char pop() { return _cells[_index--]; }
			int size() const { return _index + 1; }
		private:
			char _cells[512];
			int _index;
		} OperatorStack;

		class NodeTypeStack
		{
		public:
			NodeTypeStack() : _index(-1) {}
			void push(ExprNode* ptr) { _cells[++_index] = ptr; }
			ExprNode* pop() { return _cells[_index--]; }
			int size() const { return _index + 1; }
		private:
			ExprNode* _cells[512];
			int _index;
		} NodeStack;

		unsigned int iLen = sExpr.length();
		for (unsigned int i = 0; i < iLen; ++i)
		{
			const char c = sExpr[i];
			if (c == ' ' || c == '\t') continue;

			if (c == '(') // || c == '{' || c == '[')
				iLeftParCount++;
			else if (IsOperator(c))
				OperatorStack.push(c);
			else if (c == ')') // || c == '}' || c == ']')
			{
				iLeftParCount--;
				if (OperatorStack.size() > 0)
				{
					const char cOperator = OperatorStack.pop();
					pNode = new OperatorNode(cOperator);
					pNode->RightChild = NodeStack.pop();
					if (cOperator != NOT) pNode->LeftChild = NodeStack.pop();
					NodeStack.push(pNode);
				}
			}
			else
			{
				NodeStack.push(new OperandNode(c));
			}
		}

		if (iLeftParCount != 0) return nullptr;
		if (OperatorStack.size() > 0) return nullptr;

		return NodeStack.pop();
	}

	bool ExpressionFactory::valid_char(char c)
	{
		static const char
			aczTok[] = " \t()TF10!$%^&|=>abcdefghijklmnopqrstuvwxyz";

		return strchr(aczTok, c) != nullptr;
	}


} // End Namespace Logic



