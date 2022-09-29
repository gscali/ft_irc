#include "../../ft_irc.hpp"

void 	quit_command(std::vector<std::string> cmd, int clientFd, Server *server)
{
    std::string mess;
    
    if (cmd.size() != 1 && cmd.size() != 2)
	{
        send_error_with_arg("461", server->client[clientFd]->getNickname(), cmd[0], "Not enough parameters", clientFd);
        return;
    }	
    if (cmd.size() == 2)
        mess = cmd[1] + "\r\n"; 
    else
        mess = server->client[clientFd]->getNickname();
    send(clientFd, mess.c_str(), mess.length(), 0);
    server->clientDisconnect(clientFd);
}