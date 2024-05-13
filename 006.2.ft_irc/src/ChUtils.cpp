#include "../include/Server.hpp"

/**
 * @brief Removes a channel from the server.
 *
 * This function removes the channel with the specified name from the server.
 * If the channel exists, it is deleted and removed from the internal map of channels.
 * If the channel is already null or does not exist, an appropriate error message is written to the standard output.
 *
 * @param channelName The name of the channel to be removed.
 */
void Server::removeChannel(const std::string& channelName)
{
	std::map<std::string, Channel*>::iterator it = _channels.find(channelName);

	if (it != _channels.end())
	{
		Channel* channel = it->second;

		if (channel != NULL)
		{
			delete channel;
			_channels.erase(it);
		}
		else
		{
			string message = "Channel " + channelName + " is already null.";
			write(STDOUT_FILENO, message.c_str(), message.size());
		}
	}
	else
	{
		string message = "Channel " + channelName + " does not exist.";
		write(STDOUT_FILENO, message.c_str(), message.size());
	}
}

/**
 * @brief Removes a client from all channels.
 *
 * This function removes the specified client from all the channels it is currently a member of.
 * It also performs additional cleanup tasks such as logging the client's departure and deleting
 * empty channels if necessary.
 *
 * @param client A pointer to the client to be removed from the channels.
 */
void Server::removeClientFromAllChannels(Client* client)
{
	if (client == NULL || !client->isSocketOpen())
		return;

	std::vector<Channel*> channels = client->getChannel();
	while (!channels.empty())
	{
		Channel* channel = channels.back();
		channels.pop_back();

		if (channel != NULL)
		{
			string channelName = channel->getChannelName();
			string clientNick = client->getNickName();
			channel->removeUserFromChannel(client);
			client->removeChannel(channel);

			string leaveMessage = clientNick + " has left the channel " + channelName;
			log(leaveMessage);

			if (channel->getChannelClientCount() == 0 && channelExists(channel->getChannelName()))
			{
				string message = "Channel " + channelName + " is empty, deleting.\n";
				write(STDOUT_FILENO, message.c_str(), message.size());
				removeChannel(channelName);
			}
		}
	}
}

void Server::addChannel(Channel* channel)
{
	_channels.insert(std::make_pair(channel->getChannelName(), channel));
}

/**
 * Checks if a channel with the given name exists in the server.
 *
 * @param channelName The name of the channel to check.
 * @return `true` if a channel with the given name exists, `false` otherwise.
 */
bool Server::channelExists(const string& channelName)
{
	for (map<string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->second->getChannelName() == channelName)
			return true;
	}
	return false;
}

/**
 * @brief Retrieves a client object based on the given nickname.
 * 
 * This function searches for a client object in the map of clients based on the provided nickname.
 * If a client with the matching nickname is found, a pointer to the client object is returned.
 * If no matching client is found, NULL is returned.
 * 
 * @param nickName The nickname of the client to retrieve.
 * @return A pointer to the client object if found, NULL otherwise.
 */
Client* Server::getClient(string& nickName)
{
	for (map<int, Client*>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second->getNickName() == nickName)
			return it->second;
	}
	return NULL;
}

/**
 * @brief Retrieves a channel object based on the given channel name.
 * 
 * This function searches for a channel object in the map of channels based on the provided channel name.
 * If a matching channel is found, a pointer to the channel object is returned.
 * If no matching channel is found, NULL is returned.
 * 
 * @param channelName The name of the channel to retrieve.
 * @return A pointer to the channel object if found, NULL otherwise.
 */
Channel* Server::getChannel(string& channelName)
{
	for (map<string, Channel*>::iterator it = _channels.begin(); it != _channels.end(); ++it)
	{
		if (it->second->getChannelName() == channelName)
			return it->second;
	}
	return NULL;
}
