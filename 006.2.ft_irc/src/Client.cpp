#include "../include/Client.hpp"

Client::Client(int clientSocketFD, int clientPort, const string& hostName, const string& serverName)
	: _clientSocketFD(clientSocketFD),
	  _clientPort(clientPort),
	  _hostName(hostName),
	  _serverName(serverName),
	  _clientStatus(CLIENT_CONNECTED),
	  _channel(),
	  userAuth(false),
	  _isPass(false),
	  _isOperator(false)
{
}

/**
 * @brief Destructor for the Client class.
 * 
 * This destructor is responsible for cleaning up the resources used by the Client object.
 * It deletes all the Channel objects stored in the _channel vector and clears the vector.
 */
Client::~Client()
{
	for (std::vector<Channel*>::iterator it = _channel.begin(); it != _channel.end(); ++it)
	{
		delete *it;
		*it = NULL;
	}
	_channel.clear();
}

/**
 * @brief Assignment operator overload for the Client class.
 * 
 * This function assigns the values of the given Client object to the current object.
 * 
 * @param copy The Client object to be copied.
 * @return A reference to the current Client object after the assignment.
 */
Client& Client::operator=(const Client& copy)
{
	_clientSocketFD = copy._clientSocketFD;
	_clientPort = copy._clientPort;
	_nickName = copy._nickName;
	_userName = copy._userName;
	_realName = copy._realName;
	_hostName = copy._hostName;
	_serverName = copy._serverName;
	_clientStatus = copy._clientStatus;
	_channel = copy._channel;
	userAuth = copy.userAuth;
	_isPass = copy._isPass;
	_isOperator = copy._isOperator;
	return *this;
}

/**
 * Returns the prefix of the client in the format "nickname!username@hostname".
 * If the username or hostname is empty, it is replaced with an asterisk (*).
 *
 * @return The prefix of the client.
 */
string Client::getPrefix() const
{
	string username = _userName.empty() ? "*" : _userName;
	string hostname = _hostName.empty() ? "*" : _hostName;

	return _nickName + "!" + username + "@" + hostname;
}

/**
 * Sets the nickname of the client.
 * 
 * @param nickName The nickname to set.
 */
void Client::setNickName(const string& nickName)
{
	if (isValidName(nickName))
		_nickName = nickName;
	else
	{
		string error = "Invalid nickname: " + nickName;
		write(2, error.c_str(), error.length());
	}
}

/**
 * @brief Sets the username of the client.
 * 
 * This function sets the username of the client to the specified value. 
 * If the specified username is invalid, an error message is written to the standard error stream.
 * 
 * @param userName The username to set.
 */
void Client::setUserName(const string& userName)
{
	if (isValidName(userName))
		_userName = userName;
	else
	{
		string error = "Invalid username: " + userName;
		write(2, error.c_str(), error.length());
	}
}

/**
 * Sends a welcome message to the client after successful registration.
 * If the client status is not CLIENT_CONNECTED or any of the required fields (nickname, username, realname) is empty,
 * an error message is sent and the function returns.
 * Otherwise, the client status is set to CLIENT_REGISTERED and a welcome message is sent to the client.
 * The function also logs the client's host name, client port, and nickname.
 */
void Client::welcomeMessage()
{
	if (_clientStatus != CLIENT_CONNECTED || _nickName.empty() || _userName.empty() || _realName.empty())
	{
		sendReply("ERROR :Closing Link: " + _hostName + " (Invalid nickname or username)");
		return;
	}

	_clientStatus = CLIENT_REGISTERED;

	sendReply(WELCOME_MESSAGE(_serverName, _nickName));

	std::ostringstream oss;
	oss << _hostName << ":" << _clientPort << " is now known as " << _nickName << ".";
	log(oss.str());
}

/**
 * Sends a message to the client.
 * 
 * @param message The message to be sent.
 */
void Client::sendMessage(const string& message) const
{
	string buffer = message + "\r\n";

	if (send(_clientSocketFD, buffer.c_str(), buffer.length(), 0) == -1)
		ErrorLogger(FAILED_SOCKET_SEND, __FILE__, __LINE__);
}

void Client::sendReply(const string& reply) const
{
	sendMessage(getPrefix() + " " + reply);
}

void Client::leave()
{
	_clientStatus = CLIENT_DISCONNECTED;
}

/**
 * Joins the specified channel.
 * Adds the client to the channel and updates the client's channel list.
 * Sends a reply to the client with the list of nicknames in the channel.
 * Broadcasts a join message to all clients in the channel.
 * Logs the join message.
 *
 * @param channel A pointer to the channel to join.
 */
void Client::join(Channel* channel)
{
	channel->addClient(this);
	_channel.push_back(channel);

	std::string nickList;
	std::vector<std::string> nicknames = channel->getChannelClientNickNames();
	for (std::vector<std::string>::iterator it = nicknames.begin(); it != nicknames.end(); ++it)
	{
		nickList += *it + " ";
	}

	sendReply(RPL_NAMREPLY(getPrefix(), channel->getChannelName(), nickList));

	channel->broadcastMessage(RPL_JOIN(getPrefix(), channel->getChannelName()));
	string message = _nickName + " " + " has joined to the channel " + channel->getChannelName();
	log(message);
}

/**
 * @brief Removes the specified channel from the client's list of channels.
 * 
 * @param channel A pointer to the channel to be removed.
 */
void Client::removeChannel(Channel* channel)
{
	std::vector<Channel*>::iterator it = std::find(_channel.begin(), _channel.end(), channel);

	if (it != _channel.end())
		_channel.erase(it);
}
