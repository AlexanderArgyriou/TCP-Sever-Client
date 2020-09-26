#include "pch.h"
#define _WIN32_WINNT 0x0501 
#include "Server.h"

int main()
{
	cout << "Server is Running..." << endl << endl;

	for (;;)
	{
		Server newServer;
		boost::asio::io_service NewService;
		tcp::acceptor NewAcceptor(NewService, tcp::endpoint(tcp::v4(), 4523)); //listen to new Connection
		tcp::socket ServerSocket(NewService); //ServerSide Socket creation
		NewAcceptor.accept(ServerSocket); //waiting for connection

		//After Connection enstablished
		string ClientGetName = newServer.Read(ServerSocket); //Catch client MsgName
		string ClientGetSurname = newServer.Read(ServerSocket); //Catch client MsgSurname
	    string ClientGetAM = newServer.Read(ServerSocket); //Catch client MsgAm
		int ResponseResult = 0;

		cout << "Client Name: " << ClientGetName.c_str();
		cout << "Client Surname: " << ClientGetSurname.c_str();
		cout << "Client Am: " << ClientGetAM.c_str();

		if (stoi(ClientGetAM) < 0)
		{
			cout << "Negative AM Error" << endl;
			newServer.Send(ServerSocket, "Negative AM Error"); //Response
		}//if
		else
		{
			if (((ClientGetName.length() + ClientGetSurname.length()) % 2) == 0) //name + surname letters are even
			{
				for (int i = 0; i <= stoi(ClientGetAM); ++i)
				{
					if (i % 2 == 0)
						++ResponseResult; //number of even numbers from 0-ClientAm
				} //for
			} //if
			else
			{
				for (int i = 1; i <= stoi(ClientGetAM); ++i) //name + surname letters are odd
				{
					if (i % 2 != 0)
						++ResponseResult; //number of odd numbers from 1-ClientAm
				} //for
			} //else 

			cout << "Result sent Back:" << to_string(ResponseResult).c_str() << endl;
			string Return = "The Result is:" + to_string(ResponseResult) + "\n";
			newServer.Send(ServerSocket, Return); //Response
		} //else
		cout << endl;
		ResponseResult = 0; //reset
	} //for infinite loop

	return 0;
} //main


