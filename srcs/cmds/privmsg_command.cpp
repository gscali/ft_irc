#include "../../ft_irc.hpp"

void	privmsg_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() == 1)
	{
		send_error("411", server->client[clientFd]->getNickname(), "No receiver given", clientFd);
		return;
	}
	if (cmd.size() == 2)
	{
		send_error("412", server->client[clientFd]->getNickname(), "No text to send", clientFd);
		return;
	}
	std::vector<std::string>	checker = ft_split(cmd[1], ",");
	if (checker.size() != 1)
	{
		send_error("407", server->client[clientFd]->getNickname(), "Duplicate recipients. No message delivered", clientFd);
		return;
	}
	if (cmd[2] == ":/bot")
	{
		std::string	msg = "COMMANDS:\n-NICK- Show/Change your nickname\n-OPER- Become operator\n-JOIN- Join a channel\n-PART- Leave a channel\n-KILL- Disconnect someone\n-QUIT- Disconnect from server\n-MODE- Get user mode\n-PRIVMSG- Send a private message\n-NOTICE- Send a notice\n-TOPIC- Set/Change a channel's topic\r\n";
		send_error("003", server->client[clientFd]->getNickname(), msg, clientFd);
		return;
		//send(clientFd, msg.c_str(), msg.length(), 0);
	}
	if (cmd[1].front() == '#')
	{
		if (server->channelList.find(cmd[1]) == server->channelList.end())
		{
			send_error_with_arg("401", server->client[clientFd]->getNickname(), cmd[1], "No such nick/channel", clientFd);
			return;
		}
		Channel	*chan = server->channelList[cmd[1]];
		if (std::find(chan->clients.begin(), chan->clients.end(), clientFd) == chan->clients.end())
		{
			send_error_with_arg("404", server->client[clientFd]->getNickname(), cmd[1], "Cannot send to channel", clientFd);
			return;
		}
		std::string	toSend;
		for (std::vector<int>::iterator it = chan->clients.begin(); it != chan->clients.end(); it++)
		{	
			toSend = ":" + server->client[clientFd]->getNickname() + " PRIVMSG " + cmd[1] + " " + cmd[2] + "\r\n";
			if (*it != clientFd)
				send(*it, toSend.c_str(), toSend.length(), 0);
		}
	}
	else
	{
		Client	*receiver = server->getClientByNick(cmd[1]);
		if (!receiver)
		{
			send_error_with_arg("401", server->client[clientFd]->getNickname(), cmd[1], "No such nick/channel", clientFd);
			return;
		}
		std::string	msg = ":" + server->client[clientFd]->getNickname() + " PRIVMSG " + cmd[1] + " " + cmd[2] + "\r\n";;
		send(receiver->getFd(), msg.c_str(), msg.length(), 0);
	}
}