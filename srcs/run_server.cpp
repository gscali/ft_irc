#include "../ft_irc.hpp"

void	run_server(Server *serv)
{
	fd_set	readFds;
	int		clientFd;
	char	buffer[1024];

	while (1)
	{
		bzero(buffer, 1024);
		FD_ZERO(&readFds);
		FD_SET(serv->socketFd, &readFds);
		serv->deleteClient();
		for (std::map<int, Client *>::iterator it = serv->client.begin(); it != serv->client.end(); it++)
		{
			clientFd = it->first;
			FD_SET(clientFd, &readFds);
		}
		if (select(serv->client.size() + serv->socketFd + 1, &readFds, NULL, NULL, NULL) < 0)
			ft_error("Error: select failed");
		if (FD_ISSET(serv->socketFd, &readFds))
			serv->serverAccept();
		for (std::map<int, Client *>::iterator it = serv->client.begin(); it != serv->client.end(); it++)
		{
			clientFd = it->first;
			if (FD_ISSET(clientFd, &readFds))
			{
				if (recv(clientFd, buffer, 1024, 0))
					serv->receiveMessage(clientFd, buffer);
				else
					serv->clientDisconnect(clientFd);
			}
		}
	}
}