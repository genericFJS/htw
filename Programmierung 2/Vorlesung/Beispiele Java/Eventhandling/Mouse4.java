import java.awt.*;
import java.awt.event.*;

public class Mouse4 extends Panel
{
  int PosX=20,PosY=20;
  String S;
  public Mouse4(String S)
  {
    this.S=S;   
    // anonymous Class
    addMouseMotionListener(new myMouseMotionListener(){
    public void mouseDragged(MouseEvent e)
    {
      PosX=e.getX(); PosY=e.getY(); repaint();
    }
  }
    );
  }

  

  public void paint(Graphics g)
  {
    g.drawString(S,PosX,PosY);
  }


  public static void main(String args[])
  {
    Frame F=new Frame();
    Mouse4 P=new Mouse4(args[0]);
    F.add (P, BorderLayout.CENTER);
    F.setSize(500,200);
    F.setVisible(true);
    F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
  }
}
