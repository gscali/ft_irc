NAME = ircserv
SRCS =	srcs/main.cpp \
		srcs/utils.cpp \
		srcs/create_server.cpp \
		srcs/run_server.cpp \
		srcs/cmds/pass_command.cpp \
		srcs/cmds/user_command.cpp \
		srcs/cmds/nick_command.cpp \
		srcs/cmds/ping_command.cpp \
		srcs/cmds/mode_command.cpp \
		srcs/cmds/oper_command.cpp \
		srcs/cmds/kill_command.cpp \
		srcs/cmds/quit_command.cpp \
		srcs/cmds/join_command.cpp \
		srcs/cmds/privmsg_command.cpp \
		srcs/cmds/notice_command.cpp \
		srcs/cmds/part_command.cpp \
		srcs/cmds/topic_command.cpp \
		srcs/cmds/send_error.cpp \
		srcs/classes/Server.cpp \
		srcs/classes/Client.cpp \
		srcs/classes/Parser.cpp \
		srcs/classes/Channel.cpp

CFLAGS = -Wall -Wextra -Werror -std=c++98
OBJS = $(SRCS:.cpp=.o)

$(NAME): $(OBJS)
	c++ $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp
	c++ -o $@ -c $< $(CFLAGS)

all: $(NAME)

clean:
	@rm -rf */*.o */*/*.o

fclean:
	@rm -rf */*.o */*/*.o $(NAME)

re: fclean all

.PHONY: all clean fclean re