/**************************************************************
Beispiel aus der Vorlesung Programmieren in Java, A. Beck 2010
MouseMotionListener mit anonymous Class

**************************************************************/

import java.awt.*;
import java.awt.event.*;


public class Mouse1 extends Panel
{


  int PosX=20,PosY=20;
  String S;

  public Mouse1(String S)
  {
    final int i;
 
    this.S=S;
    setFont(new Font("sanserif",Font.BOLD,24));

    addMouseMotionListener(new MouseMotionAdapter()
                                {
                                   public void mouseDragged(MouseEvent e)
                                   {
                                      PosX=e.getX(); PosY=e.getY(); repaint();
                                   }
                                });
  }
 
  public void paint(Graphics g)
  {
    g.drawString(S,PosX,PosY);
    // g.fillRect(PosX,PosY,25,25);
  }

  public static void main(String args[])
  {
    Frame F=new Frame();
    Mouse1 P=new Mouse1(args[0]);
    F.add (P, BorderLayout.CENTER);
    F.setSize(500,200);
    F.setVisible(true);
    F.addWindowListener(new WindowAdapter()
         {public void windowClosing(WindowEvent e){System.exit(0);}});
  }
}
