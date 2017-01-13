package test;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress; 
  
class UDPServer { 
  public static void main(String args[]) throws Exception 
    {   
      DatagramSocket serverSocket = new DatagramSocket(9876); 
  
      byte[] receiveData = new byte[1024]; 
      byte[] sendData  = new byte[1024]; 
  
      while(true) 
        { 
          DatagramPacket receivePacket =  new DatagramPacket(receiveData, receiveData.length); 
          serverSocket.receive(receivePacket); 
          String sentence = new String(receivePacket.getData()); 
  
          InetAddress IPAddress = receivePacket.getAddress(); 
  
          int port = receivePacket.getPort(); 
  
          String capitalizedSentence = sentence.toUpperCase(); 

          sendData = capitalizedSentence.getBytes(); 
          
          Thread.sleep(5000);
  
          DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port);
  
          serverSocket.send(sendPacket); 
        } 
    } 
}
