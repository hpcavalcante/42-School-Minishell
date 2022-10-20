/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:46:55 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/20 12:54:15 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

#define clear() printf("\033[H\033[J")

void	prompt(int signal)
{
	(void) signal;
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	parse(char *str)
{
	if (strcmp(str, "exit") == 0)	
	{	
		
		exit(0);
	}
}

void	init_shell(char *str)
{
	char	*buffer;
	
	signal(SIGINT, prompt);
	while (1)
	{
		buffer = readline("\e[1;34mminishell: \e[0m");
		if (strlen(buffer) != 0)
		{
			add_history(buffer);
			strcpy(str, buffer);
			parse(str);
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	input[1000];

	clear();
	init_shell(input);
}