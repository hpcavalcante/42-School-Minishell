/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:15:48 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/20 15:38:41 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL
# define MINI_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>

# define clear() printf("\033[H\033[J")

typedef struct s_data
{
	char **envp;
	char *buffer;
	
} t_data;

extern t_data *g_data;
#endif