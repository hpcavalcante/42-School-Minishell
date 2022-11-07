/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:15:48 by hepiment          #+#    #+#             */
/*   Updated: 2022/11/07 19:30:01 by gissao-m         ###   ########.fr       */
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
# define STDERR 2

typedef struct s_link
{
	char			**cmd;
	char			*path;
	int				pipe_fd[2];
	struct s_link	*next;
}	t_link;

typedef struct s_data
{
	int		exitcode;
	int		pid;
	int		error;
	int		save_stdin;
	int		save_stdout;
	char 	**envp;
	char 	*buffer;
	t_link	*link;
} t_data;


char	*get_path(t_link *link, char **path_env);
char	**find_env(char **path_env);
int		count_find(char *str_cmd);
char	**matrix_cmd(char *cmd);
char	**get_cmd(char *cmd);
void	process(t_link *link);
void	parse();
void	command();
void	kill_loop(int signal);
void	exit_code(int signal);
void	tokenizer();
void	linked_list(t_link *link, t_link *new);
void	init_linked_list(t_link *new);
char	*char_join(char *str1, char c);

extern t_data *g_data;
#endif