#include <iostream>
#include <boost/asio.hpp>
#include <string>
#include <vector>
#include <stdexcept>
#include <thread>
#include <future>
#include <boost/system/error_code.hpp>
#include "ComReader.h"
#include "Message.h"

const char* ReadString( const char* port_name , size_t number)
{
	std::cout << "start reading\n";
	char c;
	std::string curr_string = "";
	int port = open(port_name, O_RDONLY);
	if (port < 0)
	{
		printf("Error %i from open: %s\n", errno, strerror(errno));
		return "";
	}
	while(true)
	{
		std::cout << "reading\n"; 
		std::future_status status;
		auto r = std::async(std::launch::async,[&]{return read(port, &c,1);});
		status = r.wait_for(std::chrono::seconds(4));
		if (status == std::future_status::timeout)
		{
			std::cout << "read from com timeout\n";
			return curr_string.c_str();
		}
		else
		{
		r.get(); 
		switch(c)
		{
			case '\n':
			std::cout << "read " << curr_string << std::endl;
			curr_string += c;
			return curr_string.c_str();
			default:
				std::cout << "read char " << c << std::endl;
				curr_string += c;
		}
		}
	}
	
	return 0;
    }

int sendBytesToUdp(const char* bytes, const char* port_num)
{
	boost::system::error_code err;
	boost::asio::io_service io_service;
	boost::asio::ip::udp::socket socket(io_service);
	socket.open(boost::asio::ip::udp::v4(), err);
    if (!err)
    {
		socket.set_option(boost::asio::ip::udp::socket::reuse_address(true));
		socket.set_option(boost::asio::socket_base::broadcast(true));
		boost::asio::ip::udp::endpoint Endpoint(boost::asio::ip::address_v4::broadcast(), atoi(port_num));
		std::string message = bytes;
		socket.send_to(boost::asio::buffer(message), Endpoint);
		socket.close(err);
    }
	return 0;
} 
const char* usage = "usage: comreader <com port name> <udp port> ";
int main(int argc, char* argv[])
{
	if ( argc < 3)
	{	std::cout << "expected 2 params, provaided - " << (argc - 1) << std::endl;
		std::cout << usage << std::endl;
		exit(1);
	}
	std::cout << "read com port\n";
	try{
	for(unsigned int i = 0; i < NumberStrings; i++)
	{
		const char* message = ReadString(argv[1], 1);
		if (strlen(message)> 0)
		{
		Message cryptor(message);
		const char* crypted = cryptor.encrypt();
		sendBytesToUdp(crypted, argv[2]);
		}
	} 
}
	catch(std::exception& e)
{
	std::cout << e.what() << std::endl;
}
}
	
