#include "Parser.hpp"
#include "Server.hpp"

Parser::Parser(void)
{
	return;
}

Parser::~Parser(void)
{
	return;
}

void	Parser::parseCommand(std::string message, int clientFd, Server *server)
{
	std::vector<std::string>	cmdArray;
	std::string	temp;
	size_t	pos;

	if ((pos = message.find(':')) != std::string::npos)
	{
		if (pos)
		{
			temp = message.substr(pos, message.length());
			message.erase(pos, temp.length());
		}
	}
	cmdArray = ft_split(message, " ");
	if (!temp.empty())
	{
		cmdArray.pop_back();
		cmdArray.push_back(temp);
	}
	if (cmdArray[0][0] == ':')
	{
		if (cmdArray.size() == 1)
			cmdArray[0].pop_back();
		if (cmdArray[0].length() == 1)
		{
			send(clientFd, "Bad prefix format\r\n", strlen("Bad prefix format\r\n"), 0);
			return;
		}
		else
		{
			if (!server->client[clientFd]->_isConnected)
			{
				send(clientFd, "Not connected to server\r\n", strlen("Not connected to server\r\n"), 0);
				return;
			}
			else if (cmdArray[0].substr(1, cmdArray[0].length()) != server->client[clientFd]->getNickname())
			{
				send(clientFd, "Error: invalid nickname\r\n", strlen("Error: invalid nickname\r\n"), 0);
				return;
			}
		}
		cmdArray.erase(cmdArray.begin());
	}
	if (cmdArray.back().back() == '\n')
		cmdArray.back().pop_back();
	_command = cmdArray[0];
	getCommand(cmdArray, clientFd, server);
}

void	Parser::getCommand(std::vector<std::string> cmd, int clientFd, Server *server)
{
	if (!_command.empty())
		std::cout << "Command receive from " << server->client[clientFd]->getNickname() << ": " << _command << std::endl;
	if (_command == "PASS")
		pass_command(cmd, clientFd, server);
	else if(_command == "NICK")
		nick_command(cmd, clientFd, server);
	else if (_command == "USER")
		user_command(cmd, clientFd, server);
	else if (_command == "PING")
		ping_command(cmd, clientFd, server);
	else if (_command == "OPER")
		oper_command(cmd, clientFd, server);
	else if (_command == "JOIN")
		join_command(cmd, clientFd, server);
	else if (_command == "PART")
		part_command(cmd, clientFd, server);
	else if (_command == "KILL" || _command == "kill") 
		kill_command(cmd, clientFd, server);
	else if (_command == "QUIT")
		quit_command(cmd, clientFd, server);
	else if (_command == "MODE")
		mode_command(cmd, clientFd, server);
	else if (_command == "PRIVMSG")
		privmsg_command(cmd, clientFd, server);
	else if (_command == "TOPIC") 
		topic_command(cmd, clientFd, server);
	else if (_command == "NOTICE")
		notice_command(cmd, clientFd, server);
}