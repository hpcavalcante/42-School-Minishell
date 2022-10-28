/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:46:55 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/28 14:25:08 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_data *g_data;

void	kill_loop(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_data->exitcode = 130;
	//fazer tratamentos para outros exits
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

void	command()
{
	if (ft_str_check(g_data->buffer, "exit"))
	{
		g_data->exitcode = 1;
		exit(g_data->exitcode);
	}
	if (g_data->link->cmd == NULL)
		printf("DEURUIM\n");
	else
		for (int i = 0; g_data->link->cmd[i]; i++)
			printf("CMD: %s\n", g_data->link->cmd[i]);
	execve(g_data->link->path, g_data->link->cmd, g_data->envp);
}

void	init_shell()
{	
	clear();
	signal(SIGINT, kill_loop);
	while (1)
	{
		signal(SIGQUIT, SIG_IGN);
		g_data->buffer = readline("\e[1;32m[minishell]: \e[0m");
		if (g_data->buffer)
		{
			add_history(g_data->buffer);
			parse(g_data->link);
			process(g_data->link);
			g_data->link = g_data->link->next;
		}
		else if (g_data->buffer == NULL)
		{	
			write(1, "exit\n", 6);
			exit (0);
		}
		// while (g_data->link != NULL)
		// {
		// 	if (g_data->link->cmd != NULL)
		// 		command();
		// 	g_data->link = g_data->link->next;
		// }
	//free_list(g_data->link);
	}
}


int	main(int argc, char **argv, char **envp)
{ 
	(void) argv;
	if (argc != 1)
	{
		printf("Invalid argument\n");
		exit(0);
	}
	g_data = malloc(sizeof(t_data));
	g_data->buffer = NULL;
	g_data->envp = envp;
	g_data->save_stdin = STDIN_FILENO;
	g_data->save_stdout = STDOUT_FILENO;
	t_link *link;
	link = (t_link *)malloc(sizeof (t_link));
	g_data->link = link;
	link->cmd == NULL;
	link->path == NULL;
	init_shell();
}

//fazer  splits de acordo com o numero de pipes + 1, por isso ele usa lista encadeada porque em cada no vai ter uma variavel.