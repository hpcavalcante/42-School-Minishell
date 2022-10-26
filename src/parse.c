/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/26 13:11:57 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parse()
{
	g_data->pid = fork();
	signal(SIGQUIT, SIG_IGN);
	if (g_data->pid == 0)
	{
		tokenizer();
		g_data->list->cmd = get_cmd(g_data->buffer);
		g_data->list->path = get_path(g_data->envp);
		command();
	}
	waitpid(g_data->pid, NULL, 0);
	command();
}

void	child_process(char **argv, char **env, t_link *link)
{
	char	*temp;
	int		i;

	dup2(link->fd[1], STDOUT_FILENO);
	dup2(link->infile, STDIN_FILENO);
	close(link->fd[0]);
	link->cmd = matrix_block_cmd(argv[2]);
	link->path = find_the_path(link, env);
	i = 0;
	while (link->cmd[i])
	{
		temp = ft_strtrim(link->cmd[i], "\'");
		free (link->cmd[i]);
		link->cmd[i] = ft_strdup(temp);
		free (temp);
		i++;
	}
	execve_error(data, env);
}

void	parent_process(t_data *data, int pid, t_link *link)
{
	int	wstatus;
	int	status_code;

	close(link->pipe_fd[0]);
	close(link->pipe_fd[1]);
	waitpid(pid, NULL, 0);
	if (WIFEXITED(wstatus))
	{
		status_code = WEXITSTATUS(wstatus);
		free(data);
		exit (status_code);
	}
}
