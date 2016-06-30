import java.awt.*;
import java.awt.event.*;

class AwtComps extends Panel
{
  Panel P;

  Button    B=new Button("Hans Huckebein");
  TextField F=new TextField("Witwe Bolte");
  TextArea  A=new TextArea("Max\n&\nMoritz",5,19);
  List      L=new List(4);
  Checkbox  H=new Checkbox("Plisch & Plum");
  Choice    X=new Choice();
  Scrollbar S=new Scrollbar(Scrollbar.HORIZONTAL,50,33,0,100);

  public AwtComps()
  {
    setLayout(new GridBagLayout());
    GridBagConstraints C=new GridBagConstraints();
    C.fill=GridBagConstraints.NONE	;
    C.insets=new Insets(10,10,10,10);
    C.gridx=0; C.gridy=0;
    C.ipadx=5; C.ipady=5;
    add(P=new Panel(new BorderLayout()),C);
    P.add(new Label("Button:"),BorderLayout.NORTH);
    P.add(B,BorderLayout.CENTER);

    C.gridx++;
    add(P=new Panel(new BorderLayout()),C);
    P.add(new Label("TextField:"),BorderLayout.NORTH);
    P.add(F,BorderLayout.CENTER);

    C.gridx++;
    add(P=new Panel(new BorderLayout()),C);
    P.add(new Label("TextArea:"),BorderLayout.NORTH);
    P.add(A,BorderLayout.CENTER);

    C.gridx=0; C.gridy++;

    add(P=new Panel(new BorderLayout()),C);
    P.add(new Label("List:"),BorderLayout.NORTH);
    P.add(L,BorderLayout.CENTER);
    L.add("Lempel"); L.add("Bolte"); L.add("Mäcke");

    C.gridx++;
    add(P=new Panel(new BorderLayout()),C);
    P.add(new Label("Checkbox:"),BorderLayout.NORTH);
    P.add(H,BorderLayout.CENTER);

    C.gridx++;
    add(P=new Panel(new BorderLayout()),C);
    P.add(new Label("Choice:"),BorderLayout.NORTH);
    P.add(X,BorderLayout.CENTER);
    X.add("Lempel"); X.add("Bolte"); X.add("Mäcke");

    C.gridx=0; C.gridy++;
    C.fill=GridBagConstraints.HORIZONTAL;
    add(P=new Panel(new BorderLayout()),C);
    P.add(new Label("Scrollbar:"),BorderLayout.NORTH);
    P.add(S,BorderLayout.CENTER);

    C.gridx++;
    add(P=new Panel(new BorderLayout()),C);
    P.setLayout(new GridLayout(4, 1));
    P.add(new Label("Group of Radiobuttons:"));
    CheckboxGroup cbg = new CheckboxGroup();
    P.add(new Checkbox("Schneider", cbg, true));
    P.add(new Checkbox("Lehrer   ", cbg, false));
    P.add(new Checkbox("Bäcker   ", cbg, false));


  }
  public static void main(String args[])
  {
      Frame F=new Frame();
      F.addWindowListener(new WindowAdapter()
           {public void windowClosing(WindowEvent W){System.exit(0);}});
      AwtComps P=new AwtComps();
      F.add(P);
      F.pack();
      F.setVisible(true);
  }
}