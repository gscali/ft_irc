#include "../ft_irc.hpp"

void	ft_error(std::string s)
{
	std::cout << s << std::endl;
	exit(1);
}

std::vector<std::string>	ft_split (std::string str, std::string delimiter)
{
	std::vector<std::string> array;
	std::string	temp;
	size_t 	pos;
	
	while((pos = str.find(delimiter)) != std::string::npos)
	{
		temp = str.substr(0, pos);
		if (!temp.empty())
			array.push_back(temp);
		str.erase(0, pos + delimiter.length());
	}
	if ((pos = str.find(delimiter)) == std::string::npos)
		array.push_back(str);
	return(array);
}