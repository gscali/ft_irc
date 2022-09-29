#ifndef FT_IRC_HPP
#define FT_IRC_HPP

/*===========================*/
/*======    INCLUDES    =====*/
/*===========================*/

#include <stdlib.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/resource.h>
#include <iostream>
#include <string>
#include <cctype>
#include <vector>
#include <algorithm>
#include "srcs/classes/Server.hpp"
#include "srcs/classes/Client.hpp"

/*===========================*/
/*=====    FUNCTIONS    =====*/
/*===========================*/

void	ft_error(std::string s);
void	create_server(Server *serv, char *port);
void	run_server(Server *serv);

void	send_error(std::string code, std::string nickname, std::string toSend, int clientFd);

#endif