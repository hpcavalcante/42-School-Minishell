/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/14 12:20:05 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**space_split(char *cmd)
{
	char	**matrix;
	int		x;
	int		y;

	x = 0;
	y = 0;
	matrix = ft_split(cmd, ' ');
	while (matrix[y] != NULL)
	{
		x = 0;
		while (matrix[y][x] && matrix[y][x] != '\0')
		{
			if (matrix[y][x] == 1)
			{
				matrix[y][x] = ' ';
			}
			x++;
		}
		y++;
	}
	return (matrix);
}

int	strchr_count(char *str, int c)
{
	int	i;
	int	j;

	j = 0;
	i = ft_strlen(str);
	while (i > -1)
	{
		if (str[i] == (unsigned char)c)
			j++;
		i--;
	}
	return (j);
}

int	parse_check(t_link **new, int i)
{
	int	j;

	if (!check_syntax(g_data->buffer[i]))
		return (-1);
	if (g_data->buffer[i] == '\'' || g_data->buffer[i] == '\"')
		i = parse_quotes(i);
	else if (g_data->buffer[i] == '>' || g_data->buffer[i] == '<')
	{
		j = redirection(*new, g_data->buffer[i], g_data->buffer + i);
		if (j == -1)
			return (-1);
		i += j;
	}
	else if (g_data->buffer[i] == '$' && (ft_isalnum(g_data->buffer[i + 1]) \
	|| g_data->buffer[i + 1] == '?'))
		i = parse_variable(i);
	else if (g_data->buffer[i] == '|')
		i = parse_pipe(i);
	else
		g_data->checked_line = char_join(g_data->checked_line, \
		g_data->buffer[i++]);
	return (i);
}

int	parse_loop(t_link **new)
{
	int	i;

	i = 0;
	while (g_data->buffer[i] != '\0')
	{
		while (g_data->buffer[i] == ' ' && g_data->checked_line == NULL)
			i++;
		i = parse_check(new, i);
		if (i == -1)
			return (0);
	}
	return (1);
}

int	parse(t_link *link)
{
	t_link	*new;

	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	g_data->checked_line = NULL;
	link->cmd = NULL;
	if (!check_quotes())
	{
		free(new);
		return (0);
	}
	if (!parse_loop(&new))
	{
		free(new);
		return (0);
	}
	if (g_data->checked_line != NULL)
		new->cmd = space_split(g_data->checked_line);
	free(g_data->checked_line);
	linked_list(link, new);
	if (g_data->link->cmd == NULL)
		g_data->error = 1;
	return (1);
}
