/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 11:15:48 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/11 20:50:33 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_SHELL
# define MINI_SHELL

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include "../libft/libft.h"

# define STDERR 2
# define STDOUT 1
# define STDIN 0
# define SYNTAX_ERROR "syntax error near unexpected token `"
# define ERROR_HD_NL "syntax error near unexpected token `newline'\n"
# define IS_DIR ": Is a directory\n"

typedef struct s_link
{
	char			**cmd;
	char			*file_in;
	char			*file_out;
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
	int		exec_pid;
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
int		redirection(t_link *new, char operator, char *cmd);
void	redirection_error(char *cmd);
void	check_syntax_red(char *cmd);
void	check_signs(char *cmd);
void	adding_redirect(t_link *new, char *aux, char operator);
void	handle_output_file(t_link *link);
void	write_error_red_NL();
void	write_error_red_1_sign(char *cmd);
void	write_error_red_2_signs(char *cmd);
void	write_error_red_3_signs(char *cmd);
void	if_is_a_directory(char *file);
void	pwd_builtin();
void	exit_builtin(t_link *link);
void	echo_builtin(char **cmd);
void	exec_builtin(t_link *link);
int		check_dir(char *path);
int		checking_directory(char *path);
void	free_matrix(char **s);
void	free_all();
void	handle_input_file(t_link *link);
int		check_syntax(char c);
int		parse_pipe(int i);
int		parse_quotes(int i);
int		check_quotes();
int		strchr_count(char *str, int c);
void	syntax_error(char c);
void	child_process();
void	parent_process(t_link *link);
int		check_built_in(t_link *link);
void	free_list(t_link *link);

extern t_data *g_data;
#endif