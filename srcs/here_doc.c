#include "minishell.h"

t_super		g_super;

int	get_heredoc(void)
{
	char	*line;
	int		fd;

	fd = open("/tmp/.heredoc", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (fd == -1)
		return (1);
	while (1)
	{
		line = readline("heredoc> ");
		if (!line)
			return (1);
		if (ft_strcmp(line, g_super.heredoc) == 0)
			break ;
		write(fd, line, ft_strlen(line));
	}
	return (fd);
}