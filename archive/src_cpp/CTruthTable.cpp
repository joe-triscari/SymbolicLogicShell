/*********************************************************/
/****  CTruthTable.cc                                 ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains the class implementation  ****/
/****    for CTruthTable.                             ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#include "CTruthTable.h"

void CTruthTable::printTable(ostream* out, TableStyle style, char cTrueSymbol, char cFalseSymbol)
{
   long lCombos=0;
   register OperandList * pOperands=NULL;   
   ExpressionList * pExpr=NULL;

   if(style != Default) m_eTableStyle = style;

   lCombos = m_Expression.GetCombonationCount();
   pOperands = m_Expression.GetOperands();

   // PRINT THE OPERANDS.
   while(pOperands) { (*out) << pOperands->cOperand; pOperands = pOperands->pNext; }

   if(m_eTableStyle == Normal)  // PRINT THE EXPRESSION.
   {
      (*out) << "| " << m_Expression.GetExpression() << endl;

      // PRINT THE HORIZONTAL BORDER.
      for(int i=0; i<m_Expression.GetVariableCount() + m_Expression.GetExpression().length() + 2; i++)
         (*out) << (i == m_Expression.GetVariableCount() ? '|' : '-');

      (*out) << endl;
   }
   else  // PRINT ALL THE SUB EXPRESSIONS.
   {
      pExpr = m_Expression.GetSubExpressions();
      int iCount=0;
      while(pExpr)
      {
         (*out) << (iCount==0 ? "| " : " | ") << pExpr->strExpression;
         ++iCount;
         pExpr = pExpr->pNext;
      }
      (*out) << endl;

      for(int i=0; i<m_Expression.GetVariableCount(); i++)
        (*out) << '-';

      (*out) << '|';
       pExpr = m_Expression.GetSubExpressions();
       while(pExpr)
       {
          for(int i=0; i<pExpr->strExpression.length()+2; i++) (*out) << '-';
          if(pExpr->pNext) (*out) << '|';
          pExpr = pExpr->pNext;
       }
       (*out) << endl;
   }

   //for(register long i=0; i<lCombos; i++)
   for(register long i=lCombos-1; i>=0; i--)
   {
      for(register int k=0; k<m_Expression.GetVariableCount(); k++)
        if( (lCombos & (i << k+1)) )
          (*out) << cTrueSymbol; 
        else
          (*out) << cFalseSymbol;

      if(m_eTableStyle==Normal)
         (*out) << "| " << (m_Expression.GetTruthValue(i) ? cTrueSymbol : cFalseSymbol) << endl;
      else
      {
         ValueList * pVal=m_Expression.GetTruthValues(i);
         pExpr = m_Expression.GetSubExpressions();
         (*out) << "| ";
         while(pVal)
         {
            (*out) << (pVal->iValue ? cTrueSymbol : cFalseSymbol);
            if(pVal->pNext)
            {
               for(int j=0; j<pExpr->strExpression.length(); j++) (*out) << ' ';
               (*out) << "| ";
            }
            pVal = pVal->pNext;
            pExpr = pExpr->pNext;
         }
         (*out) << endl;
      }

   }

}
