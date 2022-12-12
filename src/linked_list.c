/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:11:01 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/11 15:45:10 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	linked_list(t_link *link, t_link *new)
{
	if (link->cmd == NULL)
	{
		link->append = new->append;
		link->file_out = new->file_out;
		link->fd_out = new->fd_out;
		link->cmd = new->cmd;
		// link->next = new->next;
		link->path = new->path;
		link->next = NULL;
		//o ultimo elemnto da lista linkada precisa ser nulo!!
		free (new);
	}
	else
	{
		while (link->next != NULL)
			link = link->next;
		link->next = new;
	}
}

void	init_linked_list(t_link *new)
{
	new->cmd = NULL;
	new->next = NULL;
	new->path = NULL;
	new->file_out = NULL;
	new->append = 0;
	new->fd_out = 0;
}