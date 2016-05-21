##
## Makefile for mysh in /home/bongol_b/rendu/PSU_2015_minishell1
## 
## Made by Berdrigue BONGOLO BETO
## Login   <bongol_b@epitech.net>
## 
## Started on  Thu Jan  7 23:28:48 2016 Berdrigue BONGOLO BETO
## Last update Sun Jan 24 21:54:33 2016 Berdrigue BONGOLO BETO
##

CC	= 	gcc

RM	= 	rm -f

NAME	= 	mysh

B_DIR	= 	src

SRCS	= 	main.c \
		malloc_handlers.c \
		execute_cmd.c \
		execute_cmd_util.c \
		execute_cmd_util2.c \
		builtin_unsetenv.c \
		builtin_setenv.c \
		builtin_exit.c \
		builtin_env.c \
		builtin_cd.c \
		builtin_help.c \
		builtin_alias.c \
		env_util.c \
		env_util2.c \
		init_builtins.c \
		file_util.c \
		config.c \
		config_util.c \
		config_util2.c \
		config_util3.c \
		bonus_util.c \
		alias_handler.c \
		signal_util.c \

OBJS	= 	$(SRCS:.c=.o)

CFLAGS	+=	-W -Wall -Werror -pedantic
CFLAGS	+=	-I./include/ -I./lib/my/include/

LDFLAGS +=	-L./lib -lmy -L./lib/my_printf -lmyprintf

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) $(LDFLAGS)

libmy:
	@$(MAKE) -C lib/my

libmyprintf:
	@$(MAKE) -C lib/my_printf

clean:
	@$(RM) $(OBJS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all

.PHONY: clean, mrproper, re, all, fclean
