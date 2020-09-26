package tcpserver;
import java.net.*;
import java.io.*;

public class TCPServer 
{
    public static void main(String args[]) throws Exception 
    {
        ServerSocket SSocket = new ServerSocket(6789);
        int Result = 0;
  
        while(true)
        {
            Socket ConnectionSocket = SSocket.accept(); //returns a Socket object
            InputStreamReader IS = new InputStreamReader(ConnectionSocket.getInputStream());
            
            BufferedReader ClientMsg = new BufferedReader(IS);
            
            String ClientName = ClientMsg.readLine();
            System.out.println("Name:" + ClientName);
            
            String ClientSurname = ClientMsg.readLine();
            System.out.println("SurName:" + ClientSurname);
            
            String ClientAM = ClientMsg.readLine();
            System.out.println("AM:" + ClientAM);
            int AM =  Integer.parseInt(ClientAM);	
            //System.out.println(AM);
            
            DataOutputStream OutToClient = new DataOutputStream(ConnectionSocket.getOutputStream());
            
            if(AM < 0)
            {
                System.out.println("The result is : Error");
                OutToClient.writeBytes("Error" + '\n');
            } //if
            else
            {
                if( ( ( ClientName.length() + ClientSurname.length() ) % 2 ) == 0)
                {
                    for(int i = 0; i <= AM; ++i)
                    {
                        if(i % 2 == 0)
                            ++Result;
                    } //for
                } //even
                else
                {
                    for(int i = 1; i <= AM; ++i)
                    {
                        if(i % 2 != 0)
                            ++Result;
                    } //for
                } //odd
                
                System.out.println("The result is :" + Result);
                String Answer = "The result is :" + Result;
                OutToClient.writeBytes(Answer + '\n');
            } //else        
            Result = 0;
        } //while
    } //main
}
