/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 12:25:41 by gissao-m          #+#    #+#             */
/*   Updated: 2022/11/18 15:04:08 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_output_file(t_link *link)
{
	if (link->created_file != NULL)
	{
		if(access(link->created_file, F_OK) == -1 && link->append == 1)
		{
			link->fd_out = open(link->created_file, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		else if (access(link->created_file, F_OK) == 0 && link->append == 0)
			link->fd_out = open(link->created_file, O_WRONLY | O_TRUNC);
		else if (access(link->created_file, F_OK) == 0 && link->append == 1)
			link->fd_out = open(link->created_file, O_WRONLY | O_APPEND);
		dup2(link->fd_out, STDOUT);
		//aqui de fato estou mandando para a saida padrao.
	}
		
}