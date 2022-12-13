/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:45:47 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 07:21:00 by hepiment         ###   ########.fr       */
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

void	free_list(t_link *link)
{
	t_link	*temp;

	while (link != NULL)
	{
		temp = link->next;
		free(link->file_in);
		free(link->file_out);
		if (link->fd_in != 0)
			close (link->fd_in);
		if (link->fd_out != 0)
			close (link->fd_out);
		if (link->cmd != NULL)
			free_matrix(link->cmd);
		free(link->path);
		free (link);
		link = temp;
	}
}

void	free_all(void)
{
	if (g_data->link != NULL)
		free_list(g_data->link);
	if (g_data->buffer != NULL)
		free (g_data->buffer);
	free_matrix(g_data->envp);
	rl_clear_history();
	close(g_data->save_stdin);
	close(g_data->save_stdout);
	free (g_data);
}
