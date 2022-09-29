#include "../../ft_irc.hpp"

bool	nickname_parse(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (cmd.size() == 2)
	{
		if (!isalpha(cmd[1][0]))
		{
			send_error_with_arg("432", server->client[clientFd]->getNickname(), cmd[1], "Erroneous Nickname", clientFd);
			return false;
		}
		for (std::string::iterator it=cmd[1].begin(); it!=cmd[1].end(); it++)
		{
			if (!isalnum(*it) && *it != '_' && *it != '-')
			{
				send_error_with_arg("432", server->client[clientFd]->getNickname(), cmd[1], "Erroneous Nickname", clientFd);
				return false;
			}
		}
		if (cmd[1].length() > 30)
		{
			send_error_with_arg("432", server->client[clientFd]->getNickname(), cmd[1], "Erroneous Nickname", clientFd);
			return false;
		}
		for (std::vector<std::string>::iterator it = server->nicknameList.begin(); it != server->nicknameList.end(); it++)
		{
			if (*it == cmd[1])
			{
				if (server->client[clientFd]->_isConnected)
				{
					send_error("433", server->client[clientFd]->getNickname(), "Nickname already used.", clientFd);
					return false;
				}
				else
				{
					send_error("436", server->client[clientFd]->getNickname(), "Nickname collision.", clientFd);
					return false;
				}
			}
		}
	}
	return true;
}

void	nick_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (!server->client[clientFd]->_passwordOk)
	{
		send(clientFd, "You must enter the password first.\r\n", strlen("You must enter the password first.\r\n"), 0);
		return;
	}
	if (!nickname_parse(cmd, clientFd, server))
		return;
	std::string msg;
	if (server->client[clientFd]->_isConnected)
	{
		if (cmd.size() == 1)
		{
			msg = "Nickname: " + server->client[clientFd]->getNickname() + "\r\n";
			send(clientFd, msg.c_str(), msg.length(), 0);
		}
		else
		{
			msg = ":" + server->client[clientFd]->getNickname() + "!" + server->client[clientFd]->getUsername() + "127.0.0.1 NICK :" + cmd[1] + "\r\n";
			send(clientFd, msg.c_str(), msg.length(), 0);
			server->client[clientFd]->setNickname(cmd[1]);
		}
	}
	else
	{
		if (cmd.size() == 1)
		{
			send_error("431", server->client[clientFd]->getNickname(), "No nickname given", clientFd);
			return;
		}
		server->client[clientFd]->setNickname(cmd[1]);
		server->client[clientFd]->_nicknameOk = 1;
	}
	if (server->client[clientFd]->_passwordOk && server->client[clientFd]->_nicknameOk && server->client[clientFd]->_usernameOk && !server->client[clientFd]->_isConnected)
	{
		server->client[clientFd]->_isConnected = true;
		send_error("001", server->client[clientFd]->getNickname(), "Welcome to PokeIRC!", clientFd);
	}
}