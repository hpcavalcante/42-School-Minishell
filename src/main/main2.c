/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:46:55 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/25 17:41:58 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *g_data;

void	kill_loop(int signal)
{
	(void) signal;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
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

void	command()
{
	if (ft_str_check(g_data->buffer, "exit"))
	{
		g_data->exitcode = 1;
		exit(g_data->exitcode);
	}
	execve(g_data->path, g_data->cmd, g_data->envp);
}

void	init_shell()
{	
	clear();
	signal(SIGINT, kill_loop);
	while (1)
	{
		g_data->buffer = readline("\e[1;32mminishell: \e[0m");
		if (g_data->buffer)
		{
			add_history(g_data->buffer);
			parse();
		}
		else if (g_data->buffer == NULL)
		{	
			write(1, "exit\n", 6);
			exit (0);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
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
	init_shell();
}