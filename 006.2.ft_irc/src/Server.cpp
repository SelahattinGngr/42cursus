#include "../include/Server.hpp"

Server* Server::ins = NULL;

/**
 * @brief Constructs a Server object with the specified parameters.
 *
 * @param serverSocketFamily The socket family for the server.
 * @param serverSocketProtocol The socket protocol for the server.
 * @param serverSocketPort The port number for the server.
 * @param serverName The name of the server.
 */
Server::Server(int serverSocketFamily, int serverSocketProtocol, int serverSocketPort, string serverName)
	: _serverSocketFD(-1),
	_serverSocketFamily(serverSocketFamily),
	_serverSocketProtocol(serverSocketProtocol),
	_serverSocketPort(serverSocketPort),
	_serverName(serverName),
	_serverPass(""),
	_bot(NULL)
{
	signal(SIGINT, signalHandler);
	Server::setInstance(this);

	memset(&serverAddress, 0, sizeof(serverAddress));

	FD_ZERO(&read_set);

}

/**
 * @brief Destructor for the Server class.
 * 
 * This destructor is responsible for cleaning up the resources used by the Server object.
 * It deletes the singleton instance of the Server class, deallocates memory for all connected clients and channels,
 * closes the server socket file descriptor, clears the read set, and deletes the bot object if it exists.
 */
Server::~Server()
{
	delete Server::ins;
	Server::ins = NULL;

	for (map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		delete it->second;
	}
	_clients.clear();
	for (map<string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it) {
		delete it->second;
	}
	_channels.clear();

	if (_serverSocketFD != -1)
		close(_serverSocketFD);


	FD_ZERO(&read_set);

	if (_bot != NULL){
		delete _bot;
	}

}


/**
 * @brief Starts the server socket.
 * 
 * This function creates a socket, sets it to non-blocking mode, and sets the socket options.
 * 
 * @throws ErrorLogger if the socket creation fails or setting the socket to non-blocking mode fails.
 * 
 * @param _serverSocketFamily The family of the server socket.
 * @param _serverSocketProtocol The protocol of the server socket.
 */
void Server::socketStart()
{
	_serverSocketFD = socket(_serverSocketFamily, _serverSocketProtocol, 0);

	if (_serverSocketFD == -1)
		ErrorLogger(FAILED_SOCKET, __FILE__, __LINE__);

	if (fcntl(_serverSocketFD, F_SETFL, O_NONBLOCK) == -1)
	{
		close(_serverSocketFD);
		ErrorLogger(FAILED_SOCKET_NONBLOCKING, __FILE__, __LINE__);
	}

	int reuse = 1;
	if (setsockopt(_serverSocketFD, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
	{
		close(_serverSocketFD);
		ErrorLogger(FAILED_SOCKET_OPTIONS, __FILE__, __LINE__);
	}
}

/**
 * Initializes the server socket based on the selected socket family.
 */
void Server::socketInit()
{
	switch (_serverSocketFamily)
	{
		case AF_INET: // IPv4
			serverAddress.sin_addr.s_addr = INADDR_ANY;
			serverAddress.sin_family = _serverSocketFamily;
			serverAddress.sin_port = htons(_serverSocketPort);
			break;
			
		default:
			close(_serverSocketFD);
			ErrorLogger(FAILED_SOCKET_DOMAIN, __FILE__, __LINE__);
	}
}

/**
 * Binds the server socket to the specified address.
 *
 * @throws ErrorLogger if the socket bind operation fails.
 */
void Server::socketBind()
{

			if (::bind(_serverSocketFD, reinterpret_cast<struct sockaddr*>(&serverAddress), sizeof(serverAddress)) == -1)
			{
				close(_serverSocketFD);
				ErrorLogger(FAILED_SOCKET_BIND, __FILE__, __LINE__);
			}

}


/**
 * @brief Listens for incoming connections on the server socket.
 * 
 * This function calls the listen() system call to start listening for incoming connections
 * on the server socket. If the listen() call fails, the server socket is closed and an error
 * is logged using the ErrorLogger class.
 * 
 * @note This function assumes that the server socket has already been created and bound.
 */
void Server::socketListen()
{
	if ( listen(_serverSocketFD, BACKLOG_SIZE) == -1 )
	{
		close(_serverSocketFD);
		ErrorLogger(FAILED_SOCKET_LISTEN, __FILE__, __LINE__);
	}

	FD_SET(_serverSocketFD, &read_set);

	
}


/**
 * Accepts a new client connection on the server socket.
 * 
 * @return The file descriptor of the accepted client socket.
 */
int Server::socketAccept()
{
	struct sockaddr_storage clientAddress;
	socklen_t clientAddressLength = sizeof(clientAddress);

	int clientSocketFD = accept(_serverSocketFD, (struct sockaddr *)&clientAddress, &clientAddressLength);

	if (clientSocketFD < 0)
	{
		if (errno == EAGAIN || errno == EWOULDBLOCK)
		{
		}
		else
		{
			ErrorLogger(FAILED_SOCKET_ACCEPT, __FILE__, __LINE__, true);
		}
	}

	if (fcntl(clientSocketFD, F_SETFL, O_NONBLOCK) == -1)
	{
		close(clientSocketFD);
		ErrorLogger(FAILED_SOCKET_NONBLOCKING, __FILE__, __LINE__);
	}

	int reuse = 1;
	if (setsockopt(clientSocketFD, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(int)) == -1)
	{
		close(clientSocketFD);
		ErrorLogger(FAILED_SOCKET_OPTIONS, __FILE__, __LINE__);
	}

	char hostname[NI_MAXHOST];
	if (inet_ntop(AF_INET, &(((struct sockaddr_in *)&clientAddress)->sin_addr), hostname, sizeof(hostname)) == NULL)
	{
		ErrorLogger(FAILED_SOCKET_GETADDRINFO, __FILE__, __LINE__, true);
	}

	Client* client = NULL;

	client = new Client(clientSocketFD, ntohs(((struct sockaddr_in*)&clientAddress)->sin_port), hostname, _serverName);

	_clients.insert(std::make_pair(clientSocketFD, client));

	std::ostringstream messageStream;
	messageStream << "New Client: has connected.";
	client->sendMessage("Connected to Server");
	client->sendMessage("Enter the server password using /PASS");

	log(messageStream.str());

	return clientSocketFD;
}

/**
 * @brief Runs the server and handles incoming connections and client requests.
 * 
 * This function starts the server, initializes the socket, binds it to a port,
 * and listens for incoming connections. It also sets up a signal handler for
 * handling the SIGINT signal. Inside the main loop, it checks for activity on
 * the server socket and client sockets using the `select` function. If there is
 * activity, it accepts new connections, handles client requests, and listens for
 * messages from the bot. The function runs indefinitely until the server is
 * stopped manually.
 */
void Server::serverRun()
{
	socketStart();
	socketInit();
	socketBind();
	socketListen();
	signal(SIGINT, signalHandler);
	try
	{
		_bot = new Bot("localhost", _serverSocketPort, _serverPass);

	}
	catch (const std::exception &e)
	{
		delete _bot;
		_bot = NULL;
		write(STDOUT_FILENO, e.what(), strlen(e.what()));
	}
	while (true)
	{
		int max_fd = _bot->getSocket();
		int n = 0;
		FD_ZERO(&read_set);
		FD_SET(_serverSocketFD, &read_set);
		FD_SET(_bot->getSocket(), &read_set);
		for (map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
		{
			FD_SET((*it).second->getClientSocketFD(), &read_set);
			max_fd = std::max(max_fd, (*it).second->getClientSocketFD());
		}
		n = select(max_fd + 1, &read_set, NULL, NULL, NULL);
		if (n)
		{
			if (FD_ISSET(_serverSocketFD, &read_set))
				socketAccept();
			for (map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); it++)
			{
				if (FD_ISSET((*it).second->getClientSocketFD(), &read_set))
				{
					handleClient((*it).second->getClientSocketFD());
					break;
				}
				
			}
			if (FD_ISSET(_bot->getSocket(), &read_set))
				_bot->listen();
		}
	}
}
