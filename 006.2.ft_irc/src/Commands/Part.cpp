#include "../../include/Commands.hpp"

/**
 * @brief Handles the PART command, which allows a client to leave one or more channels.
 * 
 * @param client A pointer to the client who issued the command.
 * @param commandParts A vector of strings containing the command and its parameters.
 * @param srv A pointer to the server object.
 */
void Part::part(Client* client, vector<string> commandParts, Server* srv)
{
    if (commandParts.size() < 2)
    {
        client->sendMessage( ":" + client->getHostName() + " 461 " + client->getNickName() + " PART :Not enough parameters" );
        return;
    }

    string target = commandParts.at(1);

    if (target.find(',') == string::npos)
        partChannel(client, target, srv);
    else
    {
        istringstream iss(target);
        string channelName;
        while (getline(iss, channelName, ','))
            partChannel(client, channelName, srv);
    }
}

/**
 * @brief Removes a client from a channel and performs necessary cleanup.
 * 
 * This function removes the specified client from the given channel. If the client is not on the channel,
 * an error message is sent to the client. If the channel becomes empty after the client leaves, the channel
 * is deleted from the server.
 * 
 * @param client A pointer to the client object.
 * @param channelName The name of the channel to be left.
 * @param srv A pointer to the server object.
 */
void Part::partChannel(Client* client, string channelName, Server* srv)
{
    if (channelName.empty() || channelName.at(0) != '#')
    {
      	client->sendMessage( ":" + client->getHostName() + " 403 " + client->getNickName() + " " + channelName + " :No such channel" );
        return;
    }

    Channel* channel = srv->getChannel(channelName);

    if (!channel)
    {
     	client->sendMessage( ":" + client->getHostName() + " 403 " + client->getNickName() + " " + channelName + " :No such channel" );
        return;
    }

    if (!channel->isUserOnChannel(client))
    {
        client->sendMessage( ":" + client->getHostName() + " 442 " + client->getNickName() + " " + channelName + " :You're not on that channel" );
        return;
    }

    channel->removeUserFromChannel(client);
    client->removeChannel(channel);

    string message = ":" + client->getPrefix() + " PART " + channelName + "\n";
    channel->broadcastMessage(message, client);

   	client->sendMessage( "You left the channel " + channelName );

    if (channel->getChannelClientCount() == 0 && srv->channelExists(channelName))
    {
   		string channelName = channel->getChannelName();
		string message = "Channel " + channelName + " is empty, deleting.\n";
		write( 1, message.c_str(), message.length() );
		srv->removeChannel( channelName );
    }
}
