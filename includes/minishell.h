/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:00 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/03 14:34:03 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <sys/wait.h>
# include <sys/types.h>

# include <signal.h>

# include <fcntl.h>

# include "libft.h"

# define T_DEFAULT	"\033[0m"
# define T_RED		"\033[1;91m"
# define T_BLUE		"\033[1;94m"

typedef struct s_super
{
	struct s_envar		*envar;
	char				**builtins;
	char				**full_tokens;
	struct s_cmdset		*cmds;
	int					status;
	char				*heredoc;
}	t_super;

typedef struct s_envar
{
	char				*name;
	void				*data;
	struct s_envar		*next;
}	t_envar;

typedef struct s_cmdset
{
	char				**tokens;
	int					pid;
	int					fd_in;
	int					fd_out;
	struct s_cmdset		*next;
}	t_cmdset;

/* token.c */
int			get_line_length(char *line);
int			token_length(char const *line);
char		*make_token(char *line);
char		**make_tokens(char *line);
void		expand_tokens(char **tokens);

/* builtins.c */
int			is_builtin(char **tokens);
void		do_builtin(int builtin_id, char **tokens);

/* builtin_cmds.c */
void		builtin_pwd(void);
void		builtin_export(char **tokens);
void		builtin_echo(char **tokens);
void		builtin_cd(char **tokens);

/* envvars.c */
void		set_env(char **envp);
void		print_env(void);

/* envvarutils.c */
t_envar		*new_env(char *name, void *data);
void		add_env(t_envar **envars, t_envar *new);
t_envar		*to_last(t_envar *envars);
void		find_and_remove(t_envar *envars, char *var_name);
t_envar		*find_env(t_envar *envars, char *name);

/* execute.c */
void		executor(void);

/* free.c */
void		free_cmds(t_cmdset **cmdsets);
void		free_2d_array(char **array);

/* init_main.c */
void		init_super(void);
char		**set_builtin(char **builtin);

/* parse_token.c */
void		parse_token(void);

/* parse_token_utils.c */
t_cmdset	*new_cmdset(void);
void		add_cmdset(t_cmdset **cmdset, t_cmdset *new);
t_cmdset	*to_last_cmdset(t_cmdset *cmdset);

/* sig.c */
void		sig_handler_int(int sig_num);
void		sig_handler_quit(int sig_num);

/* utils.c */
int			ft_strcmp(char *s1, char *s2);
int			is_meta(char c, char next);

/* path.c */
char		**init_pathlist(void);
char		*get_path_for_cmd(char **pathlst, char const *cmd);

/* heredoc */
int			get_heredoc(void);

#endif