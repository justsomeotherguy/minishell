/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 14:29:45 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/05 13:44:51 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_super	g_super;

static char	*get_path(char const *currentPath, char const *cmd)
{
	char	*rtn;

	if (*cmd == '/')
		rtn = ft_strdup(cmd);
	else if (!ft_strncmp(cmd, "./", 2))
		rtn = ft_strjoin((find_env(g_super.envar, "PWD")->data),
				ft_strjoin("/", cmd));
	else
		rtn = ft_strjoin(currentPath, ft_strjoin("/", cmd));
	return (rtn);
}

char	**init_pathlist(void)
{
	char			**pathlst;
	t_envar const	*path;

	path = find_env(g_super.envar, "PATH");
	if (path)
		pathlst = ft_split(path->data, ':');
	else
		pathlst = NULL;
	return (pathlst);
}

char	*get_path_for_cmd(char **pathlst, char const *cmd)
{
	char	*path;
	int		i;

	i = 0;
	while (pathlst[i])
	{
		path = get_path(pathlst[i], cmd);
		if (access(path, F_OK) == 0)
			return (path);
		free(path);
		i++;
	}
	return (NULL);
}
