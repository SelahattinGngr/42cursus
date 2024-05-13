#include "../../include/Commands.hpp"

/**
 * Changes the nickname of the client.
 *
 * @param client The client whose nickname is being changed.
 * @param commandParts The vector of command parts, where the new nickname is expected to be at index 1.
 * @param srv The server object.
 */
void Nick::nick(Client *client, vector<string> commandParts, Server *srv)
{
    if (commandParts.size() < 2)
    {
        client->sendReply(ERR_NONICKNAMEGIVEN(client->getNickName()));
        return;
    }

    string nickName = commandParts.at(1);

    if (!client->getValidName(nickName))
    {
        client->sendReply(ERR_ERRONEUSNICKNAME(client->getNickName(), nickName));
        return;
    }

    if (client->getNickName() == nickName)
    {
        client->sendReply(ERR_NICKNAMEINUSE(client->getNickName(), nickName));
        return;
    }

    const std::map<int, Client *> &clients = srv->getAllClients();
    for (std::map<int, Client *>::const_iterator it = clients.begin(); it != clients.end(); ++it)
    {
        const Client *regUser = it->second;
        if (!regUser)
        {
            continue;
        }
        if (regUser != client && regUser->getNickName() == nickName)
        {
            client->sendReply(ERR_NICKNAMEINUSE(client->getNickName(), nickName));
            return;
        }
    }

    client->sendMessage(":" + client->getNickName() + " NICK " + nickName);
    client->setNickName(nickName);
}
