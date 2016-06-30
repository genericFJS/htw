import java.awt.*;
import java.awt.event.*;

class Muster extends Panel
{
  // hier Referenzen fuer Komponenten 
  // (Buttons, Textfields, Panels) vereinbaren
  Button OK;


  public Muster()
  {
    // Komponenten erzeugen und zu Oberflaeche zusammenbauen,
    // Listener verbinden
    OK=new Button("OK");
    this.add(OK);
    //addActionListener(...);
  }

  public static void main(String args[])
  {
      Frame F=new Frame();
      F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent we){System.exit(0);}});
      Muster P=new Muster();
      F.add(P);
      F.pack();
      F.setVisible(true);
  }
}