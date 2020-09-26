package tcpclient;
import java.net.*;
import java.io.*;
import java.util.Scanner;

public class TCPClient 
{
    public static void main(String[] args) throws Exception
    {
        Socket ClientSocket = new Socket("localhost",6789);
        DataOutputStream OutToServer = new DataOutputStream(ClientSocket.getOutputStream());
        
        Scanner Scan = new Scanner(System.in);
        System.out.println("Name:");
        String Name = Scan.nextLine();
        OutToServer.writeBytes(Name + '\n');
        
        System.out.println("Surname:");
        String SurName = Scan.nextLine();
        OutToServer.writeBytes(SurName + '\n');
        
        System.out.println("AM:");
        String AM = Scan.nextLine();
        OutToServer.writeBytes(AM + '\n');
        
        // OutToServer.writeBytes("Alex" + '\n');
        // OutToServer.writeBytes("Argyriou" + '\n');
        // OutToServer.writeBytes("-3" + '\n');
        
        InputStreamReader FromServer = new InputStreamReader(ClientSocket.getInputStream());
        BufferedReader ServerMsg = new BufferedReader(FromServer);
        String ServerAnswer = ServerMsg.readLine();
        
        System.out.println(ServerAnswer);
        
        ClientSocket.close();
    }
}
