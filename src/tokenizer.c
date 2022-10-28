/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:36:58 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/27 17:12:52 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_putstr_fd(char *s, int fd)
{
	write (fd, s, ft_strlen(s));
}

void	tokenizer()
{
	int	i;

	i = 0;
	while (g_data->buffer[i] != '\0')
	{
		if (g_data->buffer[0] == '|')
		{
			ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
			exit(0);
		}
		i++;
		if (g_data->buffer[i] == '|')
		{
			g_data->link->cmd = ft_split(g_data->buffer, '|');
			for (int i = 0; g_data->link->cmd[i]; i++)
				printf("Buffer: %s\n", g_data->link->cmd[i]);
		}
	}
}