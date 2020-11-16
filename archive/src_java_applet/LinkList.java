
/**
 * Title:        TruthTable <p>
 * Description:  <p>
 * Copyright:    Copyright (c) Joe Triscari <p>
 * Company:      UWM<p>
 * @author Joe Triscari 
 * @version 1.0
 */
package truthtable;

public class LinkList {
  private ListNode first;
  private ListNode last;
  private ListNode cur;

  public LinkList() { first=last=cur=null; }
  public synchronized void moveFirst() { cur=first; }
  public synchronized void moveNext() { if(cur!=null) cur=cur.next; }
  public synchronized ListNode getNext() { if(cur!=null) return cur.next;
                                           else return null;
                                         }
  public synchronized void moveLast() { cur=last; }
  public synchronized boolean EOL() { return cur==null; }
  public synchronized Object getData() { return cur.getObject(); }
  public synchronized void insertAtBack(Object o)
  {
    if(isEmpty())
      first = last = new ListNode(o);
    else
      last = last.next = new ListNode(o);
  }

  public synchronized boolean isEmpty() { return first==null; }

  public synchronized int insertSpecial(Opdata d)
  {
    ListNode tmp=first;
    Opdata e=null;
    boolean exist = false;
    if(first != null) e = (Opdata)first.getObject();
    while(tmp != null && exist==false) // && e.cOperand < d.cOperand)
    {
      if(e.cOperand == d.cOperand) exist = true;
      tmp = tmp.next;
      if(tmp != null) e = (Opdata)tmp.getObject();
    }
    if(exist) return 0;

    insertAtBack(d);
    return 1;
  }

}