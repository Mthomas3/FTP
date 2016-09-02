##
## Makefile<2> for  in /home/mart_4/rendu/PSU_2015_malloc
##
## Made by Thomas Martins
## Login   <mart_4@epitech.net>
##
## Started on  Mon Jan 25 23:08:27 2016 Thomas Martins
## Last update Sun May 15 11:55:11 2016 Thomas Martins
##

NAME	=	server

CC      =	gcc

SRC	=	src/main.c		\
		src/errors/errors.c		\
		src/server/sockets.c		\
		src/server/commands.c		\
		src/server/commands_options.c	\
		src/parsing/str_to_word_tab.c	\
		src/parsing/options.c	\
		src/server/settings.c		\
		src/parsing/list.c		\
		src/commands/server_commands.c\
		src/commands/server_deep.c\
		src/commands/server_options.c\
		src/commands/server_tools.c\

RM      =	rm -f

OBJ	=	$(SRC:.c=.o)

CFLAGS	+=	-W -Wall -Wextra -Werror

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) -o $(NAME) $(OBJ)

%.o : %.c
		$(CC) -c $(CFLAGS) -o $@ $^

clean:
		$(RM) $(OBJ)

fclean:		clean
		$(RM) $(NAME)

re:		fclean all
