#ifndef CHANNEL_HPP
#define CHANNEL_HPP

/*==========================*/
/*=====    INCLUDES    =====*/
/*==========================*/

#include "../../ft_irc.hpp"

/*==========================*/
/*=======    CLASS    ======*/
/*==========================*/
class Channel
{
	public:

		Channel(void);
		~Channel(void);
		
		std::vector<int> clients;
		std::string	topic;
};

#endif