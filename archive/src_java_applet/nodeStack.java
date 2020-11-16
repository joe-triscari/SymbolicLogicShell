
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari 
 * @version 1.0
 */
package truthtable;

public class nodeStack {
  private CNode m_Cells[];
  private int m_iIndex;

  public nodeStack() { m_iIndex=-1; m_Cells = new CNode[1024]; }
  public void push(CNode c) { m_Cells[++m_iIndex] = c; }
  public CNode pop() { return m_Cells[m_iIndex--]; }
  public int size() { return m_iIndex+1; }
}