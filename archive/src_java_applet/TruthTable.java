
//Title:       TruthTable
//Version:     1.0
//Copyright:   Copyright (c) Joe Triscari 
//Author:      Joe Triscari 
//Company:     UWM
//Description:
//package truthtable;

import java.awt.*;
import java.awt.event.*;
import java.applet.*;
import truthtable.CExpression;
import truthtable.CTruthTable;

public class TruthTable extends Applet implements ActionListener
{
  boolean isStandalone = false;
  TextField txtExpr;
  Button btnExpr;
  TextArea txtTable;
  Checkbox chkExpand;

  //Get a parameter value
  public String getParameter(String key, String def)
  {
    return isStandalone ? System.getProperty(key, def) :
      (getParameter(key) != null ? getParameter(key) : def);
  }

  //Construct the applet
  public TruthTable()
  {
  }

  //Initialize the applet
  public void init()
  {
    Font mono = new Font("Monospaced", Font.PLAIN, 12);
    setLayout(new BorderLayout());

    txtExpr = new TextField(40);
    txtExpr.setFont(mono);

    txtTable = new TextArea(10, 40);
    txtTable.setFont(mono);
    txtTable.setEditable(false);

    btnExpr = new Button("Evaluate");
    btnExpr.addActionListener(this);


    chkExpand = new Checkbox("Expand");
    chkExpand.setState(true);
    
    Panel a = addVariableButtons();
    Panel b = addOperatorButtons();
    Panel c = addParanthesisButtons();

    a.add(chkExpand);

    add("North", txtExpr);
    add("Center", a);
    add("East", b);
    add("West", c);
    add("South", txtTable);


    setSize(400, 250);
  }

  public void actionPerformed(ActionEvent e)
  {
     Button b = (Button)e.getSource();
     //if(b.equals(btnExpr))
     if(b.getLabel() == "Equal")
     {
        CExpression ex = new CExpression();
        ex.SetExpression(txtExpr.getText());
        if(ex.isValid())
        {
           CTruthTable t = new CTruthTable(ex);
           txtTable.setText(t.printTable(chkExpand.getState()));
        }
        else
           txtTable.setText("Invalid Expression");
     }
     else if(b.getLabel() == "Clear")
	 {
        txtExpr.setText("");
        txtTable.setText("");
	 }
     else if(b.getLabel() == "Back")
     {
        String str = txtExpr.getText();
        if(str.length() > 0)
           txtExpr.setText( str.substring(0, str.length()-1) );
     }
  }

  public Panel addVariableButtons()
  {
     Panel c = new Panel();
     c.setLayout(new GridLayout(6,5));
     Button btn;
     char ch = 'a';

     for(int i=0; i < 26; i++, ch++)
     {
        btn = new Button(String.valueOf(ch));
        btn.setBackground(Color.darkGray);
        btn.setForeground(Color.white);
        c.add(btn);
        btn.addActionListener(
           new ActionListener() {
              public void actionPerformed(ActionEvent e)
                { variableActionPerformed(e); }
           }
        );
     }

     btn = new Button("Equal");
     btn.setBackground(Color.green);
     btn.addActionListener(this);
     c.add(btn);

     btn = new Button("Back");
     btn.setBackground(Color.white);
     btn.setForeground(Color.red);
     btn.addActionListener(this);
     c.add(btn);

     btn = new Button("Clear");
     btn.setBackground(Color.yellow);
     btn.addActionListener(this);
     c.add(btn);

     return c;
  }

  // This function is for the variable buttons.
  public void variableActionPerformed(ActionEvent e)
  {
     Button b = (Button)e.getSource();
     txtExpr.setText(txtExpr.getText() + b.getLabel());
  }

  public String insertText(String src, String insert, int position)
  {
     String result = "";
     for(int i=0; i<src.length(); i++)
        if(i == position)
           result += insert + src.charAt(i);
        else
           result += src.charAt(i);
     return result;
  }

  public Panel addOperatorButtons()
  {
     Panel c = new Panel();
     c.setLayout(new GridLayout(4,2));
     Button btn;
     char op[] = {'&','|','!','=','^','%','$','>'};
     String toolTip[] = {"AND","OR","NOT","BICONDITIONAL","EXCLUSIVE OR",
                         "NOR", "NAND", "CONDITIONAL"};

     for(int i=0; i < 8; i++)
     {
        btn = new Button(String.valueOf(op[i]));
        btn.setBackground(Color.blue);
        btn.setForeground(Color.white);
        c.add(btn);
        btn.addActionListener(
           new ActionListener() {
              public void actionPerformed(ActionEvent e)
                { operatorActionPerformed(e); }
           }
        );
     }

     return c;
  }

  // This function is for operator buttons.
  public void operatorActionPerformed(ActionEvent e)
  {
     Button b = (Button)e.getSource();
     txtExpr.setText(txtExpr.getText() + b.getLabel());
  }

  public Panel addParanthesisButtons()
  {
     Panel c = new Panel();
     c.setLayout(new GridLayout(4,2));
     Button btn;
     char paran[] = {'T','F','(',')','[',']','{','}'};

     for(int i=0; i < 8; i++)
     {
        btn = new Button(String.valueOf(paran[i]));
        if(paran[i] == 'T' || paran[i] == 'F')
	{
           btn.setBackground(Color.black);
           btn.setForeground(Color.white);
	}
        else
	{
           btn.setBackground(Color.magenta);
           btn.setForeground(Color.white);
	}
        c.add(btn);
        btn.addActionListener(
           new ActionListener() {
              public void actionPerformed(ActionEvent e)
                { paranthesisActionPerformed(e); }
           }
        );
     }

     return c;
  }
  // This function is for paranthesis buttons.
  public void paranthesisActionPerformed(ActionEvent e)
  {
     Button b = (Button)e.getSource();
     txtExpr.setText(txtExpr.getText() + b.getLabel());
  }



  //Component initialization
  private void jbInit() throws Exception
  {
    this.setSize(new Dimension(400,300));
  }

  //Start the applet
  public void start()
  {
  }

  //Stop the applet
  public void stop()
  {
  }

  //Destroy the applet
  public void destroy()
  {
  }

  //Get Applet information
  public String getAppletInfo()
  {
    return "Applet Information";
  }

  //Get parameter info
  public String[][] getParameterInfo()
  {
    return null;
  }

  //static initializer for setting look & feel
  static
  {
    try
    {
      //UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
      //UIManager.setLookAndFeel(UIManager.getCrossPlatformLookAndFeelClassName());
    }
    catch(Exception e)
    {
    }
  }
}
