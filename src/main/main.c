/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:46:55 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/08 20:36:07 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data *g_data;

void	kill_loop(int signal)
{
	(void) signal;
	if (g_data->here_doc == 1)
	{
		close (STDIN);
		g_data->error = 1;
	}
	if (g_data->pid != 0 && g_data->in_exec == 1)
	{
		kill(g_data->pid, SIGKILL);
		write(1, "\n", 1);
	}
	if (g_data->in_exec == 0)
	{
		write(1, "\n", 1);
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
	g_data->exitcode = 130;
}

int	ft_str_check(const char *s1, const char *s2)
{
	int	a;

	a = 0;
	while (s1[a] == s2[a] && s1[a] != '\0')
		a++;
	if (s1[a] == '\n' && s2[a] == '\0')
		return (1);
	else if (s1[a] == s2[a])
		return (1);
	else
		return (0);
}

void	child_process()
{
	close(g_data->link->pipe_fd[0]);
	if (g_data->link->next != NULL)
		dup2(g_data->link->pipe_fd[1], 1);
	close(g_data->link->pipe_fd[1]);
	execve(g_data->link->path, g_data->link->cmd, g_data->envp);
}

void	chupica()
{
	if (g_data->buffer != NULL)
	{
		add_history(g_data->buffer);
		t_link *link;
		link = (t_link *)malloc(sizeof (t_link));
		link->next = NULL;
		g_data->link = link;
		if (!parse(g_data->link))
			g_data->error = 1;
		while (g_data->link != NULL && g_data->error == 0)
		{
			process(g_data->link);
			g_data->link = g_data->link->next;	
		}
	}
	else		
	{	
		free_all();
		write(1, "exit\n", 6);
		exit (0);
	}
}
void	init_shell()
{	
	signal(SIGINT, kill_loop);
	while (1)
	{
		g_data->error = 0;
		g_data->buffer = NULL;
		g_data->link = NULL;
		g_data->in_exec = 0;
		signal(SIGQUIT, SIG_IGN);
		g_data->buffer = readline("\e[1;32m[minishell]: \e[0m");
		chupica();
		dup2(g_data->save_stdin, 0);
		dup2(g_data->save_stdout, 1);
		free(g_data->buffer);
	}
}


int	main(int argc, char **argv, char **envp)
{ 
	(void) argv;
	if (argc != 1)
	{
		exit(0);
	}
	g_data = malloc(sizeof(t_data));
	g_data->buffer = NULL;
	g_data->envp = envp;
	g_data->exitcode = 0;
	g_data->save_stdin = dup(0);
	g_data->save_stdout = dup(1);
	t_link *link;
	link = (t_link *)malloc(sizeof (t_link));
	link->next = NULL;
	g_data->link = link;
	init_shell();
}

//fazer  splits de acordo com o numero de pipes + 1, por isso ele usa lista encadeada porque em cada no vai ter uma variavel.