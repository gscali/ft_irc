#include "../../ft_irc.hpp"

void	ping_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() < 2)
	{
		send_error("409", server->client[clientFd]->getNickname(), "No origin specified", clientFd);
		return;
	}
	else
	{
		if(cmd[1].compare("PokeIRC") != 0)
		{
			send_error("402", server->client[clientFd]->getNickname(), "No such server", clientFd);
			return ;
		}
	}
	std::string msg = "PONG :PokeIRC\r\n";
	send(clientFd, msg.c_str(), msg.length(), 0);
}