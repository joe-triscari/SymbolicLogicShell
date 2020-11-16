/*********************************************************/
/****  truth.cc                                       ****/
/****                                                 ****/
/****  Version: 1.0                                   ****/
/****                                                 ****/
/****  Author:  Joseph N. Triscari                    ****/
/****  Email:   triscaj@yahoo.com                     ****/
/****  Created: 10/5/2000                             ****/
/****                                                 ****/
/****  Description:                                   ****/
/****    This program computes the truth value for    ****/
/****    any valid expression. See README.TXT for     ****/
/****    the rules of valid expressions.              ****/
/****    type truth -h for help.                      ****/
/****                                                 ****/
/****                                                 ****/
/****  An unpublished work. All rights reserved.      ****/
/****                                                 ****/
/****                                                 ****/
/****                                                 ****/
/*********************************************************/

#include <iostream.h>
#include "CExpression.h"
#include "CTruthTable.h"
#include "CString.h"
#include <stdio.h>

#define FLAGS "enf:F:"

struct Options
{
   CString strExpression;
   CString strFile;
   short sAppend;
   CTruthTable::TableStyle eStyle;
   char cTrueSymbol;
   char cFalseSymbol;
};

int getOptions(Options*, int, char**);
void usage();
void showHelp();

int main(int argc, char** argv)
{
   CExpression e;
   Options xOpt;
   ostream * pOutput;
   ofstream out;

   // Set up default options.
   xOpt.strFile = "";
   xOpt.sAppend = 0;
   xOpt.eStyle  = CTruthTable::Normal;
   xOpt.cTrueSymbol = 'T';
   xOpt.cFalseSymbol = 'F';

   if(getOptions(&xOpt, argc, argv) != 0)
      exit(1);  

   if(xOpt.strFile.length() == 0)
      pOutput = &cout;
   else
   {
      if(xOpt.sAppend)
	out.open(xOpt.strFile.chars(), ios::app);
      else
        out.open(xOpt.strFile.chars());
      if(!out)
      {
	cerr << "Error: truth: Could not open output file: \"" 
             << xOpt.strFile << "\"" << endl;
        exit(1);
      }
      pOutput = &out;
   }

   e.SetExpression(xOpt.strExpression);
   if(!e)
   {
     cerr << "Invalid Expression." << endl;
     exit(1);
   }

   CTruthTable t(e);
   (*pOutput) << endl;
   t.printTable(pOutput, xOpt.eStyle, xOpt.cTrueSymbol, xOpt.cFalseSymbol);

   return 0;
}

int getOptions(Options * pxOptions, int argc, char** argv)
{
   int c, iStatus=0;
   extern char * optarg;
   extern int optind;

   while((c = getopt(argc, argv, FLAGS)) != -1)
   {
     switch(c) {
     case 'e':
       pxOptions->eStyle = CTruthTable::Expanded;
     break;
     case 'n':
       pxOptions->eStyle = CTruthTable::Normal;
     break;
     case 'f':
        pxOptions->strFile = optarg;
        pxOptions->sAppend = 0;
     break;
     case 'F':
        pxOptions->strFile = optarg;
        pxOptions->sAppend = 1;
     break;
     case '?':
        iStatus = -1;
        usage();
     break;
     }

   }     

   if(iStatus == 0)
   {
      if(argc - optind == 1)
         pxOptions->strExpression = argv[optind];
      else
      {
         iStatus = -1;
         usage();
      }
   }
  
   return iStatus;
}

void usage()
{
  cout << "usage: truth -en [-fF outfile] expression." << endl;
}
