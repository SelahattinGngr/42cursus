#include "../../include/Commands.hpp"

/**
 * @brief Handles the quit command for a client.
 *
 * This function is responsible for processing the quit command received from a client.
 * It sends a quit message to the client and removes the client from all channels.
 *
 * @param client A pointer to the client who issued the quit command.
 * @param commandParts A vector of strings containing the command arguments.
 * @param srv A pointer to the server instance.
 */
void Quit::quit(Client *client, vector<string> commandParts, Server *srv)
{
    string reason = commandParts.empty() ? "Leaving from Server" : commandParts.at(0);

    if (reason.at(0) == ':')
        reason.substr(1);

    client->sendMessage(RPL_QUIT(client->getPrefix(), reason));

    srv->removeClientFromAllChannels(client);
    srv->clientDisconnect(client->getClientSocketFD());
}
