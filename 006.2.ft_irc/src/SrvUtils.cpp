#include "../include/Server.hpp"

/**
 * Processes partial commands received from a client.
 *
 * This function processes the partial commands received from a client and executes the corresponding actions.
 * If the first character of the client buffer is '/', it assumes that the commands are newline-separated.
 * If the first character is not '/', it assumes that the commands are CRLF (carriage return + line feed) separated.
 *
 * @param clientSocketFD The file descriptor of the client socket.
 */
void Server::processPartialCommands(int clientSocketFD)
{
	string& clientBuffer = clientBuffers[clientSocketFD].getBuffer();
	size_t endOfCommand;
	string command;

	if (clientBuffer[0] == '/')
	{
		while ((endOfCommand = clientBuffer.find('\n')) != string::npos)
		{
			command = clientBuffer.substr(0, endOfCommand);
			clientBuffer.erase(0, endOfCommand + 1);
			CommandParser::commandParser(command.c_str(), _clients[clientSocketFD], this);
		}
		if (!clientBuffer.find('\n'))
			clientBuffer.clear();
	}

	else
	{
		while ((endOfCommand = clientBuffer.find("\r\n")) != string::npos)
		{
			command = clientBuffer.substr(0, endOfCommand);
			clientBuffer.erase(0, endOfCommand + 2);  
			CommandParser::commandParser(command.c_str(), _clients[clientSocketFD], this);
		}
		clientBuffer.clear();
	}
}


/**
 * Handles the client connection and processes the received data.
 *
 * @param clientSocketFD The file descriptor of the client socket.
 */

void Server::handleClient(int clientSocketFD)
{
		const size_t BUFFER_SIZE = 512;
		char tempBuffer[BUFFER_SIZE];
		memset(tempBuffer, 0, BUFFER_SIZE);

		ssize_t received = recv(clientSocketFD, tempBuffer, BUFFER_SIZE - 1, 0);
		if (received > 0) {
			clientBuffers[clientSocketFD].appendtoBuffer(string(tempBuffer, received));
			cout << "Received: " << tempBuffer << endl;
			processPartialCommands(clientSocketFD);
		} else if (received == 0 || errno == ECONNRESET) {
			FD_CLR(clientSocketFD, &read_set);
			clientDisconnect(clientSocketFD);
			clientBuffers.erase(clientSocketFD);
		} else {
			if (errno != EAGAIN && errno != EWOULDBLOCK) {
				FD_CLR(clientSocketFD, &read_set);
				ErrorLogger("recv error", __FILE__, __LINE__);
				close(clientSocketFD);
				clientBuffers.erase(clientSocketFD);
			}
		}
}

/**
 * Sends a message to all clients in a channel.
 *
 * @param channel The channel to send the message to.
 * @param message The message to send.
 * @param sender The client that sent the message.
 */
void Server::clientDisconnect(int clientSocketFD)
{
     try
    {
        std::map<int, Client*>::iterator it = _clients.find(clientSocketFD);
        if (it == _clients.end()) {
            write(STDOUT_FILENO, "Client not found for removal.\n", 30);
            return;
        }

        removeClientFromAllChannels(it->second);
        it->second->leave();

        ostringstream messageStreamDisconnect;
        messageStreamDisconnect << "Client " << it->second->getNickName() << " has disconnected.";
        log(messageStreamDisconnect.str());

        FD_CLR(clientSocketFD, &read_set);

        close(clientSocketFD);
        delete it->second;
        _clients.erase(it);
    }
    catch (const std::exception &e)
    {
        write(STDOUT_FILENO, e.what(), strlen(e.what()));
    }
}

/**
 * Sets the server password.
 * 
 * @param pass The password to set.
 */
void Server::setSrvPass(const string& pass) {
	_serverPass = pass;
}

/**
 * Verifies the server password.
 *
 * This function compares the provided password with the server's password
 * and returns true if they match, otherwise returns false.
 *
 * @param pass The password to be verified.
 * @return True if the password is correct, false otherwise.
 */
bool Server::verifySrvPass(const string& pass) {
	if (_serverPass == pass) {
		return true;
	}
	return false;
}

/**
 * @brief Signal handler function for the server.
 *
 * This function is called when a signal is received by the server process.
 * It shuts down the server by calling the `shutdownSrv` function of the `Server` class
 * and then exits the process with the given signal number.
 *
 * @param signum The signal number received by the server.
 */
void Server::signalHandler(int signum)
{
	Server::getInstance()->shutdownSrv();
	exit(signum);
}

//system("leaks ircserv");
/**
 * @brief Shuts down the server.
 * 
 * This function shuts down the server by closing all client connections, clearing the client map,
 * closing the server socket, and deleting the bot instance if it exists.
 * 
 * @note This function does not handle any exceptions. It is the responsibility of the caller to handle any exceptions that may occur.
 */
void Server::shutdownSrv()
{
	string outmessage = "Sunucu kapatılıyor...\n";
	write(STDOUT_FILENO, outmessage.c_str(), outmessage.size());

	for (std::map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it) {
		Client* client = it->second;
		if (client != NULL) {
			client->sendMessage("Sunucu kapatılıyor. Bağlantınız sonlandırılıyor.");
			removeClientFromAllChannels(client);
			close(it->first);
			delete client;
		}
	}
	_clients.clear();

	if (_serverSocketFD != -1) {
		close(_serverSocketFD);
		_serverSocketFD = -1;
	}

	if (_bot != NULL) {
		delete _bot;
		_bot = NULL;
	}

	FD_ZERO(&read_set);

	string outmessage2 = "Sunucu kapatıldı.\n";
	write(STDOUT_FILENO, outmessage2.c_str(), outmessage2.size());
}
