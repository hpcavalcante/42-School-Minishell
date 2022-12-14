/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/25 14:43:36 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 20:49:38 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_str_isnum(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] <= '9' && str[i] >= '0')
			i++;
		else
			return (0);
	}
	return (1);
}

void	exit_builtin(char **cmd)
{
	int	status;

	write (1, "exit\n", 5);
	if (cmd[1] != NULL && ft_str_isnum(cmd[1]) == 0)
	{
		g_data->exitcode = 2;
		ft_putstr_fd("exit: ", STDERR);
		ft_putstr_fd(cmd[1], STDERR);
		ft_putstr_fd(": numeric argument required\n", STDERR);
	}
	else if (cmd[1] != NULL && cmd[2] != NULL)
	{
		g_data->exitcode = 1;
		ft_putstr_fd("exit: too many arguments\n", STDERR);
	}
	else if (cmd[1] != NULL && ft_str_isnum(cmd[1]) == 1)
		g_data->exitcode = ft_atoi(cmd[1]);
	status = g_data->exitcode;
	free_all();
	exit(status);
}
