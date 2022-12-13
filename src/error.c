/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:13:26 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 09:10:39 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	syntax_error(char c)
{
	ft_putstr_fd(SYNTAX_ERROR, STDERR);
	ft_putchar_fd(c, STDERR);
	write(STDERR, "'\n", 3);
	g_data->exitcode = 2;
	g_data->error = 1;
}

void	dir_error(char **cmd)
{
	g_data->exitcode = 1;
	write(STDERR, "cd: ", 4);
	write(STDERR, cmd[1], ft_strlen(cmd[1]));
	if (access(cmd[1], F_OK) == 0)
		write(STDERR, ": Not a directory\n", 18);
	else
		write(STDERR, ": No such file or directory\n", 28);
}
