/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:11:58 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/14 16:38:18 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_builtin(t_link *link)
{
	if (link->file_out == NULL && link->next != NULL)
		dup2(link->pipe_fd[1], STDOUT);
	if (ft_str_check(link->cmd[0], "echo"))
		echo_builtin(link->cmd);
	else if (ft_str_check(link->cmd[0], "pwd"))
		pwd_builtin();
	else if (ft_str_check(link->cmd[0], "exit"))
		exit_builtin(link->cmd);
	else if (ft_str_check(link->cmd[0], "env"))
		env_builtin(link->cmd);
	else if (ft_str_check(link->cmd[0], "export"))
		export_builtin(link->cmd);
	else if (ft_str_check(link->cmd[0], "cd"))
		cd_builtin(link->cmd);
	else if (ft_str_check(link->cmd[0], "unset"))
		unset_builtin(link->cmd);
	dup2(link->pipe_fd[0], STDIN);
	dup2(g_data->save_stdout, STDOUT);
	close(link->pipe_fd[0]);
	close(link->pipe_fd[1]);
}

void	process(t_link *link)
{
	g_data->in_exec = 1;
	g_data->signal = 0;
	if (pipe(link->pipe_fd) == -1)
		exit (-1);
	if (check_built_in(link))
		exec_builtin(link);
	else
	{
		g_data->pid = fork();
		if (g_data->pid == 0)
		{
			g_data->link->path = get_path(link, g_data->envp);
			child_process();
		}
		parent_process(link);
	}
}

void	child_process(void)
{
	int	exitc;

	exitc = g_data->exitcode;
	close(g_data->link->pipe_fd[0]);
	if (g_data->link->next != NULL)
		dup2(g_data->link->pipe_fd[1], 1);
	close(g_data->link->pipe_fd[1]);
	execve(g_data->link->path, g_data->link->cmd, g_data->envp);
	printf("\033[1;31mUnknown error! \e[0m\n");
	free_all();
	exit(exitc);
}

void	parent_process(t_link *link)
{
	int	wstatus;

	close(link->pipe_fd[1]);
	if (link->next != NULL)
	{
		dup2(link->pipe_fd[0], 0);
		waitpid(g_data->pid, &wstatus, 0);
		if (g_data->signal == 1)
			g_data->exitcode = 130;
		else if (g_data->signal == 2)
			g_data->exitcode = 131;
		else
			g_data->exitcode = WEXITSTATUS(wstatus);
	}
	else
	{
		waitpid(g_data->pid, &wstatus, 0);
		if (g_data->signal == 1)
			g_data->exitcode = 130;
		else if (g_data->signal == 2)
			g_data->exitcode = 131;
		else
			g_data->exitcode = WEXITSTATUS(wstatus);
	}
	close (link->pipe_fd[0]);
}
