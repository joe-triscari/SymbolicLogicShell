
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari 
 * @version 1.0
 */
package truthtable;

public abstract class CNode extends Object {
  private CNode m_LeftChild;
  private CNode m_RightChild;
  //private OperandList m_Operands;
  private LinkList m_lstOperands;

  public CNode() {
    m_LeftChild=m_RightChild=null;
    m_lstOperands=null;
  }

  //public abstract int value(OperandList);
  public abstract int value(LinkList l);
  public abstract char symbol();
  public CNode getLeftChild()        { return m_LeftChild; }
  public CNode getRightChild()       { return m_RightChild; }
  public void setLeftChild(CNode p)  { m_LeftChild=p; }
  public void setRightChild(CNode p) { m_RightChild=p; }

  //protected void setOperands(OperandList p) { m_Operands=p; }
  protected void setOperands(LinkList p) { m_lstOperands=p; }
  //protected OperandList getOperands() { return m_Operands; }
  protected LinkList getOperands() { return m_lstOperands; }
  protected int ValueOf(char c)
  {
    if(c=='0' || c=='F') return 0;
    if(c=='1' || c=='T') return 1;

    //OperandList LWalker = m_Operands;
    //while(LWalker != null)
    //{
    //  if(LWalker.cOperand == c) return LWalker.iValue;
    //  LWalker = LWalker.Next;
    //}
    m_lstOperands.moveFirst();
    while(!m_lstOperands.EOL())
    {
      Opdata d = (Opdata)m_lstOperands.getData();
      if(d.cOperand == c) return d.iValue;
      m_lstOperands.moveNext();
    }
    return -999;
  }

} // End of class CNode
