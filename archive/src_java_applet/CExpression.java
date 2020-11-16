
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari
 * @version 1.0
 */
package truthtable;

public class CExpression {
   private int m_iNbrOperands;
   private boolean m_bIsValid;
   private long m_lNbrCombos;
   private CNode  m_ExpTree;
   private LinkList m_lstOperand;
   private LinkList m_lstExpr;
   private LinkList m_lstValue;
   private String m_strExpression;
   private char m_cTrue, m_cFalse;

   public CExpression()
   {
     clear();
   }

   public boolean isValid() { return m_bIsValid; }
   public LinkList GetOperands() { return m_lstOperand; }
   public int GetVariableCount()  { return m_iNbrOperands; }
   public long GetCombonationCount()  { return m_lNbrCombos; }
   public String GetExpression() { return m_strExpression; }

   public boolean SetExpression(String strExpr)
   {
     clear();
     m_strExpression=strExpr;

     String strErr=null;
     m_iNbrOperands = ParseExpression(m_strExpression, strErr);
     if(m_iNbrOperands < 0) clear();
     else
     {
       m_lNbrCombos = (long)Math.pow(2.0, (double)m_iNbrOperands);
       m_bIsValid=true;
     }

     if(m_bIsValid)
     {
        m_ExpTree = BuildExpressionTree(m_strExpression, strErr);
        if(m_ExpTree==null) clear();
        else m_bIsValid=true;
     }
     return m_bIsValid;
   }


   public int GetTruthValue(long lNbr)
   {
     if(m_bIsValid)
     {
       if(lNbr >= 0 && lNbr < m_lNbrCombos)
       {
         m_lstOperand.moveFirst();
         for(long j=0; j<m_iNbrOperands; j++)
         {
            Opdata d = (Opdata)m_lstOperand.getData();
            if( (m_lNbrCombos & (lNbr << j+1) ) == 0) d.iValue = 0;
            else d.iValue = 1;
            m_lstOperand.moveNext();
         }
         return m_ExpTree.value(m_lstOperand);
       }
       else return -2;
     }
     else return -3;
   }

   public LinkList GetTruthValues(long lNbr)
   {
     if(m_bIsValid)
     {
       if(lNbr >= 0 && lNbr < m_lNbrCombos)
       {
         m_lstValue = new LinkList();
         m_lstOperand.moveFirst();
         for(long j=0; j<m_iNbrOperands; j++)
         {
            Opdata d = (Opdata)m_lstOperand.getData();
            if( (m_lNbrCombos & (lNbr << j+1)) == 0) d.iValue = 0;
            else d.iValue=1;
            m_lstOperand.moveNext();
         }

         if(GetMajorOperator() == ' ')
            m_lstValue.insertAtBack(new Integer(m_ExpTree.value(m_lstOperand)));
         else
            getSubValues(m_ExpTree, m_lstOperand);

         return m_lstValue;
       }
       else return null;
     }
     else return null;
   }

   public int GetTruthValue(LinkList OpHead)
   {
     if(m_bIsValid)
       return m_ExpTree.value(OpHead);
     else
       return -5;
   }

   public LinkList GetTruthValues(LinkList OpHead)
   {
     if(m_bIsValid)
     {
       m_lstValue=null;
       m_lstValue=new LinkList();
       if(GetMajorOperator() == ' ')
         m_lstValue.insertAtBack(new Integer(m_ExpTree.value(OpHead)));
       else
         getSubValues(m_ExpTree, OpHead);

       return m_lstValue;
     }
     else
       return null;
   }


   public char GetMajorOperator()
   {
     if(m_bIsValid)
     {
       if(m_ExpTree != null)
       {
         char c = m_ExpTree.symbol();
         if(isOperator(c)) return c;
         else return ' ';
       }
       else return ' ';
     }
     else return ' ';
   }


   public LinkList GetSubExpressions()
   {
     if(m_bIsValid)
     {
        if(m_lstExpr==null) m_lstExpr = new LinkList();

        if(!m_lstExpr.isEmpty()) return m_lstExpr;
        else
        {
          if(GetMajorOperator() == ' ')
            m_lstExpr.insertAtBack(GetExpression());
          else
            getSubExpressions(m_ExpTree);

         return m_lstExpr;
       }
     }
     else return null;
   }



   public void clear()
   {
     m_iNbrOperands=0;
     m_lNbrCombos=0;
     m_bIsValid=false;
     m_strExpression = "";
     m_lstOperand=null;
     m_lstExpr=null;
     m_lstValue=null;
     m_ExpTree=null;
   }

   // Private Function.
   private int ParseExpression(String strExpr, String strErrMsg)
   {
     int len = strExpr.length();
     char c;
     int iCount=0;

     m_lstOperand = new LinkList();

     for(int i=0; i<len; i++)
     {
       c = strExpr.charAt(i);

       if( c >= 'a' && c <= 'z')
       {
         Opdata d = new Opdata();
         d.cOperand = c;
         d.iValue = -1;
         iCount += m_lstOperand.insertSpecial(d);
       }
       else if( !isOperator(c) && c != '(' && c != ')' && c != ' ' &&
               c != 'T' && c != 'F' && c != '[' && c != ']' &&
               c != '{' && c != '}')
       {
         strErrMsg = "Invalid character: " + c;
         return -1;
       }
     }
     return iCount;
   }



   private CNode BuildExpressionTree(String strExpr, String strErrMsg)
   {
     char c, cOperator;
     int iLeftParCount=0;
     CNode Node;
     chrStack OperStack = new chrStack();
     nodeStack nStack = new nodeStack();

     int len = strExpr.length();
     for(int i=0; i<len; i++)
     {
       c = strExpr.charAt(i);
       if(c == ' ' || c == '\t') continue;

       if(c == '(' || c == '{' || c == '[')
         iLeftParCount++;
       else if(isOperator(c))
         OperStack.push(c);
       else if(c == ')' || c == '}' || c == ']')
       {
         iLeftParCount--;
         if(OperStack.size() > 0)
         {
           cOperator = OperStack.pop();
           if(cOperator == '!')
           {
             Node = new COperatorNode(cOperator);
             Node.setRightChild( nStack.pop() );
             nStack.push(Node);
           }
           else
           {
             Node = new COperatorNode(cOperator);
             Node.setRightChild( nStack.pop() );
             Node.setLeftChild( nStack.pop() );
             nStack.push(Node);
           }

         }
       }
       else
       {
         Node = new COperandNode(c);
         nStack.push(Node);
       }
     }

     if(iLeftParCount != 0)
     {
       strErrMsg = "Error: Mismatched paranthesis";
       return null;
     }
     else if(OperStack.size() > 0)
     {
       strErrMsg =  "Error: Ambigous expression.";
       return null;
     }

     return nStack.pop();
   }


   private String getSubExpressions(CNode root)
   {
     String cOp1,cOp2,c;
     if(root.getRightChild() != null)
     {
       if(root.getLeftChild() != null)
       {
         cOp1 = getSubExpressions(root.getLeftChild());
         cOp2 = getSubExpressions(root.getRightChild());
         c = "(";
         c = c + cOp1;
         c = c + ((COperatorNode)root).oper();
         c = c + cOp2;
         c = c + ")";
         m_lstExpr.insertAtBack(c);
       }
       else
       {
         cOp1 = getSubExpressions(root.getRightChild());
         c = "(";
         c = c + ((COperatorNode)root).oper();
         c = c + cOp1;
         c = c + ")";
         m_lstExpr.insertAtBack(c);
       }
     }
     else c = "" + root.symbol();

     return c;
   }


   private void getSubValues(CNode root, LinkList OpList)
   {
     if(root.getRightChild() != null)
     {
       if(root.getLeftChild() != null)
       {
         getSubValues(root.getLeftChild(), OpList);
         getSubValues(root.getRightChild(), OpList);
         m_lstValue.insertAtBack(new Integer(root.value(OpList)));
       }
       else
       {
         getSubValues(root.getRightChild(), OpList);
         m_lstValue.insertAtBack(new Integer(root.value(OpList)));
       }
     }
   }

   public static boolean isOperator(char c)
   {
      boolean b = false;
      if(c == '&' || c == '^' || c == '%' || c == '$' || c == '!' ||
         c == '|' || c == '=' || c == '>')
        b = true;

      return b;
   }

}  // End of class
