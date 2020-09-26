#include "pch.h"
#define _WIN32_WINNT 0x0501 
#include "Client.h"

int main()
{
	Client C;
	boost::asio::io_service ClientService;
	tcp::socket ClientSocket(ClientService);
	ClientSocket.connect(tcp::endpoint(boost::asio::ip::address::from_string("127.0.0.1"), 4523)); //connect with local host , same port to server

	string ClientName;
	string ClientSurname;
	string ClientAm;

	//Enter info to Send to Server to calculate the problem
	cout << "Enter ur Name:";
	cin >> ClientName;
	ClientName += "\n";

	cout << "Enter ur Surname:";
	cin >> ClientSurname;
	ClientSurname += "\n";

	cout << "Enter ur Am:";
	cin >> ClientAm;
	ClientAm += "\n";

	C.SendMsg(ClientSocket, ClientName);
	C.SendMsg(ClientSocket, ClientSurname);
	C.SendMsg(ClientSocket, ClientAm);

	cout << C.RecieveResponse(ClientSocket).c_str() << endl;
} //main
