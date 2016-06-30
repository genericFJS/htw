import java.awt.*;
import java.awt.event.*;

public class Mouse5 extends Panel
{
  int PosX=20,PosY=20;
  String S;
  public Mouse5(String S)
  {
    this.S=S;   
    addMouseMotionListener(new myMouseMotionListener(this));
  }

  // Member Class
  static class myMouseMotionListener extends MouseMotionAdapter
  {
    Mouse5 M5;
    myMouseMotionListener(Mouse5 M5)
    {
      this.M5=M5;
    }

    public void mouseDragged(MouseEvent e)
    {
      M5.PosX=e.getX(); M5.PosY=e.getY(); M5.repaint();
    }
  }

  public void paint(Graphics g)
  {
    g.drawString(S,PosX,PosY);
  }


  public static void main(String args[])
  {
    Frame F=new Frame();
    Mouse5 P=new Mouse5(args[0]);
    F.add (P, BorderLayout.CENTER);
    F.setSize(500,200);
    F.setVisible(true);
    F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
  }
}
