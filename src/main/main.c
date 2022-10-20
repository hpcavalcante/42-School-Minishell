/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/19 14:30:49 by gissao-m          #+#    #+#             */
/*   Updated: 2022/10/19 17:17:18 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/types.h>
#include </usr/include/readline/readline.h>

// void	fazer_prompt(int signal)
// {
// 	(void) signal;
// 	printf("HG\n");
// 	rl_replace_line("", 0);
// 	rl_on_new_line();
// 	rl_redisplay();
// }

// int main(int argc,char **argv, char **envp)
// {
// 	signal(SIGINT, fazer_prompt);
// 	return (0);
// }


int main()
{
    printf( "%s\n", readline( "test> " ) );
    return 0;
}