import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.net.*;
import javax.swing.*;
import javax.swing.event.*;
import javax.swing.text.html.*;
 

class TestEditorPane
{
  public static void main(String args[])
  {
    try
    {
      JEditorPane p=new JEditorPane(new URL(args[0]));
      JScrollPane x=new JScrollPane(p);
      p.setEditable(false);
      p.addHyperlinkListener(new Hyperactive());
      JFrame f=new JFrame(args[0]);
      f.getContentPane().add(x);
      f.setVisible(true);
      f.setSize(1024,768);
      f.addWindowListener(new WindowAdapter(){public void windowClosing(WindowEvent e){System.exit(0);}});
    }catch (Exception e){System.out.println(e);}
  }

  static class Hyperactive implements HyperlinkListener
  {
    public void hyperlinkUpdate(HyperlinkEvent e) 
    {
       if (e.getEventType() == HyperlinkEvent.EventType.ACTIVATED) 
       {
         JEditorPane pane = (JEditorPane) e.getSource();
         if (e instanceof HTMLFrameHyperlinkEvent) 
         {
 	   HTMLFrameHyperlinkEvent  evt = (HTMLFrameHyperlinkEvent)e;
 	   HTMLDocument doc = (HTMLDocument)pane.getDocument();
 	   doc.processHTMLFrameHyperlinkEvent(evt);
 	 } else 
         {
 	    try {pane.setPage(e.getURL()); }
            catch (Throwable t) {t.printStackTrace(); }
         }
       }
    }
  }
}
