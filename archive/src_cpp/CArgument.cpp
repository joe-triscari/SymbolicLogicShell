#include "CArgument.h"

CArgument::CArgument()
{
  m_premiseCount = 0;
  m_xPremiseHead=m_xPremiseTail=NULL;
  m_isValid = -1;
}

CArgument::~CArgument()
{
  clear();
}

void CArgument::clear()
{
  m_premiseCount = 0;
  m_isValid = -1;
  xPremise* pDel=m_xPremiseHead;
  while(m_xPremiseHead)
  {
    pDel = m_xPremiseHead;
    m_xPremiseHead = m_xPremiseHead->pNext;
    delete pDel;
  }
  m_xPremiseHead=m_xPremiseTail=NULL;
  m_conclusion.clear();
}

short CArgument::addPremise(const CExpression& premise)
{
  if(!premise)
  {
     return 0;
  }
  else
  {
     struct xPremise* newpremise = new xPremise;
     newpremise->premise = premise;
     newpremise->pNext = NULL;

     m_premiseCount++;
     if(m_premiseCount == 1)
     {
        m_xPremiseHead=m_xPremiseTail=newpremise;
     }
     else
     {
        m_xPremiseTail->pNext = newpremise;
        m_xPremiseTail = m_xPremiseTail->pNext;
     }       
     m_isValid = -1;
  }

  return 1;
}

short CArgument::setConclusion(const CExpression& concl)
{
  if(!concl)
  {
    return 0;
  }
  else
  {
     m_conclusion = concl;
     m_isValid = -1;
  }
}

void CArgument::printASCII(ostream* out)
{
  int i=1;
  unsigned int len=0;
  xPremise* pTraverse=m_xPremiseHead;
  
  while(pTraverse)
  {
    (*out) << i << ".  " << pTraverse->premise.GetExpression() << endl;
     ++i;
    
    if((pTraverse->premise.GetExpression()).length() > len)
      len = pTraverse->premise.GetExpression().length();

    pTraverse = pTraverse->pNext;
  }
  
  if(m_xPremiseHead)
    { for(int j=0; j<len+4; j++) cout << '-'; cout << endl; }
  
  if((m_conclusion.GetExpression()).length() > 0)
    (*out) << ".'.  "<< m_conclusion.GetExpression() << endl;

}

int CArgument::isValid()
{
  if(m_isValid == -1) refresh();

  return m_isValid;
}

void CArgument::refresh()
{
  int i=1;
  CString strArg;
  CExpression exprArg;
  xPremise* pTraverse = m_xPremiseHead;

  for(int j=0; j < m_premiseCount-1; j++)
    strArg = strArg + "(";

  if(m_premiseCount > 1)
  {
    while(pTraverse)
    {
      if(i == 1)
        strArg = strArg + pTraverse->premise.GetExpression() + "&";
      else if(i == m_premiseCount)
        strArg = strArg + pTraverse->premise.GetExpression() + ")";
      else
        strArg = strArg + pTraverse->premise.GetExpression() + ")&";

      pTraverse = pTraverse->pNext;
       ++i;
    }
  }
  else if(m_premiseCount == 1)
     strArg = pTraverse->premise.GetExpression();

  //if(m_premiseCount == 1) strArg = strArg + ")";

  strArg = "(" + strArg + ">" + m_conclusion.GetExpression() + ")";

  //      cout << strArg << endl;

  m_isValid = 1;

  exprArg.SetExpression(strArg);
  long combos = exprArg.GetCombonationCount();
  for(int k=0; k<combos; k++)
  {
    if(exprArg.GetTruthValue(k) == 0) 
    {
       m_isValid = 0;
       break;
    }
  } 

}


























