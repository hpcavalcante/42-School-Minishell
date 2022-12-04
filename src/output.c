/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:25:41 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/01 18:54:55 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_output_file(t_link *link)
{
	if (link->file_out != NULL)
	{
		if (access(link->file_out, F_OK) == -1)
			link->fd_out = open(link->file_out, O_CREAT |
			O_WRONLY | O_APPEND, 0644);
		else if (access(link->file_out, F_OK) == 0 && link->append == 0)
			link->fd_out = open(link->file_out, O_WRONLY | O_TRUNC);
		else if (access(link->file_out, F_OK) == 0 && link->append == 1)
			link->fd_out = open(link->file_out, O_WRONLY | O_APPEND);
		dup2(link->fd_out, STDOUT);
	}
}
