/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:46:55 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/20 13:42:33 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *g_data;

void	prompt(int signal)
{
	(void) signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	parse(char *str)
{
	if (strcmp(str, "exit") == 0)	
	{	
		free(g_data->buffer);
		exit(0);
	}
}

void	init_shell()
{	
	signal(SIGINT, prompt);
	while (1)
	{
		g_data->buffer = readline("\e[1;32mminishell: \e[0m");
		if (strlen(g_data->buffer) != 0)
		{
			add_history(g_data->buffer);
			parse(g_data->buffer);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		printf("Tá malucão?\n");
		exit(1);
	}
	g_data = malloc(sizeof(t_data));
	g_data->buffer = NULL;
	clear();
	init_shell();
}