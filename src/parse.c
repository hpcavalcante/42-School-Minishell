/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/25 17:40:36 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenizer()
{
	int	i;

	i = strlen(g_data->buffer);
	while (i)
	{
		if (g_data->buffer[i] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
			return (1);
		}
		i--;
	}
	return (0);	
}

void	parse()
{
	g_data->pid = fork();
	signal(SIGQUIT, SIG_IGN);
	if (g_data->pid == 0)
	{
		tokenizer();
		g_data->cmd = get_cmd(g_data->buffer);
		g_data->path = get_path(g_data->envp);
		command();
	}
	waitpid(g_data->pid, NULL, 0);
	command();
}
