#ifndef _EXPRESSIONNODE_H_
#define _EXPRESSIONNODE_H_

#include <iostream.h>

#include "LogicExpressionFactory.h"

class ExprNode
{
public:
	ExprNode() :
	  m_pLeftChild(NULL), m_pRightChild(NULL) {}

	virtual ~ExprNode() {}

	__declspec(property(get=GetValue)) int Value;
	virtual bool GetValue() = 0;

	__declspec(property(get=GetSymbol)) char Symbol;
	virtual char GetSymbol() const = 0;

	__declspec(property(get=GetLeftChild,put=PutLeftChild)) 
		ExprNode* LeftChild;
	__declspec(property(get=GetRightChild,put=PutRightChild)) 
		ExprNode* RightChild;

	ExprNode* GetLeftChild() const { return m_pLeftChild; }
	ExprNode* GetRightChild() const { return m_pRightChild; }
	void PutLeftChild(ExprNode* p) { m_pLeftChild=p; }
	void PutRightChild(ExprNode* p) { m_pRightChild=p; }

private:
   ExprNode* m_pLeftChild;
   ExprNode* m_pRightChild;
};


class OperandNode : public ExprNode
{
public:
   OperandNode(char c) { _cOperand=c; }
   ~OperandNode() {}

   bool GetValue() { 
	   return 
	   LogicExpressionFactory::GetOperands()->ValueOf(_cOperand); 
   }
   char GetSymbol() const { return _cOperand; }
private:
   char _cOperand;
};


class OperatorNode : public ExprNode
{
public:
   OperatorNode(char c) { _cOperator=c; }
   ~OperatorNode() {}
   char GetOperator() const { return _cOperator; }
   bool GetValue() {  return Eval(this); }
   char GetSymbol() const { return _cOperator; }
private:
   char _cOperator;

   int Eval(ExprNode* ptr)  
   {
      bool bOp1,bOp2,bVal;
      if(ptr->RightChild)  
      {
         if(ptr->LeftChild)  
         {
            bOp1 = Eval(ptr->LeftChild);
            bOp2 = Eval(ptr->RightChild);          
			bVal = LogicExpressionFactory::
				Evaluate(bOp1, bOp2, ((COperatorNode*)ptr)->GetOperator());
         }
         else
         {
            iOp1 = Eval(ptr->getRightChild());            
			bVal = LogicExpressionFactory::
				Evaluate(bOp1, false, ((COperatorNode*)ptr)->GetOperator());
         }
      }
      else bVal=ptr->GetValue();

      return bVal;
   }
};

#endif
