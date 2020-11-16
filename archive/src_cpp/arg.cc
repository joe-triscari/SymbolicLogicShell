#include <iostream.h>
#include "CExpression.h"
#include "CString.h"

const int MAX_NBR_EXPR = 256;

int main(int argc, char** argv)
{
   CExpression premises[MAX_NBR_EXPR];
   CExpression conclusion;
   char buf[1024];
   int i = 0;
   CString strBuf;
   int len = 0;

   cout << "1.  ";
   while(cin.getline(buf, 1023))
   {
      strBuf = buf;
      if(strBuf.length() == 0) break;
      premises[i].SetExpression(strBuf);
      if(!premises[i])
      {
	cerr << " Invalid Expression!" << endl;
        exit(1);
      }
     
      if(strBuf.length() > len) len = strBuf.length(); 
    
      i++;
      cout << i+1 << (i+1 < 10 ? ".  " : ". ");
   }
   
   for(int r=0; r < len+4; r++) cout << '-';
   cout << endl << ".'. ";
   cin.getline(buf, 1023);
   strBuf = buf;
   conclusion.SetExpression(strBuf);
   if(!conclusion)
   {
      cerr << " Invalid Expression!" << endl;
      exit(1);
   }

   int j =0;
   CString argument = "";
   for(j=0; j<i-1; j++)
   {
      argument = argument + "(";
   }
   if(i == 1) argument = argument + "(";

   for(j=0; j<i; j++)
   {
      argument = argument + premises[j].GetExpression();
      if(j == i-1) argument = argument + ")";
      else if(j == 0) argument = argument + "&";
      else argument = argument + ")&";
   }

   argument = "(" + argument + ">" + conclusion.GetExpression() + ")";

   //cout << argument << endl;

   CExpression answer(argument);
   if(!answer)
   {
     cerr << "Problem with argument!" << endl;
     exit(1);
   }

   long count = answer.GetCombonationCount();
   long k;
   for(k=0; k<count; k++)
      if(!answer.GetTruthValue(k))
	{
          cout << "Invalid argument." << endl;
          exit(0);
        }

   cout << "Valid argument." << endl;

   return 0;
}





