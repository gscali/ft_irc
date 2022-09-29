#ifndef PARSER_HPP
#define PARSER_HPP

/*==========================*/
/*=====    INCLUDES    =====*/
/*==========================*/

#include <string>
#include <vector>
#include <map>
#include "Client.hpp"

/*==========================*/
/*=======    CLASS    ======*/
/*==========================*/

class Server;

class Parser
{
	public:

		Parser(void);
		~Parser(void);

	void	parseCommand(std::string message, int clientFd, Server *server);
	void	getCommand(std::vector<std::string> cmd, int clientFd, Server *server);

	private:

		std::string	_command;
};

/*==========================*/
/*=====    COMMANDS    =====*/
/*==========================*/

void	pass_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	user_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	nick_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	ping_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	oper_command(std::vector<std::string> cmd, int clientFd, Server *server);
void 	mode_command(std::vector<std::string> cmd, int clientFd, Server *server);
void 	kill_command(std::vector<std::string> cmd, int clientFd, Server *server);
void 	quit_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	join_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	privmsg_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	notice_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	part_command(std::vector<std::string> cmd, int clientFd, Server *server);
void	topic_command(std::vector<std::string> cmd, int clientFd, Server *server);

/*==========================*/
/*======    UTILS    =======*/
/*==========================*/

std::vector<std::string>	ft_split (std::string str, std::string delimiter);
void	ft_error(std::string s);
void	send_error(std::string code, std::string nickname, std::string toSend, int clientFd);
void	send_error_with_arg(std::string code, std::string nickname, std::string arg, std::string toSend, int clientFd);
void	send_reply(std::string nickname, std::string username, std::string command, std::string arg, int clientFd);
void	sendMode(std::string code, std::string nickname, int clientFd, std::string arg);

#endif