#ifndef SERVER_HPP
#define SERVER_HPP

/*==========================*/
/*=====    INCLUDES    =====*/
/*==========================*/

#include <unistd.h>
#include <fcntl.h>
#include <sys/select.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <fstream>
#include <string>
#include <vector>
#include <iterator>
#include <map>
#include <utility>
#include "Parser.hpp"
#include "Channel.hpp"

/*==========================*/
/*=======    CLASS    ======*/
/*==========================*/

class Client;
class Channel;

class Server
{
	public:

		Server(void);
		~Server(void);

		void				setPassword(std::string password);
		std::string const	&getPassword(void) const;
		std::string	const	&getOperatorPass() const;
		void				getConfig(std::string param);

		void	deleteClient(void);
		void	serverAccept(void);
		void	receiveMessage(int socketFd, std::string buffer);
		void	clientDisconnect(int socketFd);
		
		Client	*getClientByNick(std::string name);

		int	socketFd;
		std::map<int, Client *>	client;
		std::vector<std::string>	nicknameList;
		std::map<std::string, Channel *>	channelList;

	private:

		void	deleteChannels(void);

		std::vector<int>	clientFds;
		std::vector<std::string>	emptyChannels;
		Parser	_parse;
		std::string	_password;
		std::string	_msgSave;
		std::string	_operatorPwd;
};

std::vector<std::string>	ft_split (std::string str, std::string delimiter);
void						ft_error(std::string s);

#endif