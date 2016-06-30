import java.awt.*;
import java.awt.event.*;

public class Mouse3 extends Panel
{
  int PosX=20,PosY=20;
  String S;
  public Mouse3(String S)
  {
    this.S=S;     
    class myMouseMotionListener extends MouseMotionAdapter
    {
      public void mouseDragged(MouseEvent e)
      {
        PosX=e.getX(); PosY=e.getY(); repaint();
      }
    }

    addMouseMotionListener(new myMouseMotionListener());
  }


  public void paint(Graphics g)
  {
    g.drawString(S,PosX,PosY);
  }


  public static void main(String args[])
  {
    Frame F=new Frame();
    Mouse3 P=new Mouse3(args[0]);
    F.add (P, BorderLayout.CENTER);
    F.setSize(500,200);
    F.setVisible(true);
    F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
  }
}
