/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:25:21 by jwilliam          #+#    #+#             */
/*   Updated: 2022/11/30 16:47:26 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

/*
Creates a new environment variable using input token as name and data to
fill in the node.
*/
void	builtin_export(char **tokens)
{
	char		**split;
	int			i;

	split = ft_split(tokens[1], '=');
	i = 0;
	if (!split[1])
		return ;
	else
	{
		add_env(&g_super.envar, new_env(split[0], split[1]));
	}
	free(split);
	return ;
}

void	builtin_pwd(void)
{
	printf("%s\n", (char *)find_env(g_super.envar, "PWD")->data);
	g_super.status = 0;
	return ;
}

/*
Emulates the echo command, check if second token is -n to verify if option
is used, then print remaining tokens followed by newline if -n was used.
*/
void	builtin_echo(char **tokens)
{
	int			i;
	int			option;

	i = 1;
	option = 0;
	if (!tokens[1])
		exit(1) ;
	if (tokens[1] && ft_strcmp(tokens[1], "-n") == 0)
	{
		i++;
		option++;
	}
	while (tokens[i])
	{	
//		ft_putstr_fd(tokens[i], 1);
		printf("%s", tokens[i]);
		i++;
		if (tokens[i] != 0)
			printf(" ");
//			ft_putchar_fd(' ', 1);
	}
	if (option != 1)
		printf("\n");
//		ft_putchar_fd('\n', 1);
	g_super.status = 0;
	dprintf(2, "done echo\n");
	exit (0);
}

/*
Emulate the cd command in shell, first checks chdir (change directory) tokens[1]
if it is a valid directory, it should be able to check if absolute or relative.
If valid, change the environment variable of pwd to reflect that the
working directory is changed.
*/
void	builtin_cd(char **tokens)
{
	char		cwd[256];
	t_envar		*pwd;
	t_envar		*oldpwd;

	pwd = find_env(g_super.envar, "PWD");
	oldpwd = find_env(g_super.envar, "OLDPWD");
	if (chdir(tokens[1]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
			printf("getcwd error\n");
		else
		{
			free(oldpwd->data);
			oldpwd->data = (char *)ft_strdup(pwd->data);
			free(pwd->data);
			pwd->data = ft_strdup(cwd);
		}
	}
	else
		printf("chdir error\n");
	return ;
}
