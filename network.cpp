#include "main.h"
#include "network.h"

struct UDPConnection
{
	UDPConnection( )
	{
		quit = false;
	}
	~UDPConnection( )
	{
		SDLNet_FreePacket(packet);
		// SDLNet_Quit(); // do I want to quit sdlnet here?
	}
	bool Init( const std::string &ip, int32_t remotePort, int32_t localPort )
	{
		std::cout << "Connecting to \n\tIP : " << ip << "\n\tPort : " << remotePort << std::endl;
		std::cout << "Local port : " << localPort << "\n\n";

		if ( !OpenPort( localPort  ) )
			return false;

		if ( !SetIPAndPort( ip, remotePort ) )
			return false;

		if ( !CreatePacket( 512 ) )
			return false;

		return true;
	}

	bool CreatePacket( int32_t packetSize )
	{
		std::cout << "Creating packet with size " << packetSize << "...\n";

		// Allocate memory for the packet
		packet = SDLNet_AllocPacket( packetSize );

		if ( packet == nullptr )
		{
			std::cout << "\tSDLNet_AllocPacket failed : " << SDLNet_GetError() << std::endl;
			return false;
		}

		// Set the destination host and port
		// We got these from calling SetIPAndPort()
		packet->address.host = serverIP.host;
		packet->address.port = serverIP.port;

		return true;
	}
	bool OpenPort( int32_t port )
	{
		std::cout << "Opening port " << port << "...\n";

		// Sets our sovket with our local port
		ourSocket = SDLNet_UDP_Open( port );

		if ( ourSocket == nullptr )
		{
			std::cout << "\tSDLNet_UDP_Open failed : " << SDLNet_GetError() << std::endl;
			return false;
		}
		return true;
	}
	bool SetIPAndPort( const std::string &ip, uint16_t port )
	{
		std::cout << "Setting IP ( " << ip << " ) " << "and port ( " << port << " )\n";

		// Set IP and port number with correct endianess
		if ( SDLNet_ResolveHost( &serverIP, ip.c_str(), port )  == -1 )
		{
			std::cout << "\tSDLNet_ResolveHost failed : " << SDLNet_GetError() << std::endl;
			return false;
		}
		return true;
	}
	// Send data.
	bool Send( const std::string &str )
	{
		// Set the data
		// UDPPacket::data is an Uint8, which is similar to char*
		// This means we can't set it directly.
		//
		// std::stringstreams let us add any data to it using << ( like std::cout )
		// We can extract any data from a std::stringstream using >> ( like std::cin )
		//
		//str
		std::cout << "Type a message and hit enter\n";
		std::string msg = "";
		std::cin.ignore();
		std::getline(std::cin, msg );

		memcpy(packet->data, msg.c_str(), msg.length() );
		packet->len = msg.length();

		std::cout
			<< "Sending : \'" << str << "\', Length : " << packet->len << "\n";

		// Send
		// SDLNet_UDP_Send returns number of packets sent. 0 means error
		if ( SDLNet_UDP_Send(ourSocket, -1, packet) == 0 )
		{
			std::cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n";
			return false;
		}

		return true;
	}
	void CheckForData()
	{
		// Check t see if there is a packet wauting for us...
		if ( SDLNet_UDP_Recv(ourSocket, packet))
		{
			std::cout << "\tData received : " << packet->data << "\n";

			// If the data is "quit"
			if ( strcmp((char *)packet->data, "quit") == 0)
				quit = true;
		}
		else
			std::cout  << "\tNo data received!\n";

	}

	private:
	bool quit;
	UDPsocket ourSocket;
	IPaddress serverIP;
	UDPpacket *packet;
};




bool networkLoop()
{
    bool quit = false;

    IPaddress hostIP;
    SDLNet_ResolveHost(&hostIP,NULL,1234);

    TCPsocket server = SDLNet_TCP_Open(&hostIP);
    TCPsocket client;

    UDPConnection udpConnection;
    //udpConnection.Init()


    while( !quit )
    {
        client=SDLNet_TCP_Accept(server);
        while(client) // connected to client
        {
            SDLNet_TCP_Send(client,(const char*)("HELLO"),12);
            IPaddress *clientIP = SDLNet_TCP_GetPeerAddress(client);
            //std::cout << (const char*)clientIP.host;
        }

    }

}

bool TCPInit()
{



}
