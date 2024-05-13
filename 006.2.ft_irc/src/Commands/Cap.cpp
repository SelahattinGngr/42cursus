#include "../../include/Commands.hpp"


/**
 * Handles the CAP command.
 * 
 * This function is responsible for processing the CAP command received from a client.
 * It checks the command parts and performs the appropriate action based on the CAP value.
 * If the CAP value is "LS" or "ls", it sends a list of supported capabilities to the client.
 * Otherwise, it sends an error reply indicating an invalid CAP command.
 * 
 * @param client The client who sent the CAP command.
 * @param commandParts The vector of command parts received from the client.
 */
void Cap::cap(Client *client, const vector<string> commandParts)
{
    if (commandParts.size() < 2)
    {
        client->sendReply(ERR_NEEDMOREPARAMS(client->getNickName(), "CAP"));
        return;
    }

    string cap = commandParts.at(1);
    if (cap == "LS" || cap == "ls" )
    {
        client->sendMessage("/PASS\n/USER\n/NICK\n/JOIN\n/PART\n/PRIVMSG\n/NOTICE\n/KICK\n/MODE\n/QUIT\n");
    }
    else
    {
        client->sendReply(ERR_INVALIDCAPCMD(client->getNickName()));
    }
}
