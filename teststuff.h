/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   teststuff.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/08 12:32:00 by jwilliam          #+#    #+#             */
/*   Updated: 2022/09/21 15:15:44 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTSTUFF_H
# define TESTSTUFF_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>

# include <readline/readline.h>
# include <readline/history.h>

# include <signal.h>

/* token.c */
int			get_line_length(char *line);
int			token_length(char const *line);
char		*make_token(char *line);
char		**make_tokens(char *line);

/* builtins.c */
char		**set_builtin(char **builtin);
void		is_builtin(char **tokens);

/* sig.c */
void		sig_handler_int(int sig_num);
void		sig_handler_quit(int sig_num);

/* utils.c */
int			ft_strlen(const char *str);
int			ft_strcmp(char *s1, char *s2);

#endif