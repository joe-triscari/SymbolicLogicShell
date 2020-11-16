
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari 
 * @version 1.0
 */
package truthtable;

public class ListNode {
  private Object data;
  public ListNode next;

  public ListNode(Object o) { this(o, null); }
  public ListNode(Object o, ListNode nextNode) { data=o; next=nextNode; }

  public Object getObject() { return data; }
  public ListNode getNext() { return next; }
}