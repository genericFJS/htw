import java.awt.*;
import java.awt.event.*;

class Action2 extends Panel implements ActionListener
{


    public Action2()
    {
       setFont(new Font("System",Font.PLAIN,40));
       Button b1=new Button("TestButton");
       add(b1);
       // ActionListener mit anonymous class
       b1.addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
       System.out.println("Action:"+e);
    }

    public static void main(String args[])
    {
      Frame F=new Frame();
      Action2 p=new Action2();
      F.add(p);
      F.setSize(300,150);
      F.setVisible(true);
      F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
    }
}