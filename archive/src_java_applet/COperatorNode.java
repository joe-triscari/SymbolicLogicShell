
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari 
 * @version 1.0
 */
package truthtable;

public final class COperatorNode extends CNode {
  private char m_cOperator;

  public COperatorNode(char c)
  {
    m_cOperator = c;
  }

  public char oper() { return m_cOperator; }
  //public int value(OperandList p) { setOperands(p); return Eval(this); }
  public int value(LinkList p) { setOperands(p); return Eval(this); }
  public char symbol() { return m_cOperator; }

  private int m_EvaluateFunc(int iLhs, int iRhs, char cOperator)
  {
     int i=0;
     switch(cOperator)
     {
        case '&':
          if(iLhs==1 && iRhs==1) i=1;
          else i=0;
        break;
        case '|':
          if(iLhs==1 || iRhs==1) i=1;
          else i=0;
        break;
        case '$':
          if(iLhs==1 && iRhs==1) i=0;
          else i=1;
        break;
        case '%':
          if(iLhs==1 || iRhs==1) i=0;
          else i=1;
        break;
        case '!':
          i = (iLhs==1 ? 0 : 1);
        break;
        case '>':
          i = (iLhs==1 && iRhs==0 ? 0 : 1);
        break;
        case '=':
          i = (iLhs==iRhs ? 1 : 0);
        break;
        case '^':
          i = (iLhs!=iRhs ? 1 : 0);
        break;
     }
     return i;
  }

  private int Eval(CNode ptr)
  {
    int iOp1,iOp2,iVal;

    if(ptr.getRightChild() != null)
    {
      if(ptr.getLeftChild() != null)
      {
        iOp1 = Eval(ptr.getLeftChild());
        iOp2 = Eval(ptr.getRightChild());
        iVal = m_EvaluateFunc(iOp1, iOp2, ((COperatorNode)ptr).oper());
      }
      else
      {
        iOp1 = Eval(ptr.getRightChild());
        iVal = m_EvaluateFunc(iOp1, 0, ((COperatorNode)ptr).oper());
      }
    }
    else
      iVal=ptr.value(getOperands());

    return iVal;
  }

}