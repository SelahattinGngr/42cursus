#include "../include/Channel.hpp"

Channel::Channel(const string& channelName, const string& channelKey, Client* channelOwner)
	: _channelName(channelName),
	  _channelOwner(channelOwner),
	  _channelKey(channelKey),
	  _userLimit(1000),
	  _noExternalMessages(false),
	  _moderated(false)
{
}

Channel::~Channel()
{
}

void Channel::broadcastMessage(const string& message) const
{
	string tmp = message;
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		(*it)->sendMessage(message);
	}
}

/**
 * Broadcasts a message to all clients in the channel, except for a specific client.
 *
 * @param message The message to be broadcasted.
 * @param exceptClient The client to exclude from the broadcast.
 */
void Channel::broadcastMessage(const string& message, Client* exceptClient) const
{
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it != exceptClient)
			(*it)->sendMessage(message);
	}
}

void Channel::addClient(Client* client)
{
	_clients.push_back(client);
}

/**
 * @brief Removes a user from the channel.
 * 
 * This function removes the specified client from the channel's list of clients.
 * If the client is an operator, it checks if there are any other operators in the channel.
 * If there are no other operators, it selects a new operator from the remaining clients.
 * 
 * @param client A pointer to the client to be removed from the channel.
 */
void Channel::removeUserFromChannel(Client* client)
{
	for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it == client)
		{
			_clients.erase(it);
			break;
		}
	}

	if (client->isOperator() == true)
	{
		client->setOperator(false);
		for (vector<Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		{
			if ((*it)->isOperator() == true)
				return;
		}

		if (_clients.size() > 0)
		{
			Client* newOperator = _clients.front();
			if (newOperator->isOperator() == false)
			{
				newOperator->setOperator(true);
				setChannelOwner(newOperator);
				broadcastMessage("MODE " + _channelName + " +o " + newOperator->getNickName());
			}
		}
	}
}

/**
 * Checks if a given client is present in the channel.
 *
 * @param client A pointer to the client to check.
 * @return True if the client is present in the channel, false otherwise.
 */
bool Channel::isUserOnChannel(Client* client) const
{
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (*it == client)
			return true;
	}
	return false;
}

/**
 * Sets up the mode of the channel based on the given parameters.
 *
 * @param channel A pointer to the Channel object.
 * @param client A pointer to the Client object.
 * @param mode The mode to be set for the channel.
 * @param modeParams The parameters associated with the mode.
 */
void Channel::setUpModeChannel(Channel* channel, Client* client, string& mode, string& modeParams)
{
	if (!channel || !client)
	{
		write(2, "Channel or Client is null, cannot set mode.", 43);
		return;
	}
	if (mode == "+k" && (client->isOperator() == true))
	{
		channel->setChannelKey(modeParams);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " +k " + client->getNickName());
	}
	else if (mode == "+l" && (client->isOperator() == true))
	{
		channel->setUserLimit(atoi(modeParams.c_str()));
		channel->broadcastMessage("MODE " + channel->getChannelName() + " +l " + client->getNickName());
	}
	else if (mode == "+o" && (client->isOperator() == true))
	{
		Client* targetClient = Server::getInstance()->getClient(modeParams);
		if (!targetClient)
		{
			client->sendMessage(":" + client->getHostName() + " 401 " + client->getNickName() + " " + modeParams + " :No such nick/channel\r\n");
			return;
		}
		targetClient->setOperator(true);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " +o " + targetClient->getNickName());
	}
	else if (mode == "+m" && client->isOperator() == true)
	{
		channel->setModerated(true);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " +m " + client->getNickName());
	}
	else if (mode == "+n" && (client->isOperator() == true))
	{
		channel->setNoExternalMessages(true);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " +n " + client->getNickName());
	}
	else
	{
		client->sendMessage(":" + client->getHostName() + " 501 " + client->getNickName() + " :Unknown MODE flag");
	}
}

/**
 * Sets the low mode of the channel based on the given mode and mode parameters.
 * 
 * @param channel The channel to set the low mode for.
 * @param client The client requesting the mode change.
 * @param mode The mode flag to set.
 * @param modeParams The parameters associated with the mode flag.
 */
void Channel::setLowModeChannel(Channel* channel, Client* client, string& mode, string& modeParams)
{
	if (!channel || !client)
	{
		write(2, "Channel or Client is null, cannot set mode.", 43);
		return;
	}
	if (mode == "-k" && (client->isOperator() == true))
	{
		channel->setChannelKey("");
		channel->broadcastMessage("MODE " + channel->getChannelName() + " -k " + client->getNickName());
	}
	else if (mode == "-l" && (client->isOperator() == true))
	{
		channel->setUserLimit(1000);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " -l " + client->getNickName());
	}
	else if (mode == "-n" && (client->isOperator() == true))
	{
		channel->setNoExternalMessages(false);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " -n " + client->getNickName());
	}
	else if (mode == "-o" && (client->isOperator() == true))
	{
		Client* targetClient = Server::getInstance()->getClient(modeParams);
		if (!targetClient)
		{
			client->sendMessage(":" + client->getHostName() + " 401 " + client->getNickName() + " " + modeParams + " :No such nick/channel\r\n");
			return;
		}
		if (targetClient->getNickName() != channel->getChannelOwner()->getNickName())
		{
			targetClient->setOperator(false);
			channel->broadcastMessage("MODE " + channel->getChannelName() + " -o " + targetClient->getNickName());
		}
	}
	else if (mode == "-m" && client->isOperator() == true)
	{
		channel->setModerated(false);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " -m " + client->getNickName());
	}
	else
		client->sendMessage(":" + client->getHostName() + " 501 " + client->getNickName() + " :Unknown MODE flag");
}

std::vector<std::string> Channel::getChannelClientNickNames() const
{
	vector<string> nickNames;
	for (vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		nickNames.push_back((*it)->getNickName());
	}
	return nickNames;
}

string Channel::getExistingUsersNickList() const
{
	string nickList;
	for (std::vector<Client*>::const_iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it != _clients.begin())
			nickList += " ";

		nickList += (*it)->getNickName();
	}
	return nickList;
}
