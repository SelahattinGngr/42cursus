#include "../../include/Commands.hpp"

/**
 * Sends a notice message to a specific channel.
 *
 * @param client The client sending the notice message.
 * @param channelName The name of the channel to send the notice to.
 * @param message The notice message to send.
 * @param srv The server instance.
 */
static void sendNoticeChannelMessage(Client *client, string channelName, string message, Server *srv)
{
    Channel *channel = srv->getChannel(channelName);

    if (channel == NULL)
    {
        client->sendReply(ERR_NOSUCHCHANNEL(client->getNickName(), channelName));
        return;
    }

    channel->broadcastMessage(":" + client->getPrefix() + " NOTICE " + channelName + " :" + message);
}

/**
 * Sends a notice message from a client to a target client.
 * 
 * @param client The client sending the notice message.
 * @param target The nickname of the target client.
 * @param message The message to be sent.
 * @param srv The server instance.
 */
static void sendNoticeMessage(Client *client, string target, string message, Server *srv)
{
    Client *targetClient = srv->getClient(target);

    if (targetClient == NULL)
    {
        client->sendReply(ERR_NOSUCHNICK(client->getNickName(), target));
        return;
    }

    targetClient->sendMessage(":" + client->getPrefix() + " NOTICE " + target + " :" + message);
}

/**
 * Sends a NOTICE message from the client to a target.
 *
 * @param client The client sending the NOTICE message.
 * @param commandParts The parts of the command received from the client.
 * @param srv The server instance.
 */
void Notice::notice(Client *client, vector<string> commandParts, Server *srv)
{
    if (commandParts.size() < 3)
    {
        client->sendMessage(":" + client->getHostName() + " 461 " + client->getNickName() + " NOTICE :Not enough parameters");
        return;
    }

    string commandString = mergeString(commandParts, " ");
    size_t targetStart = commandString.find("NOTICE") + 7;
    size_t messageStart = commandString.find(" :", targetStart);

    if (messageStart == string::npos)
    {
        client->sendMessage(":" + client->getHostName() + " 412 " + client->getNickName() + "  NOTICE :No text to send");
        return;
    }

    string target = commandString.substr(targetStart, messageStart - targetStart);
    string message = commandString.substr(messageStart + 2);

    if (target.empty())
    {
        client->sendMessage(":" + client->getHostName() + " 401 " + client->getNickName() + " NOTICE :No such nick/channel");
        return;
    }

    if (message.empty())
    {
        client->sendMessage(":" + client->getHostName() + " 412 " + client->getNickName() + " NOTICE :No text to send");
        return;
    }

    target = strim(target);

    if (target.at(0) == '#')
    {
        sendNoticeChannelMessage(client, target, message, srv);
    }
    else
    {
        sendNoticeMessage(client, target, message, srv);
    }
}
