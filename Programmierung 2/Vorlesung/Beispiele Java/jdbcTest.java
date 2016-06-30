import java.sql.*;

// verwendet mysql-connector-java-3.0.15-ga-bin.jar
// Aufruf:
// java -cp mysql-connector-java-3.0.15-ga-bin.jar:. jdbcTest
// A. Beck
public class jdbcTest
{
  public static void main(String args[])
  {
    Connection con;
    Statement  stmnt;
    ResultSet  Rs;
    try 
    {
//      Class.forName("gwe.sql.gweMysqlDriver");
      Class.forName("org.gjt.mm.mysql.Driver");

      String url = "jdbc:mysql://localhost:3306/addresses";
        
      con = DriverManager.getConnection(url,"user","password");
      if (con!=null)
      {
        String Query="Select * from AddrB where Town='Buschhausen'";
        stmnt=con.createStatement();
        Rs=stmnt.executeQuery(Query);
        while(Rs.next())
        {
          System.out.printf("%-10s %-10s %-15s %05d,%s\n",
                            Rs.getString(2),
                            Rs.getString(3),
                            Rs.getString(4),
                            Rs.getInt(5),
                            Rs.getString(6));
        }
      }
    }
    catch(Exception e)
    {
      System.out.println(e); e.printStackTrace();
    }

  }
}
