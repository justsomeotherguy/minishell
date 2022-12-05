/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jwilliam <jwilliam@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/07 13:38:05 by jwilliam          #+#    #+#             */
/*   Updated: 2022/12/05 19:55:05 by jwilliam         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <stdbool.h>

t_super		g_super;

static void	free_main_items(char *line, char *prompt)
{
	free_cmds(&g_super.cmds);
	free_2d_array(g_super.full_tokens);
	free(prompt);
	free(line);
}

char	*ft_strjoin_safe_free(char *s1, char *s2, bool f1, bool f2)
{
	char	*str;

	str = ft_strjoin(s1, s2);
	if (f1)
		free(s1);
	if (f2)
		free(s2);
	return (str);
}

static char	*get_prompt(void)
{
	char	*prompt;
	t_envar	*temp;

	prompt = ft_strdup(T_RED);
	temp = find_env(g_super.envar, "USER");
	if (temp)
	{
		prompt = ft_strjoin_safe_free(prompt, (char *)temp->data, true, false);
		prompt = ft_strjoin_safe_free(prompt, "@minishell ", true, false);
	}	
	else
	{
		prompt = ft_strjoin_safe_free(prompt, "guest", true, false);
		prompt = ft_strjoin_safe_free(prompt, "@minishell ", true, false);
	}
	temp = find_env(g_super.envar, "PWD");
	prompt = ft_strjoin_safe_free(prompt, T_BLUE, true, false);
	if (temp)
		prompt = ft_strjoin_safe_free(prompt, (char *)temp->data, true, false);
	else
		prompt = ft_strjoin_safe_free(prompt, "Unable to find $PWD", true,
				false);
	prompt = ft_strjoin_safe_free(prompt, T_DEFAULT, true, false);
	prompt = ft_strjoin_safe_free(prompt, " $> ", true, false);
	return (prompt);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*prompt;

	init_super();
	set_env(envp);
	rebuild_envar_arr();
	make_signal();
	while (1)
	{
		prompt = get_prompt();
		if (prompt == NULL)
			return (1); // TODO: FREE.
		line = readline(prompt);
		if (!line)
			write(1, "\n", 1);
		else
		{
			add_history(line);
			g_super.full_tokens = make_tokens(line);
			for (int i = 0; g_super.full_tokens[i]; i++)
				dprintf(2, "full tokens - '%s'\n", g_super.full_tokens[i]);
			parse_token();
			executor();
		}
		free_main_items(line, prompt);
	}
	return (0);
}
