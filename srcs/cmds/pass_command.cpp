#include "../../ft_irc.hpp"

void	pass_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (server->client[clientFd]->_isConnected)
	{
		send_error("462", server->client[clientFd]->getNickname(), "You are already registered.", clientFd);
		return;
	}
	else
	{
		if (cmd.size() == 1)
			send_error("461", server->client[clientFd]->getNickname(), "Not enough parameters.", clientFd);
		else if (cmd[1].compare(server->getPassword()))
			send_error("464", server->client[clientFd]->getNickname(), "Password incorrect.", clientFd);
		else
			server->client[clientFd]->_passwordOk = true;
	}
}