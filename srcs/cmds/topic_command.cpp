#include "../../ft_irc.hpp"

void	topic_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() < 2)
	{
		send_error("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd);
		return;
	}
	if (server->channelList.find(cmd[1]) == server->channelList.end())
	{
		send_error_with_arg("442", server->client[clientFd]->getNickname(), cmd[1], "You're not on that channel", clientFd);
		return;
	}
	Channel	*chan = server->channelList[cmd[1]];
	if (std::find(chan->clients.begin(), chan->clients.end(), clientFd) == chan->clients.end())
	{
		send_error_with_arg("442", server->client[clientFd]->getNickname(), cmd[1], "You're not on that channel", clientFd);
		return;
	}
	if (cmd.size() == 2)
	{	
		std::string	msg = chan->topic + "\r\n";
		send(clientFd, msg.c_str(), msg.length(), 0);
	}
	else
	{
		std::string msg = ":" + server->client[clientFd]->getNickname() + "!" + server->client[clientFd]->getUsername() + "127.0.0.1 TOPIC " + cmd[1] + " " + cmd[2] + "\r\n";
		send(clientFd, msg.c_str(), msg.length(), 0);
		chan->topic = cmd[2];
	}
}