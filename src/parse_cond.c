/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cond.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:09:32 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/14 12:10:35 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	checking_directory(char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (0);
	return (S_ISDIR(statbuf.st_mode));
}

void	if_is_a_directory(char *file)
{
	if (file == NULL)
		return ;
	if (checking_directory(file) == 1 && g_data->error == 0)
	{
		ft_putstr_fd(file, STDERR);
		ft_putstr_fd(IS_DIR, STDERR);
		g_data->exitcode = 1;
		g_data->error = 1;
	}
}

void	adding_redirect(t_link *new, char *aux, char operator)
{
	dup2(g_data->save_stdin, STDIN);
	if (operator == '<')
	{
		if (new->file_in)
		{
			free (new->file_in);
			close(new->fd_in);
		}
		new->file_in = aux;
		handle_input_file(new);
	}
	if (operator == '>')
	{
		if (new->file_out)
		{
			free (new->file_out);
			close(new->fd_out);
		}
		new->file_out = aux;
		handle_output_file(new);
	}
}

int	redirection(t_link *new, char operator, char *buffer)
{
	char	*aux;
	int		i;
	int		init_buffer;

	i = 0;
	while (buffer[i] == ' ' || (buffer[i] == operator && i < 2))
		i++;
	init_buffer = i;
	while (buffer[i] != '<' && buffer[i] != '>' && buffer[i] != ' ' && \
	buffer[i] != '|' && buffer[i] != '&' && buffer[i] != ';' && buffer[i] \
	!= '\0' && buffer[i] != '(' && buffer[i] != ')')
		i++;
	if (i == init_buffer)
	{
		redirection_error(buffer);
		return (-1);
	}
	check_operator(new, '>', buffer);
	check_operator2(new, '<', buffer);
	aux = ft_substr(buffer, init_buffer, i - init_buffer);
	if_is_a_directory(aux);
	if (operator == '>' || operator == '<')
		adding_redirect(new, aux, operator);
	return (i);
}

int	parse_variable(int i)
{
	char	*var;
	int		temp;

	if (g_data->buffer[i + 1] == '?')
	{
		var = ft_itoa(g_data->exitcode);
		g_data->checked_line = ft_my_strjoin(g_data->checked_line, var);
		free (var);
		return (i + 2);
	}
	if (ft_isdigit(g_data->buffer[i + 1]))
		return (i + 2);
	i++;
	temp = i;
	while (ft_isalnum(g_data->buffer[i]))
		i++;
	var = ft_substr(g_data->buffer, temp, i - temp);
	if (var != NULL)
	{
		if (find_env(var) != NULL && find_env(var)[0] != '\0')
			g_data->checked_line = ft_my_strjoin(g_data->checked_line, \
			find_env(var));
		free (var);
	}
	return (i);
}
