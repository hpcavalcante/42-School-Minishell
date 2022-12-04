/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 16:45:47 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/04 17:01:55 by hepiment         ###   ########.fr       */
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

void	free_all()
{
	if (g_data->link != NULL)
	if (g_data->buffer != NULL)
		free (g_data->buffer);
	//free_matrix(g_data->envp);
	rl_clear_history();
	close(g_data->save_stdin);
	close(g_data->save_stdout);
	free (g_data);
}