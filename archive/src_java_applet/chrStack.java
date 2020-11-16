
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari 
 * @version 1.0
 */
package truthtable;

public class chrStack
{
  private char m_Cells[];
  private int m_iIndex;

  public chrStack() { m_iIndex=-1; m_Cells = new char[1024]; }
  public void push(char c) { m_Cells[++m_iIndex] = c; }
  public char pop() { return m_Cells[m_iIndex--]; }
  public int size() { return m_iIndex+1; }
}