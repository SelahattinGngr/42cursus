#include "../../include/Commands.hpp"

/**
 * Joins a client to a specified channel.
 * 
 * @param client The client to join the channel.
 * @param commandParts The vector of command parts.
 * @param srv The server instance.
 */
void Join::join(Client* client, vector<string> commandParts, Server* srv)
{
    if (commandParts.size() < 2)
    {
        client->sendReply(ERR_NEEDMOREPARAMS(client->getNickName(), "JOIN"));
        return;
    }

    string channel = commandParts.at(1);

    if (!channel.empty())
        joinChannel(client, channel, commandParts, srv);
        
}

/**
 * Joins a channel.
 *
 * This function allows a client to join a channel on the server. It checks if the channel name is valid,
 * if the client is already on the channel, if the channel requires a password, and if the channel is full.
 * If the channel exists, the client is added to the channel. If the channel does not exist, a new channel
 * is created and the client becomes the owner of the channel.
 *
 * @param client The client joining the channel.
 * @param channelName The name of the channel to join.
 * @param commandParts The parts of the command used to join the channel.
 * @param srv The server instance.
 */
void Join::joinChannel(Client* client, string channelName, vector<string> commandParts, Server* srv)
{
    string channelPass;

    if (channelName.empty())
    {
        client->sendReply(ERR_NOSUCHCHANNEL(client->getNickName(), channelName));
        return;
    }

    if (commandParts.size() == 2)
        channelPass = "";
    else
        channelPass = commandParts.at(2);

    if (channelName.size() < 2 || channelName.at(0) != '#')
    {
        client->sendReply(ERR_NOSUCHCHANNEL(client->getNickName(), channelName));
        return;
    }

    Channel* channel;

    if (srv->channelExists(channelName))
    {
        channel = srv->getChannel(channelName);

        if (channel->isUserOnChannel(client))
        {
            client->sendReply(ERR_USERONCHANNEL(client->getNickName(), channelName));
            return;
        }
        else if (channel->getChannelKey() != channelPass)
        {
            client->sendReply(ERR_BADCHANNELKEY(client->getNickName(), channelName));
            return;
        }
        else if (channel->getUserLimit() <= channel->getChannelClientCount())
        {
            client->sendReply(ERR_CHANNELISFULL(client->getNickName(), channelName));
            return;
        }
    }
    else
    {
        channel = new Channel(channelName, channelPass, client);
        channel->setChannelOwner(client);
        client->setOperator(true);
        srv->addChannel(channel);
        channel->setNoExternalMessages(true);
		channel->broadcastMessage("MODE " + channel->getChannelName() + " +n " + client->getNickName());
    }

    client->join(channel);
}
