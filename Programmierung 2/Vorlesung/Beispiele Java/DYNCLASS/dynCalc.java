import java.io.*;
import java.util.*;
import java.lang.*;

class ccalc implements Calculate
{
public double fVonX(double x){return x;}
}


public class dynCalc
{

   String Command;
   double x;
   int Count=0;
   String Name;

   void calculate(double x)
   {
     /* Durch Einführung der Funktion calculate verliert das Objekt
        Class X nach jeder Ausführung sein Leben wird also jedesmal
        neu angelegt. */
     try
     {
       Class X=Class.forName(Name);
       Calculate C=(Calculate)(X.newInstance());
       System.out.println("Y(x)="+C.fVonX(x));
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
          Name="dcalc"+Count; // Hier wird der Name zusammengebaut
          FileWriter O=new FileWriter(Name+".java");
          O.write("class "+Name+" implements Calculate\n");
          O.write("{public double fVonX(double x){return "+Command+";}}");
          O.close();
          Process p = Runtime.getRuntime().exec("javac "+Name+".java");
          System.out.println("Compilation of "+Name+" started");
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
	     Runtime.getRuntime().gc();
	     Command=
               new BufferedReader(new InputStreamReader(System.in)).readLine();
          }
          catch(Exception e){System.out.println("Exception " + e);}
          Count++;

     }
   }


   public static void main (String args[])
   {
     double x;
     try
     {
       new dynCalc(args[0],Double.parseDouble(args[1]));
     }
     catch(Exception e){}
   }
}