/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:30:49 by gissao-m          #+#    #+#             */
/*   Updated: 2022/10/20 11:24:55 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fazer_prompt(int signal)
{
	(void) signal;
	printf("HG\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

int main(int argc,char **argv, char **envp)
{
	if (argc != 1)
	{
		perror("Error");
		exit(1);
		//termino do programa com algum erro.
	}
	
	signal(SIGINT, fazer_prompt);
	return (0);
}


int main()
{
	printf( "%s\n", readline( "test> " ) );
	return 0;
}