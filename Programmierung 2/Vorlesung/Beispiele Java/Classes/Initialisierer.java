 
public class Initialisierer
{

  private String TestStr;

  {
    TestStr="Max"+" & "+"Moritz";
  }

  public String getStr()
  {
    return TestStr;
  }

  public static void main(String args[])
  {
     Initialisierer meinObject=new Initialisierer();
     System.out.println(meinObject.getStr());
  }


}
