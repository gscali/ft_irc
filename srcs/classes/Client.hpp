#ifndef CLIENT_HPP
#define CLIENT_HPP

/*==========================*/
/*=====    INCLUDES    =====*/
/*==========================*/

#include <string>
#include <vector>

/*==========================*/
/*=======    CLASS    ======*/
/*==========================*/

class Client
{
	public:

		Client(void);
		~Client(void);

		int const			&getFd(void) const;
		void				setFd(int const &fd);
		std::string			&getMessage(void);
		void				setMessage(std::string const &message);
		std::string const	&getNickname(void) const;
		void				setNickname(std::string const &nickname);
		std::string	const	&getUsername(void) const;
		void				setUsername(std::string const &username);
		std::string			const &getMode() const;
		void				setMode(std::string const &mode);
		int	const			&getChannelNb(void) const;
		void				setChannelNb(int const &nb);

		bool	_isConnected;
		bool	_passwordOk;
		bool	_nicknameOk;
		bool	_usernameOk;

	private:

		int			_fd;
		std::string	_message;
		std::string	_nickname;
		std::string	_username;
		std::string	_mode;
		int			_channelNb;
};

#endif