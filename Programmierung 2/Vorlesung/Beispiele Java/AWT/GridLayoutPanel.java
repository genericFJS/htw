/*************************************************************************************
Beispiel aus der Vorlesung Programmieren in Java, A. Beck 2010

Das Beispiel demonstriert 5 Arten des Eventhanlings von Actionevents

- ActionListener mit implementiertem Interface "ActionListener"
- ActionListener mit nested top level class
- ActionListener mit memberclass
- ActionListener mit local class
- ActionListener mit anonymous class
- Als Kommentar die deprecated Variante: überschriebene Methode action

*************************************************************************************/



import java.awt.*;
import java.awt.event.*;
public class GridLayoutPanel extends Panel 
implements ActionListener
{
  Panel  PN=new Panel(new GridLayout(2,3));
  Button b1=new Button("Button 1");
  Button b2=new Button("Button 2");
  Button b3=new Button("Button 3");
  Button b4=new Button("Button 4");
  Button b5=new Button("Button 5");

  /* Eventlistener in nested top level class */
  static class myAction3 implements ActionListener
  {
    public void actionPerformed(ActionEvent e)
    {
      System.out.println("Button4 pressed - Eventhandler mit nested top level class"); 
    }
  }


  /* Eventlistener in Memberclass */
  class myAction1 implements ActionListener
  {
    public void actionPerformed(ActionEvent e)
    {
      System.out.println("Button1 pressed - Eventhandler mit MemberClass"); 
    }
  }

  public GridLayoutPanel()
  {
    /* EventListener in Local Class */
    class myAction2 implements ActionListener
    {
      public void actionPerformed(ActionEvent e)
      {
        System.out.println("Button2 pressed - Eventhandler mit local Class"); 
      }
  }
    
    setLayout(new GridLayout(3,2,5,5));
    setFont(new Font("Helvetca",Font.PLAIN,30));
    add(b1); b1.addActionListener(new myAction1());
    add(b2); b2.addActionListener(new myAction2());

    /* EventListener in anonymous class */
    add(b3); b3.addActionListener(new ActionListener()
                   {

                     public void actionPerformed(ActionEvent e)
                     {
                       System.out.println("Button3 pressed - Eventhandler mit anonymous Class"); 
                     }
                   }
                                    );
    add(b4); b4.addActionListener(new myAction3());
    add(b5); b5.addActionListener(this);
  }

  /* EventListener mit implementiertem Interface ActionListener */
  public void actionPerformed(ActionEvent e)
  {
    Button X=(Button)e.getSource();
    
    if (X==b5) System.out.println("Button5 pressed - Eventhandler mit implementiertem Interface ActionListener");
  }

  public static void main(String args[])
  {
    GridLayoutPanel p=new GridLayoutPanel();
    Frame f=new Frame("GridLayoutPanel");
    f.setLayout(new BorderLayout());
    f.add(p,BorderLayout.CENTER);

    f.addWindowListener(new WindowAdapter()
              {
                public void windowClosing(WindowEvent e)
                {
                  System.exit(0);
                }
              });
    f.pack();
    f.setVisible(true);
  }

/*
   //oldstyle  JAVA Eventhandling
   public boolean action(Event evt,Object what)
   {
     Button X=(Button)evt.target;
     if (X==b1) System.out.println("B1 pressed");
     if (X==b2) System.out.println("B2 pressed");
     if (X==b3) System.out.println("B3 pressed");
     if (X==b4) System.out.println("B4 pressed");
     if (X==b5) System.out.println("B5 pressed");
     return (true);
   }

*/


}