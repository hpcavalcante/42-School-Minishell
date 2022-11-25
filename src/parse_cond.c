/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cond.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:09:32 by gissao-m          #+#    #+#             */
/*   Updated: 2022/11/25 16:37:20 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		redirection(t_link *new, char operator)
{
	char	*cmd;
	char	*aux;
	int		i;
	int		init_buffer;
	//buffer inicial.
	int		j;

	i = 0;
	cmd = g_data->buffer;
	while (cmd[i] == ' ' || (cmd[i] == operator && i < 2))
		i++;
	init_buffer = i;
	while (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != ' ' && cmd[i] != '|' \
	&& cmd[i] != '&' && cmd[i] != ';' && cmd[i] != '\0' && cmd[i] != '(' && cmd[i] != ')')
		i++;
	if (i == init_buffer)
	{
		redirection_error(cmd);
	}
	j = 0;
	if (cmd[j] == '>' && cmd[j + 1] == '>')
		new->append = 1;
	// else if (cmd[0] == '<' && cmd[1] == '<')
	// 	new->delimiter = 1;
	aux = ft_substr(cmd, init_buffer, i - init_buffer);
	if_is_a_directory(aux);
	if (operator == '>' || operator == '<')
		add_redirect(new, aux, operator);
	return (i);
}

void	if_is_a_directory(char *file)
{
	if (file == NULL)
		return ;
	if (check_dir(file) == 1 && g_data->error == 0)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(": Is a directory\n", STDERR);
		g_data->error = 1;
		g_data->exitcode = 1;
	}
}

int	check_dir(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	handle_output_file(t_link *link)
{
	if (link->file_out != NULL)
	{
		if(access(link->file_out, F_OK) == -1)
		{
			link->fd_out = open(link->file_out, O_CREAT | O_WRONLY | O_APPEND, 0644);
		}
		else if (access(link->file_out, F_OK) == 0 && link->append == 0)
			link->fd_out = open(link->file_out, O_WRONLY | O_TRUNC);
		else if (access(link->file_out, F_OK) == 0 && link->append == 1)
			link->fd_out = open(link->file_out, O_WRONLY | O_APPEND);
		dup2(link->fd_out, STDOUT);
		//aqui de fato estou mandando para a saida padrao.
	}
}

void	add_redirect(t_link *new, char *aux, char operator)
//tratamento para varios redirects seguidos
//ex: echo hello > a > b > c, neste caso ele criara os tres arquivos, porem so o c vai ter
//escrito o hello.
{
	dup2(g_data->save_stdin, STDIN);
	if (operator == '<')
	{
		if (new->file_in != NULL)
		{
			free (new->file_in);
			close(new->fd_in);
		}
		new->file_in = aux;
		//open_file_input(new);
	}
	if (operator == '>')
	{
		if (new->file_out != NULL)
		{
			free (new->file_out);
			close(new->fd_out);
		}
		new->file_out = aux;
		handle_output_file(new);
	}
}

void	redirection_error(char *cmd)
{
	check_signs(cmd);
	// check_syntax_red(cmd);
}

// void	check_syntax_red(char *cmd)
// {
// 	int i;

// 	i = 0;
// 	if (cmd[i] == '&' && cmd[i + 1] == '>')
// 		write_error_red_NL(cmd);
// 	else if (cmd[i] == '&' || cmd[i] == ';'|| cmd[i] == '|' || cmd[i] == '(' || cmd[i] == ')')
// 		write_error_red_1_sign(cmd);
// }

void	check_signs(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i + 5] == '<')
		write_error_red_3_signs(cmd);
	else if (cmd[i + 4] == '<')
		write_error_red_2_signs(cmd);
	else if (cmd[i + 3] == '<')
		write_error_red_1_sign(cmd);
	else if (cmd[i + 3] == '>')
		write_error_red_2_signs(cmd);
	else if (cmd[i + 2] == '>')
		write_error_red_1_sign(cmd);
	else if ((cmd[i] == '>' || cmd[i + 1] == '>') ||\
	(cmd[i] == '<' || cmd[i + 1] == '<' || cmd[i + 2] == '<'))
		write_error_red_NL(cmd);
	else if (cmd[i] == '&' && cmd[i + 1] == '>')
	{
		printf("entro aqui");
		write_error_red_NL(cmd);
	}
	else if (cmd[i] == '&' || cmd[i] == ';'|| cmd[i] == '|' || cmd[i] == '(' || cmd[i] == ')')
		write_error_red_1_sign(cmd);
}

void	write_error_red_NL()
{
	write (STDERR, ERROR_HD_NL, 46);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	write_error_red_1_sign(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	write_error_red_2_signs(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	write_error_red_3_signs(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, cmd, 1);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}
