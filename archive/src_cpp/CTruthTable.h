/*********************************************************/
/****  CTruthTable.h                                  ****/
/****                                                 ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This file contains the class definition for  ****/
/****    CTruthTable.                                 ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#ifndef _CTRUTH_TABLE_H_
#define _CTRUTH_TABLE_H_

#include <iostream.h>
#include "CExpression.h"

#define TRUE_SYMBOL_DEF  'T'
#define FALSE_SYMBOL_DEF 'F'

class CTruthTable
{
public:
   enum TableStyle { Expanded=0, Normal=1, Default=2 };
   enum TableValue { Tautology=0, Contradiction=1, Contigency=2, Undefined=3 };
   CTruthTable(CExpression e) { m_Expression=e; m_eTableStyle=Normal; }
   ~CTruthTable() { }

   void setTableStyle(TableStyle s) { m_eTableStyle=s; }
   TableStyle getTableStyle() const { return m_eTableStyle; }

   void printTable(ostream*, TableStyle=Default, char='T', char='F');

private:
   CExpression m_Expression;
   TableStyle m_eTableStyle;
};

#endif
