#include <iostream.h>
#include <stdlib.h>
#include "CArgument.h"
#include "CString.h"


int main()
{
  CArgument arg;
  CExpression expr;
  char buf[1024];
  CString strBuf, strArg;
  const CString sep(" \n\t");
  long i=1;

  cout << "<1>: ";
  while(cin.getline(buf, 1023))
  {
    strBuf = buf;
    strBuf.downcase();
    
    if(strBuf.compare("reset") == 0)
       arg.clear();
    else if(strBuf.compare("exit") == 0)
       return 0;
    else if(strBuf.startsWith("pre"))
    {
       strArg = strBuf.firstToken(sep);
       strArg = CString::nextToken(sep);
       CExpression e(strArg);
       if(!e) cout << "ERROR: Invalid expression." << endl;
       else { cout << "==> Adding premise " << strArg << " ..." << endl;
       arg.addPremise(e); }
    }     
    else if(strBuf.compare("print") == 0)
       arg.printASCII();
    else if(strBuf.startsWith("con"))
    {
       strArg = strBuf.firstToken(sep);
       strArg = CString::nextToken(sep);
       CExpression e(strArg);
       if(!e) cout << "ERROR: Invalid expression." << endl;
       else { cout << "==> setting conclusion " << strArg << " ..." << endl;
       arg.setConclusion(e); }
    }
    else if(strBuf.startsWith("eval"))
    {
      //arg.printASCII();
       if(arg.isValid()) cout << "==> Argument is valid." << endl;
       else cout << "==> Argument is invalid." << endl;
    }
    else
       system(strBuf.chars());
    cout << "<" << ++i << ">: ";
  }

  return 0;
}
