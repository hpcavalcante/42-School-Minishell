/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 10:25:17 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_built_in(t_link *link)
{
	if (ft_str_check(link->cmd[0], "echo"))
		return (1);
	else if (ft_str_check(link->cmd[0], "pwd"))
		return (1);
	else if (ft_str_check(link->cmd[0], "export"))
		return (1);
	else if (ft_str_check(link->cmd[0], "env"))
		return (1);
	else if (ft_str_check(link->cmd[0], "exit"))
		return (1);
	else if (ft_str_check(link->cmd[0], "unset"))
		return (1);
	else if (ft_str_check(link->cmd[0], "cd"))
		return (1);
	else
		return (0);
}

char	**space_split(char *cmd)
{
    char    **matrix;
    int        x;
    int        y;

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

int		parse_loop(t_link **new)
{
	int		i;

	i = 0;
	while (g_data->buffer[i] != '\0')
	{
		while (g_data->buffer[i] == ' ' && g_data->checked_line == NULL)
			i++;
		if (!check_syntax(g_data->buffer[i]))
		 	return (0);
		if (g_data->buffer[i] == '\'' || g_data->buffer[i] == '\"')
			i = parse_quotes(i);
		else if (g_data->buffer[i] == '>')
			i += redirection(*new, '>', g_data->buffer + i);
		else if (g_data->buffer[i] == '<')
			i += redirection(*new, '<', g_data->buffer + i);
		else if (g_data->buffer[i] == '$' && (ft_isalnum(g_data->buffer[i + 1]) || g_data->buffer[i + 1] == '?'))
			i += parse_variable(i);
		else if (g_data->buffer[i] == '|')
			i = parse_pipe(i);
		else
			g_data->checked_line = char_join(g_data->checked_line, g_data->buffer[i++]);
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
		return (0);
	if (!parse_loop(&new))
		return (0);
	if (g_data->checked_line != NULL)
		new->cmd = space_split(g_data->checked_line);
	free(g_data->checked_line);
	linked_list(link, new);
	if (g_data->link->cmd == NULL)
		g_data->error = 1;
	return (1);
}
