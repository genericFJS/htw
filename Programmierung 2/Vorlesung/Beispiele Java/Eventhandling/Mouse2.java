import java.awt.*;
import java.awt.event.*;

public class Mouse2 extends Panel
{
  int PosX=20,PosY=20;
  String S;
  public Mouse2(String S)
  {
    this.S=S;   
    addMouseMotionListener(new myMouseMotionListener());
  }

  // Member Class
  class myMouseMotionListener extends MouseMotionAdapter
  {

    public void mouseDragged(MouseEvent e)
    {
      PosX=e.getX(); PosY=e.getY(); repaint();
    }
  }

  public void paint(Graphics g)
  {
    g.drawString(S,PosX,PosY);
  }


  public static void main(String args[])
  {
    Frame F=new Frame();
    Mouse2 P=new Mouse2(args[0]);
    F.add (P, BorderLayout.CENTER);
    F.setSize(500,200);
    F.setVisible(true);
    F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
  }
}
