/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:00 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/12 19:34:28 by jwilliam         ###   ########.fr       */
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
# include <sys/ioctl.h>

# include <fcntl.h>

# include "libft.h"

# define T_DEFAULT	"\033[0m"
# define T_RED		"\033[1;91m"
# define T_BLUE		"\033[1;94m"

typedef struct s_super
{
	struct s_envar		*envar;
	char				**envar_arr;
	char				**builtins;
	char				**full_tokens;
	struct s_cmdset		*cmds;
	int					status;
	pid_t				pid;
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
	int					pipefd[2];
	int					fd_in;
	int					fd_out;
	int					cmd_no;
	struct s_cmdset		*next;
}	t_cmdset;

/* token.c */
int			token_length(char const *line);
char		*make_token(char *line);
char		**make_tokens(char *line);
int			count_tokens(char const *line, int count);

/* token_utils.c */
char		*get_envar(char *getname);
int			get_envarname_length(char *token);
char		*trim_quotes(char *str, char c);
int			check_for_dollar(char *str);
int			check_quotes(char *str);

/* token_expand.c */
char		*check_to_trim(char *token);
void		expand_tokens(char **tokens);
char		*make_expanded_str(char *token);
char		*add_expanded_str(char *new, char *token, int pos, int i);

/* builtins.c */
int			is_builtin_child(char **tokens);
int			is_builtin_parent(char **tokens);
void		do_builtin(int builtin_id, char **tokens);

/* builtin_cmds.c */
int			builtin_pwd(void);
int			builtin_export(char **tokens);
int			builtin_echo(char **tokens);
int			builtin_cd(char **tokens);

/* envvars.c */
void		set_env(char **envp);
void		print_env(void);
void		rebuild_envar_arr(void);

/* envvarutils.c */
t_envar		*new_env(char *name, void *data);
void		add_env(t_envar **envars, t_envar *new);
t_envar		*to_last(t_envar *envars);
void		find_and_remove(t_envar *envars, char *var_name);
t_envar		*find_env(t_envar *envars, char *name);

/* envvar_utils2.c */
void		do_remove_envar(t_envar *to_remove, t_envar *prev);

/* error.c */
void		error_message(char *message, int status);
void		mini_perror(void);

/* execute.c */
void		exec_cmd(char **cmds);
int			pipe_exec(t_cmdset *current, int *curr_p, int *new_p);
void		pipe_exec_fin(t_cmdset *current, int *old_p, int *new_p);
int			set_pipe(t_cmdset *current, int *new_p);
void		executor(void);

/* execute_setfds.c */
int			set_filein(t_cmdset *current, char *filein, int set);
int			set_fileout(t_cmdset *current, char *fileout, int set);
int			set_fd_in(t_cmdset *current);
int			set_fd_out(t_cmdset *current);

/* execute_utils.c */
//int			ft_dup2(int old, int new);
void		set_fds(void);
int			set_redir(t_cmdset *current);
void		open_close(t_cmdset *current, int *old_p, int *new_p);

/* free.c */
void		free_cmds(t_cmdset **cmdsets);
void		free_2d_array(char **array);
void		free_envar(t_envar *tofree);

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
void		make_signal(void);

/* utils.c */
int			ft_strcmp(char *s1, char *s2);
int			is_meta(char c, char next);

/* path.c */
char		**init_pathlist(void);
char		*get_path_for_cmd(char **pathlst, char const *cmd);

/* heredoc */
int			get_heredoc(char *end);

#endif