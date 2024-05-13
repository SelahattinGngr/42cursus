#include "../../include/Commands.hpp"

/**
 * Handles the PRIVMSG command.
 *
 * This function is responsible for processing the PRIVMSG command received from a client.
 * It extracts the target and message from the command, and based on the target type (channel or user),
 * it either sends a channel message or a private message.
 *
 * @param client A pointer to the client who sent the PRIVMSG command.
 * @param commandParts A vector of strings containing the command and its parameters.
 * @param srv A pointer to the server instance.
 */
void PrivMsg::privMsg(Client *client, vector<string> commandParts, Server *srv)
{
    if (commandParts.size() < 2)
    {
        client->sendReply(ERR_NEEDMOREPARAMS(client->getNickName(), "PRIVMSG"));
        return;
    }

    string commandString = mergeString(commandParts, " ");

    size_t targetStart = commandString.find("PRIVMSG") + 8;
    size_t messageStart = commandString.find(" :", targetStart);

    if (messageStart == string::npos)
    {
        client->sendReply(ERR_NOTEXTTOSEND(client->getNickName()));
        return;
    }

    string target = commandString.substr(targetStart, messageStart - targetStart);
    target = strim(target);
    string message = commandString.substr(messageStart + 2);

    if (target.at(0) == '#')
    {
        sendChannelMessage(client, target, message, srv);
    }
    else
    {
        sendPrivateMessage(client, target, message, srv);
    }
}

/**
 * Sends a message to a specific channel.
 *
 * @param client The client sending the message.
 * @param channelName The name of the channel to send the message to.
 * @param message The message to send.
 * @param srv The server instance.
 */
void sendChannelMessage(Client *client, string channelName, string message, Server *srv)
{
    Channel *channel = srv->getChannel(channelName);

    if (channel == NULL)
    {
        client->sendReply(ERR_NOSUCHCHANNEL(client->getNickName(), channelName));
        return;
    }

    if (channel->getModerated() && !client->isOperator())
    {
        client->sendReply(ERR_NOCANNOTSENDTOCHAN(client->getNickName(), channelName));
        return;
    }

    if (channel->getNoExternalMessages() && !channel->isUserOnChannel(client))
    {
        client->sendReply(ERR_NOCANNOTSENDTOCHAN(client->getNickName(), channelName));
        return;
    }

    channel->broadcastMessage(":" + client->getPrefix() + " PRIVMSG " + channelName + " :" + message, client);
}

/**
 * Sends a private message from a client to a target client.
 *
 * @param client The client sending the private message.
 * @param target The nickname or channel name of the target client.
 * @param message The message to be sent.
 * @param srv The server instance.
 */
void sendPrivateMessage(Client *client, string target, string message, Server *srv)
{
    Client *targetClient = srv->getClient(target);

    if (targetClient == NULL)
    {
        client->sendReply(ERR_NOSUCHNICK(client->getNickName(), target));
        return;
    }

    targetClient->sendMessage(":" + client->getPrefix() + " PRIVMSG " + target + " :" + message);
}
