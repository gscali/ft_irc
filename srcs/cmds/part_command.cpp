#include "../../ft_irc.hpp"

void	part_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() < 2)
	{
		send_error("461", server->client[clientFd]->getNickname(), "Not enough parameters", clientFd);
		return;
	}
	std::vector<std::string>	channels = ft_split(cmd[1], ",");
	for (std::vector<std::string>::iterator it = channels.begin(); it != channels.end(); it++)
	{
		if (server->channelList.find(*it) == server->channelList.end())
		{
			send_error_with_arg("403", server->client[clientFd]->getNickname(), *it, "No such channel", clientFd);
			return;
		}
		std::vector<int>::iterator	toDelete;
		Channel	*chan = server->channelList[*it];
		if ((toDelete = std::find(chan->clients.begin(), chan->clients.end(), clientFd)) == chan->clients.end())
		{
			send_error_with_arg("442", server->client[clientFd]->getNickname(), *it, "You're not on that channel", clientFd);
			return;
		}
		std::string	msg;
		for (std::vector<int>::iterator client = chan->clients.begin(); client != chan->clients.end(); client++)
		{
			if (*client != clientFd)
				send_reply(server->client[clientFd]->getNickname(), server->client[clientFd]->getUsername(), "PART", *it, *client);
			else
				send_reply(server->client[clientFd]->getNickname(), server->client[clientFd]->getUsername(), "PART", *it, clientFd);		
		}
		chan->clients.erase(toDelete);
		if (chan->clients.empty())
		{	
			std::map<std::string, Channel *>::iterator	delChannel = server->channelList.find(*it);
			delete delChannel->second;
			server->channelList.erase(*it);
		}
	}
}
