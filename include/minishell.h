/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:15:48 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/24 17:31:30 by hepiment         ###   ########.fr       */
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
#include <sys/wait.h>
#include <sys/types.h>
#include "../libft/libft.h"

# define clear() printf("\033[H\033[J")

typedef struct s_data
{
	int		exitcode;
	int		pid;
	int		save_stdin;
	int		save_stdout;
	char	**cmd;
	char	*path;
	char 	**envp;
	char 	*buffer;	
} t_data;

char	*get_path(char **path_env);
char	**find_env(char **path_env);
int		count_find(char *str_cmd);
char	**matrix_cmd(char *cmd);
char	**get_cmd(char *cmd);
void	parse();
void	command();
void	kill_loop(int signal);
void	exit_code(int signal);

extern t_data *g_data;
#endif