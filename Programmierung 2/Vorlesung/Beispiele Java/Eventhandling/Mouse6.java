import java.awt.*;
import java.awt.event.*;
  // non public Class
  class myMouseMotionListener extends MouseMotionAdapter
  {
    Mouse6 M6;
    myMouseMotionListener(Mouse6 M6)
    {
      this.M6=M6;
    }

    public void mouseDragged(MouseEvent e)
    {
      M6.PosX=e.getX(); M6.PosY=e.getY(); M6.repaint();
    }
  }
public class Mouse6 extends Panel
{
  int PosX=20,PosY=20;
  String S;
  public Mouse6(String S)
  {
    this.S=S;      
    setFont(new Font("sanserif",Font.BOLD,24));
    addMouseMotionListener(new myMouseMotionListener(this));
  }

  public void paint(Graphics g)
  {
    g.drawString(S,PosX,PosY);
  }


  public static void main(String args[])
  {
    Frame F=new Frame();
    Mouse6 P=new Mouse6(args[0]);
    F.add (P, BorderLayout.CENTER);
    F.setSize(500,200);
    F.setVisible(true);
    F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
  }
}
