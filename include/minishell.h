/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:15:48 by hepiment          #+#    #+#             */
/*   Updated: 2022/11/22 16:05:00 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL
# define MINI_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../libft/libft.h"

# define STDERR 2
# define STDOUT 1
# define SYNTAX_ERROR "syntax error near unexpected token `"
# define ERROR_HD_NL "syntax error near unexpected token `newline'\n"

typedef struct s_link
{
	char			**cmd;
	char			*file_in;
	char			*created_file;
	int				fd_out;
	int				fd_in;
	char			*path;
	int				pipe_fd[2];
	int				delimiter;
	int				append;
	struct s_link	*next;
}	t_link;

typedef struct s_data
{
	int		exitcode;
	int		pid;
	int		here_doc;
	int		in_exec;
	int		error;
	int		save_stdin;
	int		save_stdout;
	char	*checked_line;
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
int		parse();
void	command(char *checked_line);
char	**space_split(char *cmd);
void	child_process();
void	kill_loop(int signal);
void	exit_code(int signal);
void	linked_list(t_link *link, t_link *new);
void	init_linked_list(t_link *new);
char	*char_join(char *str1, char c);
int		ft_str_check(const char *s1, const char *s2);
int		redirection(t_link *new, char operator);
void	redirection_error(char *cmd);
void	check_syntax_red(char *cmd);
void	check_signs(char *cmd);
void	handle_output_file(t_link *link);
void	write_error_red_NL(char *cmd);
void	write_error_red_1_sign(char *cmd);
void	write_error_red_2_signs(char *cmd);
void	write_error_red_3_signs(char *cmd);

extern t_data *g_data;
#endif