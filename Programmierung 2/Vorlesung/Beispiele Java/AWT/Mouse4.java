/**************************************************************
Beispiel aus der Vorlesung Programmieren in Java, A. Beck 2010
MouseMotionListener mit nested top level class

**************************************************************/
import java.awt.*;
import java.awt.event.*;

public class Mouse4 extends Panel
{
  int PosX=20,PosY=20;
  String S;
  // nested top level Class
  static class myMouseMotionListener extends MouseMotionAdapter
  {
    // Hat keinen Zugang zu den Instanzdaten der umgebenden
    // Klasse, deshalb Konstuktor nötig
    Mouse4 M;
    myMouseMotionListener(Mouse4 M)
    {
      this.M=M;
    } 
    public void mouseDragged(MouseEvent e)
    {
      M.PosX=e.getX(); M.PosY=e.getY(); M.repaint();
    }
  }

  public Mouse4(String S)
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
    Mouse4 P=new Mouse4(args[0]);
    F.add (P, BorderLayout.CENTER);
    F.setSize(500,200);
    F.setVisible(true);
    F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
  }
}
