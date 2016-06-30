import java.awt.*;
import java.awt.event.*;

public class myPanel extends Panel implements WindowListener
{
  private String myString;

  public void windowActivated(WindowEvent e){}
  public void windowClosed(WindowEvent e){}
  public void windowClosing(WindowEvent e){System.exit(1);}
  public void windowDeactivated(WindowEvent e){}
  public void windowDeiconified(WindowEvent e){}
  public void windowIconified(WindowEvent e){}
  public void windowOpened(WindowEvent e){}


  myPanel(String s)
  {
     myString =s;
  }

  public static void main(String args[])
  {
    Frame   f=new Frame  (args.length>0?args[0]:"no String - no fun");
    myPanel p=new myPanel(args.length>0?args[0]:"no String - no fun");
    System.out.println(p.myString+" in main");
    f.add(p);
    f.addWindowListener(p);
    f.setSize(400,200);
    f.setVisible(true);
    f.repaint();
  }

  @Override
  public void paint(Graphics gc)
  {
    System.out.println(myString+"  in paint");
    gc.drawString(myString,10,20);
  }
}
