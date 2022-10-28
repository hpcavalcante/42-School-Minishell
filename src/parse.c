/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/28 14:04:11 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	process(t_link *link)
{
	g_data->pid = fork();
	
	// close(g_data->fd_pipe[0]);
	// dup2(g_data->fd_pipe, );
	if (g_data->pid == 0)
	{
		g_data->link->path = get_path(link, g_data->envp);
		command();
	}
	waitpid(g_data->pid, NULL, 0);
	command();
}

void	parse_loop(char **checked_line)
{
	int	i;
	
	i = 0;
	while (g_data->buffer[i] != '\0')
	{
		while (g_data->buffer[i] == ' ' && *checked_line == NULL)
			i++;
		// if (g_data->buffer[i] == '&' || g_data->buffer[i] == ';' || g_data->buffer[i] == '\\'\
		// ||g_data->buffer[i] == '(' || g_data->buffer[i] == ')' || g_data->buffer[i] == '*')
		// 	syntax_error(g_data->link->cmd + i);
		// if (g_data->buffer[i] == '|')
		// 	i += pipe_split(); 
		if (g_data->buffer[i] != '\0')
			*checked_line = char_join(*checked_line, g_data->buffer[i++]);
	}
}

void	parse(t_link *link)
{
	char	*checked_line;
	t_link	*new;

	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	checked_line = NULL;
	parse_loop(&checked_line);
	process(link);
	if (checked_line != NULL)
		new->cmd = get_cmd(checked_line);
	free (checked_line);
	linked_list(link, new);
	if (link->cmd == NULL)
		g_data->error = 1;
}

void	linked_list(t_link *link, t_link *new)
{
	if (link->cmd == NULL)
	{
		link->cmd = new->cmd;
		link->next = new->next;
		link->path = new->path;
		link->next = NULL;
		free (new);
	}
	else
	{
		while (link->next != NULL)
			link = link->next;
		link->next = new;
	}
}

void	init_linked_list(t_link *new)
{
	new->cmd = NULL;
	new->next = NULL;
	new->path = NULL;
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
