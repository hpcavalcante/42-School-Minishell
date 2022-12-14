/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:11:01 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 20:51:58 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	linked_list(t_link *link, t_link *new)
{
	if (link->cmd == NULL)
	{
		link->append = new->append;
		link->delimiter = new->delimiter;
		link->file_in = new->file_in;
		link->file_out = new->file_out;
		link->cmd = new->cmd;
		link->next = NULL;
		link->fd_in = new->fd_in;
		link->fd_out = new->fd_out;
		link->path = new->path;
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
	new->file_in = NULL;
	new->file_out = NULL;
	new->next = NULL;
	new->delimiter = 0;
	new->append = 0;
	new->fd_in = 0;
	new->fd_out = 0;
	new->path = NULL;
}
