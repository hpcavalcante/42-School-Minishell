/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 23:03:00 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 07:24:41 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	command(char *checked_line)
{
	t_link	*temp;
	t_link	*new;

	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	temp = g_data->link;
	while (temp->next != NULL)
		temp = temp->next;
	new->cmd = space_split(checked_line);
	linked_list(temp, new);
	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	temp = g_data->link;
	if (g_data->checked_line != NULL)
		free(g_data->checked_line);
	g_data->checked_line = NULL;
}
