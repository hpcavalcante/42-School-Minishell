/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 10:41:24 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/13 20:51:41 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	handle_here_doc(t_link *link)
{
	int		fd;
	char	*line;

	if (access(".here_doc", F_OK))
		unlink(".here_doc");
	fd = open(".here_doc", O_CREAT | O_WRONLY | O_TRUNC, 0644);
	while (1)
	{
		line = readline(">");
		if (line == NULL || ft_str_check(line, link->file_in) == 1)
		{
			if (line != NULL)
				free (line);
			if (line == NULL && g_data->error == 0)
				printf (" warning: here-document delimited by"
					" end-of-file (wanted `%s')\n", link->file_in);
			close(fd);
			link->fd_in = open(".here_doc", O_RDONLY);
			unlink(".here_doc");
			return ;
		}
		write (fd, line, ft_strlen(line));
		write (fd, "\n", 1);
		free(line);
	}
}

void	quit_core(int signum)
{
	(void)signum;
	if (g_data->exec_pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->exec_pid, SIGKILL);
		ft_putstr_fd("Quit (Core dumped)\n", 1);
	}
}

void	handle_input_file(t_link *link)
{
	if (link->file_in != NULL)
	{
		if (access(link->file_in, F_OK | R_OK) == -1 && link->delimiter == 0)
		{
			write (2, link->file_in, ft_strlen(link->file_in));
			write (2, ": No such file or directory\n", 28);
			g_data->error = 1;
			return ;
		}
		else if (access(link->file_in, F_OK | R_OK) \
		== 0 && link->delimiter == 0)
			link->fd_in = open (link->file_in, O_RDONLY);
		else if (link->delimiter == 1)
		{
			g_data->here_doc = 1;
			signal (SIGQUIT, SIG_IGN);
			handle_here_doc(link);
			signal (SIGQUIT, quit_core);
			g_data->here_doc = 0;
		}
		dup2 (link->fd_in, STDIN);
	}
}
