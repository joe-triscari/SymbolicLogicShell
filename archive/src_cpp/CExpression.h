/*********************************************************/
/****  CExpression.h                                  ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains the class definition for  ****/
/****    CExpression.                                 ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#ifndef _CEXPRESSION_H_
#define _CEXPRESSION_H_

#include <iostream.h>
#include <fstream.h>
#include <math.h>
#include "CString.h"
#include "CNode.h"
#include "exprdef.h"

class CExpression
{
   //friend class CArgument;
   //friend class CTruthTable;
   //friend int ValueOf(char);
public:
   CExpression();
   CExpression(const CExpression&);
   CExpression(const CString&);
   ~CExpression();

   OperandList* GetOperands() const { return m_pxOperandHead; }
   int GetVariableCount() const { return m_iNbrOperands; }
   long GetCombonationCount() const { return m_lNbrCombos; }
   short operator ! () const { return (m_iIsValid == 0); }
   short SetExpression(CString);
   CString GetExpression() const { return m_strExpression; }
  
   int GetTruthValue(unsigned long);
   int GetTruthValue(OperandList*);
   ValueList* GetTruthValues(unsigned long);
   ValueList* GetTruthValues(OperandList*);

   char GetMajorOperator() const;
   ExpressionList* GetSubExpressions();

   const CExpression& operator=(const CExpression&);
   const CExpression& operator=(const CString&);

   //bool LogicallyEquivalent(CExpression&);
   short operator==(CExpression&);

   short LogicallyImplies(CExpression&);
   short operator>(CExpression& e) { return LogicallyImplies(e); }
   
   void clear();
private:
   int m_iNbrOperands;
   int m_iIsValid;
   long m_lNbrCombos;
   CNode * m_pExpTree;
   OperandList * m_pxOperandHead;
   ExpressionList * m_pxExprHead;
   ValueList * m_pxValueHead;
   CString m_strExpression;
   char m_cTrue, m_cFalse;

   // Private Function prototypes.
   int ParseExpression(CString, CString*);
   CNode* BuildExpressionTree(CString, CString*);
   void destroyTree(CNode*);
   //void clear();
   CString getSubExpressions(CNode*);
   void getSubValues(CNode*, OperandList*);
};

#endif
