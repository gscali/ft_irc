#include "../ft_irc.hpp"

int	check_port(char *s)
{
	for (int i = 0; s[i]; i++)
		if (!isdigit(s[i]))
			ft_error("Error: port is not a number");
	int	port = atoi(s);
	if (port <= 0 || port > 65535)
		ft_error("Error: port is out of range");
	return (port);
}

void	create_server(Server *serv, char *s)
{
	int	port = check_port(s);
	int	opt = 1;
	struct sockaddr_in	address;
	socklen_t	addr_len = sizeof(address);

	if ((serv->socketFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		ft_error("Error: failed to create a socket");
	if (setsockopt(serv->socketFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(int)) < 0)
		ft_error("Error: setsockopt failed");
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;
	address.sin_port = htons(port);
	if (bind(serv->socketFd, (struct sockaddr *)&address, addr_len) < 0)
		ft_error("Error: failed to bind address");
	if (listen(serv->socketFd, 2) < 0)
		ft_error("Error: failed to listen to server");
	std::cout << "ircserv is on, waiting for connections..." << std::endl;
	run_server(serv);
}