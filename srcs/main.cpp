#include "../ft_irc.hpp"

int main(int ac, char **av)
{
	if (ac != 3)
		ft_error("Error: usage: ./ircserv <port> <password>");
	Server	serv;
	serv.setPassword(std::string(av[2]));
	serv.getConfig("ircserv.conf");
	create_server(&serv, av[1]);
}