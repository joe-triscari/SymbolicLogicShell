
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari 
 * @version 1.0
 */
package truthtable;

public final class COperandNode extends CNode {
  private char m_cOperand;

  public COperandNode(char c) { m_cOperand=c; }
  public int value(LinkList p)
  {
    setOperands(p);
    return ValueOf(m_cOperand);
  }
  public char symbol() { return m_cOperand; }

}