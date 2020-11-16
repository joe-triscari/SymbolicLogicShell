/*********************************************************/
/****  CExpression.cc                                 ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains the class implementation  ****/
/****    for CExpression.                             ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#include "CExpression.h"

CExpression::CExpression()
{
   m_iNbrOperands=0;
   m_lNbrCombos=0;
   m_iIsValid=0;
   m_strExpression = "";
   m_pxOperandHead=NULL;
   m_pxExprHead=NULL;
   m_pxValueHead=NULL;
   m_pExpTree=NULL;
   m_cTrue='1';
   m_cFalse='0';
}

CExpression::CExpression(const CExpression& e)
{
   m_pxOperandHead=NULL;
   m_pxExprHead=NULL;
   m_pxValueHead=NULL;
   m_pExpTree=NULL;
   m_cTrue='1';
   m_cFalse='0';
   (*this) = e;
}

const CExpression& CExpression::operator=(const CExpression& e)
{
   SetExpression(e.GetExpression());
   return(*this);
}

const CExpression& CExpression::operator=(const CString& s)
{
    SetExpression(s);
    return(*this);
}

CExpression::CExpression(const CString& s)
{
   m_pxOperandHead=NULL;
   m_pxExprHead=NULL;
   m_pxValueHead=NULL;
   m_pExpTree=NULL;
   SetExpression(s);
}

CExpression::~CExpression() { clear(); }

short CExpression::SetExpression(CString strExpr)
{
   clear();
   m_strExpression=strExpr;

   CString strErr;
   m_iNbrOperands = ParseExpression(m_strExpression, &strErr);
   if(m_iNbrOperands < 0) clear();
   else { m_lNbrCombos = (long)pow(2.0, (double)m_iNbrOperands); m_iIsValid=1; }

   if(m_iIsValid)
   {
      m_pExpTree = BuildExpressionTree(m_strExpression, &strErr);
      if(!m_pExpTree) clear();
      else m_iIsValid=1;
   }
   return (short)m_iIsValid;
}

int CExpression::GetTruthValue(unsigned long lNbr)
{
   if(m_iIsValid)
   {
      if(lNbr >= 0 && lNbr < m_lNbrCombos)
      {
         OperandList * pListWalker=m_pxOperandHead;
         for(register long j=0; j<m_iNbrOperands; j++)
         {
            pListWalker->iValue = ( (m_lNbrCombos & (lNbr << j+1)) ? 1 : 0);
            pListWalker = pListWalker->pNext;
         }
         return m_pExpTree->value(m_pxOperandHead);
      }
      else return int(-2);
   }
   else return int(-3);
}

ValueList* CExpression::GetTruthValues(unsigned long lNbr)
{
   if(m_iIsValid)
   {
      if(lNbr >= 0 && lNbr < m_lNbrCombos)
      {
         if(m_pxValueHead)
         {
            register ValueList * pDel;
            while(m_pxValueHead)
            {
               pDel = m_pxValueHead;
               m_pxValueHead = m_pxValueHead->pNext;
               delete pDel;
            }
            m_pxValueHead=NULL;
         }

         register OperandList * pListWalker=m_pxOperandHead;
         for(register long j=0; j<m_iNbrOperands; j++)
         {
            pListWalker->iValue = ( (m_lNbrCombos & (lNbr << j+1)) ? 1 : 0);
            pListWalker = pListWalker->pNext;
         }

         if(GetMajorOperator() == ' ')
         {
            m_pxValueHead = new ValueList;
            m_pxValueHead->iValue = m_pExpTree->value(m_pxOperandHead);
            m_pxValueHead->pNext=NULL;
         }
         else
            getSubValues(m_pExpTree, m_pxOperandHead);

         return m_pxValueHead;
      }
      else return NULL;
   }
   else return NULL;
}


int CExpression::GetTruthValue(OperandList * pHead)
{
   if(m_iIsValid) 
   {
      //if(pHead) 
         return m_pExpTree->value(pHead);
      //else 
      //   return int(-4);
   }
   else 
      return int(-5);
}

ValueList* CExpression::GetTruthValues(OperandList * pHead)
{
   if(m_iIsValid) 
   {
      if(m_pxValueHead)
      {
         register ValueList * pDel;
         while(m_pxValueHead)
         {
            pDel = m_pxValueHead;
            m_pxValueHead = m_pxValueHead->pNext;
            delete pDel;
         }
         m_pxValueHead=NULL;
      }

      if(GetMajorOperator() == ' ')
      {
         m_pxValueHead = new ValueList;
         m_pxValueHead->iValue = m_pExpTree->value(pHead);
         m_pxValueHead->pNext=NULL;
      }
      else
         getSubValues(m_pExpTree, pHead);

      return m_pxValueHead;
   }
   else           
      return NULL;
}

char CExpression::GetMajorOperator() const
{
   if(m_iIsValid)
   {
      if(m_pExpTree)
      {
         char c = m_pExpTree->symbol();
         if(isOperator(c)) return c;
         else return ' ';
      }
      else return ' ';
   }
   else return ' ';
}

ExpressionList* CExpression::GetSubExpressions()
{
   if(m_iIsValid)
   {
      if(m_pxExprHead) return m_pxExprHead;
      else
      {
         if(GetMajorOperator() == ' ')  // No Operator
         {
            m_pxExprHead = new ExpressionList;
            m_pxExprHead->strExpression = GetExpression();
            m_pxExprHead->pNext=NULL;
         }
         else
            (void)getSubExpressions(m_pExpTree);

         return m_pxExprHead;
      }
   }
   else return NULL;
}

void CExpression::clear()
{
   m_iNbrOperands=0;
   m_lNbrCombos=0;
   m_iIsValid=0;
   m_strExpression = "";

   OperandList * pDel;
   while(m_pxOperandHead) 
   {
      pDel = m_pxOperandHead;
      m_pxOperandHead = m_pxOperandHead->pNext;
      delete pDel;
   }
   m_pxOperandHead=NULL;

   ExpressionList * pDel2;
   while(m_pxExprHead) 
   {
      pDel2 = m_pxExprHead;
      m_pxExprHead = m_pxExprHead->pNext;
      delete pDel2;
   }
   m_pxExprHead=NULL;

   ValueList * pDel3;
   while(m_pxValueHead) 
   {
      pDel3 = m_pxValueHead;
      m_pxValueHead = m_pxValueHead->pNext;
      delete pDel3;
   }
   m_pxValueHead=NULL;

   if(m_pExpTree) destroyTree(m_pExpTree);
   m_pExpTree=NULL;
}

short CExpression::operator==(CExpression& e)
{
   short sIsEqual=1;
   int iOperandCount=0;
  
   if(!m_iIsValid || !e) return 0;

   register OperandList *pAllOperands=NULL, *pOperand1=NULL, *pOperand2=NULL, *pInsert=NULL;
   int iOperandCount1=0, iOperandCount2=0;

   pOperand1=m_pxOperandHead;
   while(pOperand1)
   {
      pInsert = new OperandList;
      pInsert->cOperand = pOperand1->cOperand;
      iOperandCount1 += OperandInsert(&pAllOperands, pInsert);
      pOperand1 = pOperand1->pNext;
   }

   pOperand2=e.m_pxOperandHead;
   while(pOperand2)
   {
      pInsert = new OperandList;
      pInsert->cOperand = pOperand2->cOperand;
      iOperandCount2 += OperandInsert(&pAllOperands, pInsert);
      pOperand2 = pOperand2->pNext;
   } 
 
   iOperandCount = iOperandCount1 + iOperandCount2;

   //if(iOperandCount2 != 0)
   //   sIsEqual = 0;
   //else
   //{
      long lNbrCombo = (long)pow(2.0, (double)iOperandCount);
      register OperandList * pListWalker=NULL;
      for(register long i=0; i<lNbrCombo && sIsEqual==1; i++)
      {
         pListWalker=pAllOperands;
         for(register long j=0; j<iOperandCount; j++)
         {
            pListWalker->iValue = ((lNbrCombo & (i << j+1)) ? 1 : 0);
            pListWalker = pListWalker->pNext;
         }
         if(GetTruthValue(pAllOperands) != e.GetTruthValue(pAllOperands))
            sIsEqual = 0;
      }
   //}

   register OperandList * pDel=NULL;
   while(pAllOperands)
   {
      pDel = pAllOperands;
      pAllOperands = pAllOperands->pNext;
      delete pDel;
   }
   return sIsEqual;
}


short CExpression::LogicallyImplies(CExpression& e)
{
   short sDoesImply=1;
   int iOperandCount=0;
  
   if(!m_iIsValid || !e) return 0;

   register OperandList *pAllOperands=NULL, *pOperand1=NULL, *pOperand2=NULL, *pInsert=NULL;
   int iOperandCount1=0, iOperandCount2=0;

   pOperand1=m_pxOperandHead;
   while(pOperand1)
   {
      pInsert = new OperandList;
      pInsert->cOperand = pOperand1->cOperand;
      iOperandCount1 += OperandInsert(&pAllOperands, pInsert);
      pOperand1 = pOperand1->pNext;
   }

   pOperand2=e.m_pxOperandHead;
   while(pOperand2)
   {
      pInsert = new OperandList;
      pInsert->cOperand = pOperand2->cOperand;
      iOperandCount2 += OperandInsert(&pAllOperands, pInsert);
      pOperand2 = pOperand2->pNext;
   } 
 
   iOperandCount = iOperandCount1 + iOperandCount2;

      long lNbrCombo = (long)pow(2.0, (double)iOperandCount);
      OperandList * pListWalker=NULL;
      for(register long i=0; i<lNbrCombo && sDoesImply==1; i++)
      {
         pListWalker=pAllOperands;
         for(register long j=0; j<iOperandCount; j++)
         {
            pListWalker->iValue = ( (lNbrCombo & (i << j+1)) ? 1 : 0);
            pListWalker = pListWalker->pNext;
         }
         if(!e.GetTruthValue(pAllOperands))
            if(GetTruthValue(pAllOperands))
               sDoesImply = 0;
      }

   register OperandList * pDel=NULL;
   while(pAllOperands)
   {
      pDel = pAllOperands;
      pAllOperands = pAllOperands->pNext;
      delete pDel;
   }
   return sDoesImply;
}

/////
// Private Functions
/////

int CExpression::ParseExpression(CString strExpr, CString* strErrMsg)
{
   int len = strExpr.length();
   char c;
   int iCount=0;

   for(int i=0; i<len; i++)
   {
      c = strExpr[i];
   
      if(c=='[' || c=='{') strExpr[i]=c='(';
      if(c==']' || c=='}') strExpr[i]=c=')';

      if( c >= 'a' && c <= 'z')
      {
        OperandList* pTmp = new OperandList;
        pTmp->cOperand = c;
        pTmp->iValue = -1;
        iCount += OperandInsert(&m_pxOperandHead, pTmp);
      } 
      else if( !isOperator(c) && c != '(' && c != ')' && c != ' ' && 
               c != m_cTrue && c != m_cFalse)
      {
         if(strErrMsg) (*strErrMsg) = "Invalid character: " + c;
         return int(-1);
      }
    }
   return iCount;
}

CNode* CExpression::BuildExpressionTree(CString strExpr, CString* strErrMsg)
{
  char c, cOperator;
  int iLeftParCount=0;
  CNode * pNode;

  class chrStack
  {
  public:
    chrStack() { _iIndex=-1; }
    void push(char c) { _Cells[++_iIndex] = c; }
    char pop() { return _Cells[_iIndex--]; }
    int size() const { return _iIndex+1; }
  private:
    char _Cells[MAX_STACK_SIZE];
    int _iIndex;
  } OperStack;

  class nodeStack
  {
  public:
    nodeStack() { _iIndex=-1; }
    void push(CNode* ptr) { _Cells[++_iIndex] = ptr; }
    CNode* pop() { return _Cells[_iIndex--]; }
    int size() const { return _iIndex+1; }

  private:
    CNode* _Cells[MAX_STACK_SIZE];
    int _iIndex;
  } nStack;

  int len = strExpr.length();
  for(int i=0; i<len; i++)
  {
    c = strExpr[i];
    if(c == ' ' || c == '\t') continue;

    if(c == '(' || c == '{' || c == '[')
      iLeftParCount++;
    else if(isOperator(c))
      OperStack.push(c);
    else if(c == ')' || c == '}' || c == ']')
    {
       iLeftParCount--;
       if(OperStack.size() > 0)
       {
         cOperator = OperStack.pop();
         if(cOperator == NOT)
         {
           pNode = new COperatorNode(cOperator,iCalc);
           pNode->setRightChild( nStack.pop() ); 
           nStack.push(pNode);
         }
         else
         {
           pNode = new COperatorNode(cOperator,iCalc);
           pNode->setRightChild( nStack.pop() );
           pNode->setLeftChild( nStack.pop() );
           nStack.push(pNode);
         }

       }
    }
    else
    {
      pNode = new COperandNode(c);
      nStack.push(pNode);
    }
  }

  if(iLeftParCount != 0)
  {
    if(strErrMsg) (*strErrMsg) = "Error: Mismatched paranthesis";
    return NULL;
  }
  else if(OperStack.size() > 0)
  {
     if(strErrMsg) (*strErrMsg) =  "Error: Ambigous expression.";
     return NULL;
  }
  
   return nStack.pop();
}

void CExpression::destroyTree(CNode* ptr)
{
   if(ptr)
   {
      destroyTree(ptr->getLeftChild());
      delete ptr;
      destroyTree(ptr->getRightChild());
   }
}

CString CExpression::getSubExpressions(CNode* ptr) 
{
   CString cOp1,cOp2,c;
   if(ptr->getRightChild())  
   {
      if(ptr->getLeftChild())  
      {
         cOp1 = getSubExpressions(ptr->getLeftChild());
         cOp2 = getSubExpressions(ptr->getRightChild());
         c = "(";
         c = c + cOp1;
         c = c + ((COperatorNode*)ptr)->oper();
         c = c + cOp2;
         c = c + ")";
         ExpressionList * pEx = new ExpressionList;
         pEx->strExpression = c;
         ExpressionInsertTail(&m_pxExprHead, pEx);
      }
      else
      {
         cOp1 = getSubExpressions(ptr->getRightChild());
         c = "(";
         c = c + ((COperatorNode*)ptr)->oper();
         c = c + cOp1;
         c = c + ")"; 
         ExpressionList * pEx = new ExpressionList;
         pEx->strExpression = c;
         ExpressionInsertTail(&m_pxExprHead, pEx);
      }
   }
   else c=ptr->symbol();

   return c;
}


void CExpression::getSubValues(CNode* ptr, OperandList* pList)
{
   if(ptr->getRightChild())
   {
      if(ptr->getLeftChild())
      {
         getSubValues(ptr->getLeftChild(), pList);
         getSubValues(ptr->getRightChild(), pList);
         ValueList * pVal = new ValueList;
         pVal->iValue = ptr->value(pList);
         ValueInsertTail(&m_pxValueHead, pVal);
      }
      else
      {
         getSubValues(ptr->getRightChild(), pList);
         ValueList * pVal = new ValueList;
         pVal->iValue = ptr->value(pList);
         ValueInsertTail(&m_pxValueHead, pVal);
      }
   }
}
