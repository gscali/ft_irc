#include "Server.hpp"
#include "Client.hpp"
#include "Parser.hpp"

Server::Server(void)
{
	return;
}

Server::~Server(void)
{
	return;
}

void	Server::setPassword(std::string password)
{
	_password = password;
}

std::string const &Server::getPassword(void) const
{
	return (_password);
}

std::string const &Server::getOperatorPass() const
{
	return (_operatorPwd);
}

void	Server::getConfig(std::string param) 
{
	std::ifstream ifs(param);
	std::string temp;
	size_t pos;

	if (!ifs.is_open())
		ft_error("Error: cannot open file");
	while (getline(ifs, temp))
	{
		if (temp.compare("op_pass") == 0)
			break;
	}
	pos = temp.find("=");
	_operatorPwd = temp.substr(pos + 2, temp.length());
}

void	Server::deleteClient(void)
{
	std::vector<int>::iterator	it = clientFds.begin();
	std::vector<int>::iterator	ite = clientFds.end();
	std::map<int, Client *>::iterator	clientIt;

	for ( ; it != ite; it++)
	{
		clientIt = client.find(*it);
		delete clientIt->second;
		close (clientIt->first);
		client.erase(clientIt->first);
	}
	clientFds.clear();
}

void	Server::serverAccept(void)
{
	struct sockaddr_in address;
	socklen_t addr_len = sizeof(address);
	int	newSock;
	Client	*user = new Client();

	newSock = accept(socketFd, (struct sockaddr*)&address, &addr_len);
	fcntl(newSock, F_SETFL, O_NONBLOCK);
	client.insert(std::pair<int, Client *>(newSock, user));
	client[newSock]->setFd(newSock);
	std::cout << "\e[1mA client has logged to the server\e[0m\n";
}


void	Server::receiveMessage(int clientFd, std::string buffer)
{
	if (buffer.length() > 510)
	{
		send(clientFd, "Warning: Limit of a string is 512 characters\r\n", 47, 0);
		return;
	}
	std::vector<std::string>	array;
	if (buffer.find('\n') == std::string::npos)
		client[clientFd]->setMessage(buffer);
	else if (!client[clientFd]->getMessage().empty())
	{
		client[clientFd]->setMessage(buffer);
		array.push_back(client[clientFd]->getMessage());
	}
	else
	{
		client[clientFd]->setMessage(buffer);
		array = ft_split(client[clientFd]->getMessage(), "\r\n");
	}
	if (client[clientFd]->getMessage().find('\n') != std::string::npos)
	{
		for (std::vector<std::string>::iterator it = array.begin(); it != array.end(); it++)
			_parse.parseCommand(*it, clientFd, this);
		client[clientFd]->getMessage().clear();
	}
}

void	Server::clientDisconnect(int socketFd)
{
	clientFds.push_back(socketFd);
	if (client[socketFd]->getUsername().empty())
		std::cout << "\e[1mClient has logged out\e[0m" << std::endl;
	else
		std::cout << "\e[1m" << client[socketFd]->getNickname() + " has logged out\e[0m" << std::endl;
	std::vector<int>::iterator	client;
	for (std::map<std::string, Channel *>::iterator it = channelList.begin(); it != channelList.end(); it++)
	{
		if ((client = std::find((*it).second->clients.begin(), (*it).second->clients.end(), socketFd)) != (*it).second->clients.end())
			(*it).second->clients.erase(client);
		if ((*it).second->clients.empty())
			emptyChannels.push_back((*it).first);
	}
	deleteChannels();
}

Client *Server::getClientByNick(std::string name)
{
	std::map<int, Client*>::iterator it = client.begin();
	std::map<int, Client*>::iterator ite = client.end();

	for ( ; it != ite; it++)
	{
		if ((*it).second->getNickname() == name)
			return ((*it).second);
	}
	return (nullptr);
}

void	Server::deleteChannels(void)
{
	std::vector<std::string>::iterator	it = emptyChannels.begin();
	std::vector<std::string>::iterator	ite = emptyChannels.end();
	std::map<std::string, Channel *>::iterator channelIt;
	for ( ; it != ite; it++)
	{
		channelIt = channelList.find(*it);
		delete channelIt->second;
		channelList.erase(channelIt->first);
	}
	emptyChannels.clear();
}