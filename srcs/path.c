#include "minishell.h"

extern t_super	g_super;

char	**init_pathlist(void)
{
	char	**pathlst;
	t_envar	*path;

	path = find_env(g_super.envar, "PATH");
	if (path)
		pathlst = ft_split(path->data, ':');
	else
		pathlst = NULL;
	return (pathlst);
}
