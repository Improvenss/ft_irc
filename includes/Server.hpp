#ifndef	SERVER_HPP
# define SERVER_HPP

# include <iostream>
# include <cstdlib>
# include <stdint.h>
# include <limits>
# include <sys/socket.h>
# include <sys/types.h>
# include <arpa/inet.h>
# include <cstring>
# include <netinet/in.h>
# include <unistd.h>
# include <fcntl.h>
# include <map>
# include <vector>
# include <sys/poll.h>
# include <netdb.h>
# include "Colors.hpp"
# include "Client.hpp"
# include "Channel.hpp"

# define MAX_CONNECTIONS 10
# define MAX_BUFFER 1024

class Client;

class Channel;

typedef std::vector<pollfd>::iterator itPoll;
typedef std::map<int, Client *>::iterator itClients;
typedef std::vector<Channel *>::iterator itChannels;

class Server
{
	private:
		bool					_isCheck; // arguments size is okay.
		const unsigned short	_port; // server port number.
		const std::string		_password; // server password.
		const std::string		_host; // server ip 127.0.0.1
		bool					_isRun; // program is running?
		int						_serverFd; // server's fd number.
		std::vector<pollfd>		_pollfds;
		std::map<int, Client*>	_clients; // client's with fd numbers.
		std::vector<Channel*>	_channels; // channel's vector.

		Server( void ); // Default Constructor.
	public:
		Server( int argc, char **argv );
		~Server( void ); // Destructor.
/* _________________________ MAIN FUCTION ___________________________________ */
		void	newSocket( void );
		void	start( void );
/* -------------------------------------------------------------------------- */
/* _________________________ CONNECTION FUNCTIONS ___________________________ */
		// void onClientDisconnect(int fd);
		void	onClientConnect( void );
		// void onClientMessage(int fd);
/* -------------------------------------------------------------------------- */
/* _________________________ SET/GET FUNCTIONS ______________________________ */
/* -------------------------------------------------------------------------- */
/* _________________________ TIME FUNCTIONS _________________________________ */
/* -------------------------------------------------------------------------- */
/* _________________________ IF FUNCTIONS ___________________________________ */
/* -------------------------------------------------------------------------- */
/* _________________________ PRINT FUCTIONS _________________________________ */
/* -------------------------------------------------------------------------- */
/* _________________________ UTILS __________________________________________ */
	private:
		bool			check( int argc );
		unsigned short	port( std::string argv );
		std::string		password( std::string argv );
/* -------------------------------------------------------------------------- */
/* _________________________ EXCEPTIONS _____________________________________ */
/* -------------------------------------------------------------------------- */
};

#endif