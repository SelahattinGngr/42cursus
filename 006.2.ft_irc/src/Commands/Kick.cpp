#include "../../include/Commands.hpp"

/**
 * Kicks a user from a channel.
 *
 * @param client The client who initiated the kick command.
 * @param commandParts The vector of command parts, where the first element is the channel name, the second element is the nickname of the user to be kicked, and the optional third element is the reason for the kick.
 * @param srv The server instance.
 */
void Kick::kick(Client* client, vector<string> commandParts, Server* srv)
{
    if (commandParts.size() < 3)
    {
        client->sendReply(ERR_NEEDMOREPARAMS(client->getNickName(), "KICK"));
        return;
    }

    string channelNamee = commandParts.at(1);
    string nickName = commandParts.at(2);
    string reason = (commandParts.size() > 3) ? commandParts.at(3) : "No reason specified";

    if (channelNamee.at(0) != '#')
    {
        client->sendReply(ERR_NOSUCHCHANNEL(client->getNickName(), channelNamee));
        return;
    }

    Channel* channel = srv->getChannel(channelNamee);
    if (!channel)
    {
        client->sendReply(ERR_NOSUCHCHANNEL(client->getNickName(), channelNamee));
        return;
    }

    if (!channel->isUserOnChannel(client))
    {
        client->sendReply(ERR_NOTONCHANNEL(client->getNickName(), channelNamee));
        return;
    }

    Client* target = srv->getClient(nickName);
    if (!target)
    {
        client->sendReply(ERR_NOSUCHNICK(client->getNickName(), nickName));
        return;
    }

    if (!channel->isUserOnChannel(target))
    {
        client->sendReply(ERR_USERNOTINCHANNEL(client->getNickName(), nickName, channelNamee));
        return;
    }

    if (channel->getChannelOwner()->getNickName() == target->getNickName())
    {
        client->sendReply(ERR_NOKICKCHANNELOWNER(client->getNickName(), channelNamee));
        return;
    }

    if (client->isOperator())
    {
        channel->removeUserFromChannel(target);
        target->removeChannel(channel);

        string message = ":" + client->getPrefix() + " KICK " + channelNamee + " " + nickName + " :" + reason + "\n";
        channel->broadcastMessage(message, client);

        target->sendMessage(":" + client->getPrefix() + " KICK " + channelNamee + " " + nickName + " :" + reason);
        target->sendMessage("You have been kicked from channel " + channelNamee + " by " + client->getNickName());

        string leavemessage = client->getNickName() + " kicked " + target->getNickName() + " from channel " + channel->getChannelName();
        log(leavemessage);
    }
    else
    {
        client->sendReply(ERR_CHANOPRIVSNEEDED(client->getNickName(), channelNamee));
        return;
    }

    if (channel->getChannelClientCount() == 0)
    {
        string channelName = channel->getChannelName();
        srv->removeChannel(channelName);
    }
}
