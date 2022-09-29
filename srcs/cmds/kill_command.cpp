#include "../../ft_irc.hpp"

void 	kill_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	Client *client_target = NULL;

	if (cmd.size() != 3)
	{
		send_error_with_arg("461", server->client[clientFd]->getNickname(), cmd[0], "Not enough parameters", clientFd);
		return;
	}
	if (server->client[clientFd]->getMode().find('o') == std::string::npos)
	{
		send_error("481", server->client[clientFd]->getNickname(), "Permission Denied- You're not an IRC operator", clientFd);
		return;
	}
	client_target = server->getClientByNick(cmd[1]);
	if (!client_target)
	{
		send_error_with_arg("401", server->client[clientFd]->getNickname(), cmd[1], "No such nick/channel", clientFd);
		return;
	}
	send_reply(server->client[clientFd]->getNickname(), server->client[clientFd]->getUsername(), "KILL", cmd[2], client_target->getFd());
	server->clientDisconnect(client_target->getFd());
}