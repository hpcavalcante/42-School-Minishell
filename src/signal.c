/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 00:40:58 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/14 01:13:30 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	kill_loop(int signal)
{
	(void) signal;
	if (g_data->here_doc == 1)
	{
		close (STDIN);
		g_data->error = 1;
		g_data->exitcode = 130;
	}
	if (g_data->pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->pid, SIGKILL);
		write(1, "\n", 1);
		g_data->signal = 1;
	}
	if (g_data->in_exec == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_data->exitcode = 130;
	}
}

void	core_dump(int signal)
{
	(void) signal;
	if (g_data->pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->pid, SIGKILL);
		write(1, "Quit (Core dumped)\n", 20);
		g_data->signal = 2;
	}
}
