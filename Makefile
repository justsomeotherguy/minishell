# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 14:18:22 by jwilliam          #+#    #+#              #
#    Updated: 2022/12/15 14:05:31 by jwilliam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc -g

INCL = includes
INCL_RL = /usr/local/opt/readline/include/
LINK_RL = /usr/local/opt/readline/lib

LIB = libft

FLAGS = #-Wall -Werror -Wextra

RM = rm -rf

FILES = main.c \
		builtins.c \
		builtin_cmds.c \
		envvars.c \
		envvarutils.c \
		envvar_utils2.c \
		error.c \
		execute.c \
		execute_setfds.c \
		execute_utils.c \
		free.c \
		init_main.c \
		parse_token.c \
		parse_token_utils.c \
		sig.c \
		token.c \
		token_utils.c \
		token_utils2.c \
		token_expand.c \
		utils.c \
		path.c \
		here_doc.c \

OBJS_NAME = $(FILES:.c=.o)

OBJS = $(addprefix $(OBJS_DIR), $(OBJS_NAME))
SRCS = $(addprefix $(SRC_DIR), $(FILES))
SRC_DIR = srcs/
OBJS_DIR = objs/

all: $(NAME)

$(NAME): $(OBJS)
		@$(MAKE) -C ./$(LIB)
		@$(CC) $(FLAGS) $(OBJS) -L$(LIB) $(LIB)/$(LIB).a -L $(LINK_RL) -lreadline -o $@
		@echo "\033[32m████████████████████████████"
		@echo "\033[32m█████\033[39mminishell  created\033[32m█████"
		@echo "\033[32m████████████████████████████\033[39m"

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< -I $(INCL) -I ./$(LIB)/$(INCL) -I $(INCL_RL) 

clean:
		@$(MAKE) clean -C ./$(LIB)
		@$(RM) $(OBJS)
		@$(RM) $(OBJS_DIR)
		@echo "\033[33m████████████████████████████"
		@echo "\033[33m█████\033[39mcleaned  minishell\033[33m█████"
		@echo "\033[33m█████   \033[39mobject files   \033[33m█████"		
		@echo "\033[33m████████████████████████████\033[39m"

fclean:	clean
		@$(MAKE) fclean -C ./$(LIB)		
		@$(RM) $(NAME)
		@$(RM) $(NAME).a
		@echo "\033[33m████████████████████████████"
		@echo "\033[33m█████      \033[39mcleaned     \033[33m█████"
		@echo "\033[33m█████  \033[39mminishell file  \033[33m█████"		
		@echo "\033[33m████████████████████████████\033[39m"

re: fclean all

.PHONY: clean fclean all re
