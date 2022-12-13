/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:03:23 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 10:22:55 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	parse_pipe(int i)
{
	t_link	*temp;
	t_link	*new;

	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	temp = g_data->link;
	if (g_data->buffer[0] == '|')
	{
		syntax_error('|');
		i = ft_strlen(g_data->buffer);
		return(i);
	}
	while (temp->next != NULL)
		temp = temp->next;
	new->cmd = ft_split(g_data->checked_line, ' ');
	free(g_data->checked_line);
	linked_list(temp, new);
	g_data->checked_line = NULL;
	i++;
	return (i);
}

int		check_syntax(char c)
{
	if (c == '&' || c == ';' || c == '\\'\
		||c == '(' || c == ')' || c == '*')
		{
			syntax_error(c);
			return (0);
		}
	return (1);
}

int	parse_quotes(int i)
{
	char	quote;

	quote = g_data->buffer[i];
	i++;
	// if (quote == '\"' && g_data->buffer[i] == '$' && (ft_isalnum(g_data->buffer[i + 1]) || g_data->buffer[i + 1] == '?'))
	// 	i = parse_variable(i);
	while (g_data->buffer[i] != quote)
	{
		g_data->checked_line = char_join(g_data->checked_line, g_data->buffer[i]);
		if (g_data->buffer[i] == ' ')
			g_data->checked_line = char_join(g_data->checked_line, 1);
		i++;
	}
	if (g_data->buffer[i] == quote)
		i++;
	return (i);
}

int	check_quotes()
{
	char	quote;
	int		i;

	i = 0;
	quote = 1;
	while (g_data->buffer[i])
	{
		if (g_data->buffer[i] == '\'' || g_data->buffer[i] == '\"')
		{
			quote = g_data->buffer[i];
			break ;
		}
		i++;
	}
	if (strchr_count(g_data->buffer, quote) % 2 != 0 && strchr_count(g_data->buffer, quote) > 0)
	{	
		write(STDERR, "error: unclosed quotes\n", 24);
		g_data->error = 1;
		g_data->exitcode = 1;
		return (0);
	}
	return (1);
}

char	*char_join(char *str1, char c)
{
	int		i;
	char	*str2;

	i = -1;
	if (c == '\0')
		return (str1);
	if (str1 == NULL)
	{
		str2 = malloc (2 * sizeof(char));
		str2[0] = c;
		str2[1] = '\0';
	}
	else
	{
		str2 = malloc ((ft_strlen(str1) + 2) * sizeof(char));
		if (str2 == NULL)
			return (NULL);
		while (str1[++i] != '\0')
			str2[i] = str1[i];
		str2[i++] = c;
		str2[i] = '\0';
	}
	free (str1);
	return (str2);
}