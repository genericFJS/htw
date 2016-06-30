/************************************************************
Beispiel aus der Vorlesung Programmieren in Java, A. Beck 2010
mit implementiertem Interface
************************************************************/

import java.awt.*;
import java.awt.event.*;

public class Mouse5 extends Panel implements MouseMotionListener
{
  int PosX=20,PosY=20;
  String S;
  public Mouse5(String S)
  {
    this.S=S;   
    setFont(new Font("sanserif",Font.BOLD,24));
    addMouseMotionListener(this);
  }

    //implementierte Funktionen aus MouseMotionListener
    public void mouseDragged(MouseEvent e)
    {
      PosX=e.getX(); PosY=e.getY(); repaint();
    }

    public void mouseMoved(MouseEvent e)
    {
      
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
