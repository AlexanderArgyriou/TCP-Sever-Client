#pragma once

#include <iostream>
#include <boost/asio.hpp>
#include <string>
using namespace std;
using namespace boost::asio;
using ip::tcp; 

class Server
{
	private:
		string Data;

	public:
		inline Server() noexcept; //Constrctor
		inline ~Server() noexcept; //Destructor
		inline Server(const Server &other) noexcept; //Copy Constructor
		inline Server(Server &&other) noexcept; //move Constructor
		inline const Server &operator=(Server &&other) noexcept; //move operator
		inline const string &Read(tcp::socket &newSocket) noexcept; //Read
		inline void Send(tcp::socket &newSocket, 
			const string &newMsg) const noexcept; //Send
}; //Server Interface

inline Server::Server() noexcept
	: Data("")
{} //Constrctor

inline Server::~Server() noexcept
{
	Data = "";
}//Destructor

inline Server::Server(const Server &other) noexcept
	: Data(other.Data)
{
	if (this == &other)
		return;
}//Copy Constructor

inline Server::Server(Server &&other) noexcept
	: Data("")
{
	if (this != &other)
	{
		Data = move(other.Data);
		other.Data = "";
	} //if
}//move Constructor

inline const Server &Server::operator=(Server &&other) noexcept
{
	if (this != &other)
	{
		Data = move(other.Data);
		other.Data = "";
	} //if
} //move operator

inline const string &Server::Read(tcp::socket &newSocket) noexcept
{
	boost::asio::streambuf Buffer;
	boost::asio::read_until(newSocket, Buffer, "\n");
	Data = boost::asio::buffer_cast<const char *>(Buffer.data());
	
	return Data;
} //Read

inline void Server::Send(tcp::socket &newSocket, 
	const string &newMsg) const noexcept
{
	const string Response = newMsg + "\n";
	boost::asio::write(newSocket, boost::asio::buffer(newMsg));
} //Send 
