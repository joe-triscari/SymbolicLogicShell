
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari<p>
 * Company:      UWM<p>
 * @author Joe Triscari
 * @version 1.0
 */
package truthtable;

public class CTruthTable {
  private CExpression m_Expression;
  private boolean m_bFullTable;
  private char m_cTrueSymbol;
  private char m_cFalseSymbol;

  public CTruthTable(CExpression e)
  {
    m_Expression = e;
    m_bFullTable = false;
    m_cTrueSymbol = 'T';
    m_cFalseSymbol = 'F';
  }

  public String printTable(boolean bStyle)
  {
    long lCombos=0;
    LinkList lstOperands=null;
    LinkList lstExpr=null;
    String strPrint="";
    int len = 0;

    m_bFullTable = bStyle;
    lCombos = m_Expression.GetCombonationCount();
    lstOperands = m_Expression.GetOperands();

    // PRINT THE OPERANDS.
    lstOperands.moveFirst();
    while(!lstOperands.EOL())
    {
      Opdata d = (Opdata)lstOperands.getData();
      strPrint += String.valueOf(d.cOperand);
      lstOperands.moveNext();
    }

    if(m_bFullTable == false)  // PRINT THE EXPRESSION.
    {
       strPrint += "| " + m_Expression.GetExpression() + "\n";

       // PRINT THE HORIZONTAL BORDER.
       for(int i=0;  i < m_Expression.GetVariableCount() +
                     m_Expression.GetExpression().length() + 2; i++)
         strPrint += (i == m_Expression.GetVariableCount() ? "|" : "-");

       strPrint += "\n";
    }
    else  // PRINT ALL THE SUB EXPRESSIONS.
    {
      lstExpr = m_Expression.GetSubExpressions();
      int iCount=0;
      lstExpr.moveFirst();
      while(!lstExpr.EOL())
      {
         strPrint += (iCount==0 ? "| " : " | ") +
                     (String)lstExpr.getData();
         ++iCount;
         lstExpr.moveNext();
      }
      strPrint += "\n";

      for(int i=0; i<m_Expression.GetVariableCount(); i++)
        strPrint += "-";

      strPrint += "|";
      lstExpr.moveFirst();
      while(!lstExpr.EOL())
      {
          len = ((String)lstExpr.getData()).length();
          for(int i=0; i<len+2; i++)
            strPrint += "-";
          if(lstExpr.getNext() != null) strPrint += "|";
          lstExpr.moveNext();
      }
      strPrint += "\n";
   }

    //for(long i=0; i<lCombos; i++)
   for(long i=lCombos-1; i >= 0; i--)
   {
      for(int k=0; k<m_Expression.GetVariableCount(); k++)
        if( (lCombos & (i << k+1)) != 0)
          strPrint += String.valueOf(m_cTrueSymbol);
        else
          strPrint += String.valueOf(m_cFalseSymbol);

      if(m_bFullTable == false)
      {
         strPrint += "| ";
         if(m_Expression.GetTruthValue(i)==1)
           strPrint += String.valueOf(m_cTrueSymbol);
         else
           strPrint += String.valueOf(m_cFalseSymbol);
         strPrint += "\n";
      }
      else
      {
         LinkList lstVal = m_Expression.GetTruthValues(i);
         lstExpr.moveFirst();
         strPrint += "| ";
         lstVal.moveFirst();
         while(!lstVal.EOL())
         {
            Integer iTmp = (Integer)lstVal.getData();
            if(iTmp.intValue() == 1)
              strPrint += String.valueOf(m_cTrueSymbol);
            else
              strPrint += String.valueOf(m_cFalseSymbol);

            if(lstVal.getNext() != null)
            {
               len = ((String)lstExpr.getData()).length();
               for(int j=0; j<len; j++)
                 strPrint += " ";
               strPrint += "| ";
            }
            lstVal.moveNext();
            lstExpr.moveNext();
         }
         strPrint += "\n";
      }

   }

   return strPrint;
}

} // End of class
