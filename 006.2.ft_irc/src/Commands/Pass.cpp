#include "../../include/Commands.hpp"

/**
 * Handles the PASS command for authenticating a client.
 *
 * This function checks if the client is already registered, has user authentication, or has already provided a password.
 * If any of these conditions are true, it sends an error reply and returns.
 * Otherwise, it checks if the command has enough parameters. If not, it sends an error reply and returns.
 * Then, it verifies the server password using the provided password.
 * If the password is not valid, it sends a message indicating access denied and returns.
 * If the password is valid, it sets the client's pass flag to true and sends a message indicating password accepted.
 *
 * @param client The client object representing the connected client.
 * @param commandParts The vector of command parts, where the first part is the command itself and the second part is the password.
 * @param srv The server object representing the IRC server.
 */
void Pass::pass(Client *client, const vector<string> commandParts, Server *srv)
{
    if (client->isRegistered() || client->getUserAuth() || client->getIsPass())
    {
        client->sendReply(ERR_ALREADYREGISTERED(client->getNickName()));
        return;
    }

    if (commandParts.size() < 2)
    {
        client->sendReply(ERR_NEEDMOREPARAMS(client->getNickName(), "PASS"));
        return;
    }

    string passw = commandParts.at(1);

    if (!srv->verifySrvPass(passw))
    {
        client->sendMessage("Access denied!");
        return;
    }

    client->setPass(true);
    client->sendMessage("Password accepted!");
}
