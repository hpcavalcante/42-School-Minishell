/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:45:47 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/08 23:20:15 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_matrix(char **s)
{
	int	i;

	i = 0;
	while (s[i] != NULL)
		free(s[i++]);
	free(s);
}

void	free_link()
{	
	t_link	*temp;

	if (g_data->link)
	{
		while (g_data->link)
		{
			temp = g_data->link;
			g_data->link = g_data->link->next;
			if (temp->cmd)
				free_matrix(temp->cmd);
			if (temp->path)
				free(temp->path);
			free(temp);
		}
	}
}

void	free_all()
{
	if (g_data->buffer != NULL)
		free (g_data->buffer);
	rl_clear_history();
	close(g_data->save_stdin);
	close(g_data->save_stdout);
	free_link(link);
	free(g_data);
}