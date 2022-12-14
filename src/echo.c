/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:26:17 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/12 16:55:00 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(char **cmd)
{
	int	i;

	i = 1;
	if (cmd[1] == NULL)
		write (1, "\n", 1);
	else
	{
		if (ft_str_check(cmd[1], "-n") || ft_str_check(cmd[1], "-e"))
			i++;
		while (cmd[i] != NULL)
		{
			if (cmd[i][0] != '\0')
				ft_putstr_fd(cmd[i], 1);
			if (cmd[i + 1] != NULL)
				write (1, " ", 1);
			i++;
		}
		if ((ft_str_check(cmd[1], "-n")) == 0)
			write (1, "\n", 1);
	}
	g_data->exitcode = 0;
	return ;
}
