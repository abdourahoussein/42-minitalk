# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: abhousse <abhousse@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/09 00:05:14 by abhousse          #+#    #+#              #
#    Updated: 2022/03/10 02:44:10 by abhousse         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CC_FLAGS = -Wall -Wextra -Werror -I.

HEADER		= minitalk.h

S_SRCS		= server.c utilis.c
C_SRCS		= client.c utilis.c

C_OBJS	= ${C_SRCS:.c=.o}
S_OBJS	= ${S_SRCS:.c=.o}

S_BONUS_SRCS		= server_bonus.c utilis.c
C_BONUS_SRCS		= client_bonus.c utilis.c

C_OBJS_BONUS	= ${C_BONUS_SRCS:.c=.o}
S_OBJS_BONUS	= ${S_BONUS_SRCS:.c=.o}

NAME_CLIENT = client
NAME_SERVER = server
NAME_CLIENT_B = client_bonus
NAME_SERVER_B = server_bonus


all: $(NAME_CLIENT) $(NAME_SERVER)

bonus: $(NAME_CLIENT_B) $(NAME_SERVER_B)

client: $(C_SRCS) $(HEADER)
	gcc $(CC_FLAGS) $(C_SRCS) -o $(NAME_CLIENT)

server: $(S_SRCS) $(HEADER)
	$(CC) $(CC_FLAGS) $(S_SRCS) -o $(NAME_SERVER)

client_bonus: $(C_BONUS_SRCS) $(HEADER)
	$(CC) $(CC_FLAGS) $(C_BONUS_SRCS) -o $(NAME_CLIENT_B)

server_bonus: $(S_BONUS_SRCS) $(HEADER)
	$(CC) $(CC_FLAGS) $(S_BONUS_SRCS) -o $(NAME_SERVER_B)

clean:
		rm -f ${C_OBJS}
		rm -f ${C_OBJS_BONUS}
		rm -f ${S_OBJS}
		rm -f ${S_OBJS_BONUS}


fclean:	clean
			
		rm -f client
		rm -f server
		rm -f client_bonus
		rm -f server_bonus


re:	fclean all