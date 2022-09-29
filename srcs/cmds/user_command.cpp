#include "../../ft_irc.hpp"

void	user_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (!server->client[clientFd]->_passwordOk)
	{
		send(clientFd, "You must enter the password first.\r\n", strlen("You must enter the password first.\r\n"), 0);
		return;
	}
	if (server->client[clientFd]->_isConnected)
		send_error("462", server->client[clientFd]->getNickname(), "You are already registered.", clientFd);
	else
	{
		if (cmd.size() < 5)
			send_error("461", server->client[clientFd]->getNickname(), "Not enough parameters.", clientFd);
		else
		{
			server->client[clientFd]->setUsername(cmd[1]);
			server->client[clientFd]->_usernameOk = true;
		}
	}
	if (server->client[clientFd]->_passwordOk && server->client[clientFd]->_nicknameOk && server->client[clientFd]->_usernameOk && !server->client[clientFd]->_isConnected)
	{
		server->client[clientFd]->_isConnected = true;
		send_error("001", server->client[clientFd]->getNickname(), "Welcome to PokeIRC!", clientFd);
	}
}