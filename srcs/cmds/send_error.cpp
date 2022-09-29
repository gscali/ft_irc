#include "../../ft_irc.hpp"

void	send_error(std::string code, std::string nickname, std::string toSend, int clientFd)
{
	std::string	message;

	message = ":PokeIRC " + code + " " + nickname + " :" + toSend + "\r\n";
	send(clientFd, message.c_str(), message.length(), 0);
}

void	send_error_with_arg(std::string code, std::string nickname, std::string arg, std::string toSend, int clientFd)
{
	std::string	message;

	message = ":PokeIRC " + code + " " + nickname + " " + arg + " :" + toSend + "\r\n";
	send(clientFd, message.c_str(), message.length(), 0);
}

void	send_reply(std::string nickname, std::string username, std::string command, std::string arg, int clientFd)
{
	std::string	message;

	message = ":" +  nickname + "!" + username + "@127.0.0.1 " + command + " :" + arg + "\r\n";
	send(clientFd, message.c_str(), message.length(), 0);
}

void	sendMode(std::string code, std::string nickname, int clientFd, std::string arg)
{
	std::string	message;

	message = ":PokeIRC " + code + " " + nickname + " +" + arg + "\r\n";
	send(clientFd, message.c_str(), message.length(), 0);
}