import java.awt.*;
import java.awt.event.*;

class Action1 extends Panel
{


    public Action1()
    {
       setFont(new Font("System",Font.PLAIN,40));
       Button b1=new Button("TestButton");
       add(b1);
       // ActionListener mit anonymous class
       b1.addActionListener(new ActionListener()
         {public void actionPerformed(ActionEvent e){System.out.println("Action:"+e);}}
                           );
    }

    public static void main(String args[])
    {
      Frame F=new Frame();
      Action1 p=new Action1();
      F.add(p);
      F.setSize(300,150);
      F.setVisible(true);
      F.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
    }
}
