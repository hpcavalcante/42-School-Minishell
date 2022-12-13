/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:46:55 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 11:48:36 by gissao-m         ###   ########.fr       */
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

void	prompt()
{
	t_link *link;
	
	if (g_data->buffer[0] == '\0')
		return ;
	link = (t_link *)malloc(sizeof (t_link));
	link->next = NULL;
	add_history(g_data->buffer);
	init_linked_list(link);
	g_data->link = link;
	if (!parse(g_data->link))
		g_data->error = 1;
	if (g_data->error == 1)
	{
		free_list(g_data->link);
		return ;
	}
	while (g_data->link != NULL && g_data->error == 0)
	{
		process(g_data->link);
		g_data->link = g_data->link->next;	
	}
	free_list(link);
}
void	init_shell()
{	
	signal(SIGINT, kill_loop);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		g_data->error = 0;
		g_data->buffer = NULL;
		g_data->link = NULL;
		g_data->in_exec = 0;
		g_data->here_doc = 0;
		g_data->buffer = readline("\e[1;32m[minishell]: \e[0m");
		if (g_data->buffer != NULL)
			prompt();
		else		
		{	
			free_all();
			write(1, "exit\n", 5);
			exit (0);
		}
		free(g_data->buffer);
		dup2(g_data->save_stdin, STDIN);
		dup2(g_data->save_stdout, STDOUT);
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
	g_data->envp = fill_env(envp);
	g_data->exitcode = 0;
	g_data->save_stdin = dup(0);
	g_data->save_stdout = dup(1);
	t_link *link;
	link = (t_link *)malloc(sizeof (t_link));
	link->next = NULL;
	g_data->link = link;
	init_shell();
}
