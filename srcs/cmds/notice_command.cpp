#include "../../ft_irc.hpp"

void	notice_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() < 3)
		return;
	std::vector<std::string>	checker = ft_split(cmd[1], ",");
	if (checker.size() != 1)
		return;
	if (cmd[1].front() == '#')
	{
		if (server->channelList.find(cmd[1]) == server->channelList.end())
			return;
		Channel	*chan = server->channelList[cmd[1]];
		if (std::find(chan->clients.begin(), chan->clients.end(), clientFd) == chan->clients.end())
			return;
	
		std::string	toSend;
		for (std::vector<int>::iterator it = chan->clients.begin(); it != chan->clients.end(); it++)
		{	
			toSend = ":" + server->client[clientFd]->getUsername() + " NOTICE " + cmd[1] + " " + cmd[2] + "\r\n";
			if (*it != clientFd)
				send(*it, toSend.c_str(), toSend.length(), 0);
		}
	}
	else
	{
		Client	*receiver = server->getClientByNick(cmd[1]);
		if (!receiver)
			return;
		std::string	msg = ":" + server->client[clientFd]->getUsername() + " NOTICE " + cmd[1] + " " + cmd[2] + "\r\n";;
		send(receiver->getFd(), msg.c_str(), msg.length(), 0);
	}
}