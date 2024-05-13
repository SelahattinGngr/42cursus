#include "../include/Bot.hpp"

/**
 * @brief Constructs a Bot object with the specified server, port, and password.
 *
 * @param serv The server address to connect to.
 * @param port The port number to connect to.
 * @param pass The password for the bot.
 */
Bot::Bot(const string &serv, int port, const string &pass)
	: serv(serv),
	  port(port),
	  botPass(pass),
	  nick("GaribanBot"),
	  user("IRC"),
	  realname("Bot")
{
	connectServ();
}

Bot::~Bot()
{
	close(sock);
}

/**
 * Establishes a connection to the server.
 * 
 * This function creates a socket, connects to the server, and sends registration messages.
 * 
 * @throws std::runtime_error if the socket creation, connection, or fcntl operation fails.
 */
void Bot::connectServ()
{
	struct sockaddr_in server_addr;
	struct hostent *host;

	host = gethostbyname(serv.c_str());
	if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
		write(STDOUT_FILENO, "Error: Bot socket creation failed.\n", 34);
		exit(1);
	}

	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(port);
	server_addr.sin_addr = *((struct in_addr *)host->h_addr);
	memset(&(server_addr.sin_zero), '\0', 8);

	if (connect(sock, (struct sockaddr *)&server_addr, sizeof(struct sockaddr)) == -1)
	{
		write(STDOUT_FILENO, "Error: Bot socket connection failed.\n", 36);
		exit(1);
	}

	if (fcntl(sock, F_SETFL, O_NONBLOCK) == -1)
	{
		write(STDOUT_FILENO, "Error: Bot socket fcntl failed.\n", 32);
		exit(1);
	}

	if (sock != -1)
	{
		sendRegMsg("PASS " + botPass + "\r\n");
		sendRegMsg("NICK " + nick + "\r\n");
		sendRegMsg("USER " + user + " 0 * :" + realname + "\r\n");
	}
}

/**
 * Listens for incoming messages from the socket and processes them.
 */
void Bot::listen()
{
	const int BUFFER_SIZE = 1024;
	char buffer[BUFFER_SIZE];
	memset(buffer, 0, BUFFER_SIZE);
	string accumulated;

	int bytes_read = recv(sock, buffer, BUFFER_SIZE - 1, 0);
	if (bytes_read < 0)
	{
		string errrecv = "Error in recv: " + string(strerror(errno)) + "\n";
		write(STDOUT_FILENO, errrecv.c_str(), errrecv.length());
		return;
	}
	else if (bytes_read == 0)
	{
		write(STDOUT_FILENO, "Connection closed by peer.\n", 27);
		return;
	}
	buffer[bytes_read] = '\0';
	accumulated += buffer;

	size_t pos;
	while ((pos = accumulated.find("\r\n")) != string::npos)
	{
		string msg = accumulated.substr(0, pos);
		accumulated.erase(0, pos + 2);
		processMessage(msg);
	}
}

/**
 * Processes the incoming message and performs specific actions based on its content.
 * 
 * @param msg The message to be processed.
 */
void Bot::processMessage(const string &msg)
{
	if (msg.find("PRIVMSG") != string::npos)
	{
		string senderNick = msg.substr(1, msg.find("!") - 1);
		{
			if (msg.find("hello") != string::npos)
				sendMsg(senderNick, "Hello " + senderNick + "!");

			if (msg.find("time") != string::npos || msg.find("date") != string::npos)
			{
				time_t rawtime;
				struct tm *timeinfo;
				time(&rawtime);
				timeinfo = localtime(&rawtime);
				sendMsg(senderNick, asctime(timeinfo));
			}

			if (msg.find("amk") != string::npos)
				sendMsg(senderNick, "Saygılı ol lütfen  " + senderNick + "!");
		}
	}
}

/**
 * Sends a message to a specific channel.
 * 
 * @param channel The channel to send the message to.
 * @param message The message to send.
 */
void Bot::sendMsg(const string &channel, const string &message)
{
	string fullMessage = "PRIVMSG " + channel + " :" + message + "\r\n";
	send(sock, fullMessage.c_str(), fullMessage.length(), 0);
}

/**
 * Sends a registration message to the server.
 *
 * This function sends the provided message to the server using the socket connection.
 *
 * @param message The message to be sent.
 */
void Bot::sendRegMsg(const string &message)
{
	send(sock, message.c_str(), message.length(), 0);
}
