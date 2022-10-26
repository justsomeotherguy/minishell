# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/19 14:18:22 by jwilliam          #+#    #+#              #
#    Updated: 2022/10/20 15:39:44 by jwilliam         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc

INCL = includes
#INCL_RL = /usr/local/opt/readline/include/

LIB = libft

FLAGS = #-Wall -Werror -Wextra

#RL = /usr/local/opt/readline/lib -lreadline

RM = rm -rf

FILES = main.c \
		builtins.c \
		builtin_cmds.c \
		envvars.c \
		envvarutils.c \
		execute.c \
		free.c \
		init_main.c \
		parse_token.c \
		parse_token_utils.c \
		sig.c \
		token.c \
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
		@$(CC) $(FLAGS) $(OBJS) -L$(LIB) $(LIB)/$(LIB).a -lreadline -o $@
		@echo "\033[32m████████████████████████████"
		@echo "\033[32m█████ \033[39mpushswap created \033[32m█████"
		@echo "\033[32m████████████████████████████ \033[39m"

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
		@mkdir -p $(OBJS_DIR)
		@$(CC) $(FLAGS) -o $@ -c $< -I $(INCL) -I ./$(LIB)/$(INCL) -lreadline

clean:
		@$(MAKE) clean -C ./$(LIB)
		@$(RM) $(OBJS)
		@$(RM) $(OBJS_DIR)
		@echo "\033[33m████████████████████████████"
		@echo "\033[33m█████ \033[39mcleaned pushswap \033[33m█████"
		@echo "\033[33m█████   \033[39mobject files   \033[33m█████"		
		@echo "\033[33m████████████████████████████ \033[39m"

fclean:	clean
		@$(MAKE) fclean -C ./$(LIB)		
		@$(RM) $(NAME)
		@$(RM) $(NAME).a
		@echo "\033[33m████████████████████████████"
		@echo "\033[33m█████      \033[39mcleaned     \033[33m█████"
		@echo "\033[33m█████ \033[39mpushswap.a files \033[33m█████"		
		@echo "\033[33m████████████████████████████ \033[39m"

re: fclean all

.PHONY: clean fclean all re