import java.awt.*;
import java.awt.event.*;
public class CardPanel extends Panel implements ActionListener
{
  Button b1=new Button("Max");
  Button b2=new Button("Mexi");
  Button b3=new Button("Miss");
  Button b4=new Button("Murks");
  Button b5=new Button("Der große Rest");
  CardLayout cards=new CardLayout();

  public CardPanel()
  {
    setFont(new Font("System",Font.PLAIN,22));
    setLayout(cards);
    add("1",b1); b1.addActionListener(this);
    add("2",b2); b2.addActionListener(this);
    add("3",b3); b3.addActionListener(this);
    add("4",b4); b4.addActionListener(this);
    add("5",b5); b5.addActionListener(this);
  }

  public void actionPerformed(ActionEvent e)
  {
    cards.next(this);
  }
  public static void main(String args[])
  {
    CardPanel p=new CardPanel();
    Frame f=new Frame("CardLayoutPanel");
    f.add(p);

    f.addWindowListener(new WindowAdapter()
              {
                public void windowClosing(WindowEvent e)
                {
                  System.exit(0);
                }
              });

    f.setVisible(true);
    f.pack();
  }
}