#pragma once

#include <iostream>
#include <boost/asio.hpp>
using namespace std;
using namespace boost::asio;
using ip::tcp;

class Client
{
	private:
		string Data;

	public:
		inline Client() noexcept; //Constrctor
		inline ~Client() noexcept; //Destructor
		inline Client(const Client &other) noexcept; //Copy Constructor
		inline Client(Client &&other) noexcept; //move Constructor
		inline const Client &operator=(Client &&other) noexcept; //move operator
		inline void SendMsg(tcp::socket &newSocket,
			const string &newMsg) const noexcept; //SendMsg
		inline const string &RecieveResponse(tcp::socket &newSocket) noexcept; //RecieveResponse
}; //Client Interface

inline Client::Client() noexcept
	: Data("")
{} //Constrctor

inline Client::~Client() noexcept
{
	Data = "";
}//Destructor

inline Client::Client(const Client &other) noexcept
	: Data(other.Data)
{
	if (this == &other)
		return;
}//Copy Constructor

inline Client::Client(Client &&other) noexcept
	: Data("")
{
	if (this != &other)
	{
		Data = move(other.Data);
		other.Data = "";
	} //if
}//move Constructor

inline const Client &Client::operator=(Client &&other) noexcept
{
	if (this != &other)
	{
		Data = move(other.Data);
		other.Data = "";
	} //if
} //move operator

inline void Client::SendMsg(tcp::socket &newSocket,
	const string &newMsg) const noexcept
{
	boost::asio::write(newSocket, boost::asio::buffer(newMsg));
} //SendMsg

inline const string &Client::RecieveResponse(tcp::socket &newSocket) noexcept
{
		boost::asio::streambuf RecieveBuffer;
		boost::system::error_code Error;
		boost::asio::read(newSocket, RecieveBuffer, boost::asio::transfer_all(),Error);

		if (Error && Error != boost::asio::error::eof)
		{
			cout << "receive failed: " << Error.message() << endl;
			exit(1);
		} //if
		else
		{
			Data = boost::asio::buffer_cast<const char *>(RecieveBuffer.data());
		} //else

		return Data;
} //SendMsg