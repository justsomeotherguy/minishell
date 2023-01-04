/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_cmds.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:25:21 by jwilliam          #+#    #+#             */
/*   Updated: 2023/01/04 14:22:43 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

/*
Creates a new environment variable using input token as name and data to
fill in the node.
*/
int	builtin_export(char **tokens)
{
	char		**split;

	split = ft_split(tokens[1], '=');
	if (!split[1])
		return (1);
	else
		add_env(&g_super.envar, new_env(split[0], split[1]));
	free(split);
	return (0);
}

int	builtin_pwd(void)
{
	printf("%s\n", (char *)find_env(g_super.envar, "PWD")->data);
	g_super.status = 0;
	return (0);
}

/*
Emulates the echo command, check if second token is -n to verify if option
is used, then print remaining tokens followed by newline if -n was used.
*/
int	builtin_echo(char **tokens)
{
	int			i;
	int			option;

	i = 0;
	option = 0;
	if (!tokens[1])
		return (1);
	if (tokens[1] && ft_strcmp(tokens[1], "-n") == 0)
	{
		i++;
		option++;
	}
	while (tokens[++i] != NULL)
	{
		if ((ft_strcmp(tokens[i], "-n") != 0) && tokens[i] != NULL)
		{
			printf("%s", tokens[i]);
			if (tokens[i + 1] != 0)
				printf(" ");
		}
	}
	if (option != 1)
		printf("\n");
	g_super.status = 0;
	return (0);
}

static void	change_dirs(t_envar *pwd, t_envar *old, char *cwd)
{
	free(old->data);
	old->data = (char *)ft_strdup(pwd->data);
	free(pwd->data);
	pwd->data = ft_strdup(cwd);
}

/*
Emulate the cd command in shell, first checks chdir (change directory) tokens[1]
if it is a valid directory, it should be able to check if absolute or relative.
If valid, change the environment variable of pwd to reflect that the
working directory is changed.
*/
int	builtin_cd(char **tokens)
{
	char		cwd[256];
	t_envar		*pwd;
	t_envar		*oldpwd;

	pwd = find_env(g_super.envar, "PWD");
	oldpwd = find_env(g_super.envar, "OLDPWD");
	if (chdir(tokens[1]) == 0)
	{
		if (getcwd(cwd, sizeof(cwd)) == NULL)
		{
			error_message("cd error", 1);
			return (1);
		}
		else
			change_dirs(pwd, oldpwd, cwd);
	}
	else
	{
		error_message("No such file or directory", 1);
		return (1);
	}
	return (0);
}
