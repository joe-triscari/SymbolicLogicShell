#ifndef __CARGUMENT__H__
#define __CARGUMENT__H__

#include <iostream.h>
#include <fstream.h>
#include "CExpression.h"
#include "CString.h"

class CArgument
{
 public:
  CArgument();  
  ~CArgument();
  short addPremise(const CExpression&);
  short setConclusion(const CExpression&);
  void printASCII(ostream* = &cout);
  int isValid();
  void clear();
 private:
   void refresh();

 private:
   int m_isValid;
   CExpression m_conclusion;
   struct xPremise
   {
      CExpression premise;
      struct xPremise* pNext;
   };
   struct xPremise* m_xPremiseHead;
   struct xPremise* m_xPremiseTail;
   int m_premiseCount;
};

#endif





