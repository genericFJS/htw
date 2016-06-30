import java.io.*;
import java.util.*;
import java.lang.*;
import java.net.*;
/*
class dcalc implements Calculate
{
  public double fVonX(double x){return x;}
}
*/

public class dynCalc
{

   String Command;
   double x;
   String Name;

   void calculate(double x)
   {
     /* Durch Einfhrung der Funktion calculate verliert das Objekt
        Class X nach jeder Ausfhrung sein Leben wird also jedesmal
        neu angelegt. */
     Calculate C=null;
     try
     {
      // Get the directory (URL) of the reloadable class
       URL[] urls = null;
       try 
       {
        // Convert the file object to a URL
        File dir = new File(System.getProperty("user.dir")
            +File.separator+"XFX"+File.separator);
        URL url = dir.toURI().toURL();
	System.out.println("URL:"+url);
        urls = new URL[]{url};

       } catch (MalformedURLException e) 
       {
         System.out.println(e);
       }

       try 
       {
         // Create a new class loader with the directory
         ClassLoader cl = new URLClassLoader(urls); //java.net

         // Load in the class
         Class cls = cl.loadClass("dcalc");

         // Create a new instance of the new class
         C = (Calculate)cls.newInstance();
    	} 
        catch (IllegalAccessException e) {System.out.println(e);}
        catch (InstantiationException e) {System.out.println(e);}
        catch (ClassNotFoundException e) {System.out.println(e);}
        System.out.println("Y="+Command);
        System.out.println("Y(x)=Y("+x+")="+C.fVonX(x));
     }
     catch(Exception e){System.out.println("Exception " + e);}
   }

   dynCalc(String Command,double x)
   {
    this.Command=Command;
    this.x      =x;
    go();
   }

   void go()
   {
        while(true)
     {
        try
        {
          
          FileWriter O=new FileWriter("XFX/dcalc.java");
          O.write("public class dcalc implements Calculate\n");
          O.write("{public double fVonX(double x){return "+Command+";}}");
          O.close();
          Process p = Runtime.getRuntime().exec("javac -classpath XFX -d XFX XFX/dcalc.java");
          System.out.println("Compilation of dcalc.java started");
          p.waitFor();

          String line;
          BufferedReader input =
			new BufferedReader(new InputStreamReader(p.getErrorStream()));
           while ((line = input.readLine()) != null)
           {
             System.out.println(line);
           }
           input.close();

	   calculate(x);
           System.out.print("y(x)=");
	   Command=new BufferedReader(new InputStreamReader(System.in)).readLine();
           System.out.print("x   =");
	   x=Double.parseDouble(new BufferedReader(new InputStreamReader(System.in)).readLine());
         }
         catch(Exception e){System.out.println("Exception " + e);}
     }
   }


   public static void main (String args[])
   {
     // args[0]: f(x), z.B.: "x*x" oder Math.sin(x)
     // args[1]: x
     double x;
     try
     {
       new dynCalc(args[0],Double.parseDouble(args[1]));
     }
     catch(Exception e){}
   }
}