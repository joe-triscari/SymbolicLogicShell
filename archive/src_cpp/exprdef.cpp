/*********************************************************/
/****  exprdef.cc                                     ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains the implementation of     ****/
/****    functions that are used by various classes.  ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#include "exprdef.h"

int OperandInsert(OperandList** ppHead, OperandList* pInsert)
{
   while(*ppHead && (*ppHead)->cOperand < pInsert->cOperand) 
      ppHead = &(*ppHead)->pNext;

   if(*ppHead && ( (*ppHead)->cOperand == pInsert->cOperand) ) 
      { delete pInsert; pInsert=NULL; return 0; }

   pInsert->pNext = *ppHead;
   *ppHead = pInsert;
   return 1;
}

void ExpressionInsertTail(ExpressionList** ppHead, ExpressionList* pInsert)
{
   while(*ppHead) ppHead = &(*ppHead)->pNext;

   pInsert->pNext = *ppHead;
   *ppHead = pInsert;
}

void ValueInsertTail(ValueList** ppHead, ValueList* pInsert)
{
   while(*ppHead) ppHead = &(*ppHead)->pNext;

   pInsert->pNext = *ppHead;
   *ppHead = pInsert;
}

void PremiseInsertTail(PremiseList** ppHead, PremiseList* pInsert)
{
   while(*ppHead) ppHead = &(*ppHead)->pNext;

   pInsert->pNext = *ppHead;
   *ppHead = pInsert;
}

short isOperator(char c)
{
   short sRet=0;

   switch(c) {
   case AND:
   case OR:
   case NOT:
   case COND:
   case XOR:
   case NAND:

   case NOR:

   case BICOND:
      sRet=1;
   break;
   }
 
   return sRet;
}

short isOperand(char c)
{
   if(c >= 'a' && c <= 'z') return short(1);
   else return short(0);
}

int iCalc(int iLHS, int iRHS, char cOper)
{
   int iResult=0;

   switch(cOper)
   {
   case AND:    iResult = iLHS && iRHS;
                break;
   case NAND:   iResult = !(iLHS && iRHS);
                break;
   case OR:     iResult = iLHS || iRHS;
                break;
   case NOR:    iResult = !(iLHS || iRHS);

                break;
   case NOT:    iResult = !iLHS;
                break;

   case COND:   if(iLHS == 1 && iRHS == 0) iResult = 0;
                else iResult = 1;
                break;
   case XOR:    if((iLHS==0 && iRHS==0) || (iLHS==1 && iRHS==1) ) iResult = 0;
                else iResult = 1;
                break;
   case BICOND: if((iLHS==1 && iRHS==1) || (iLHS==0 && iRHS==0) ) iResult=1;
                else iResult=0;
                break;
   }

   return iResult;
}
