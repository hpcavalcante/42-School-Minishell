/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/11/07 19:47:09 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
void	parent_command(t_link *list)
{
	int	status;

	close(list->pipe_fd[1]);
	if (list->next != NULL)
	{
		dup2(list->pipe_fd[0], 0);
		waitpid(g_data->pid, &status, 0);
		g_data->exitcode = WEXITSTATUS(status);
	}
	else
	{
		waitpid(g_data->pid, &status, 0);
		g_data->exitcode = WEXITSTATUS(status);
	}
	close (list->pipe_fd[0]);
}

void	process(t_link *link)
{
	
	// close(g_data->fd_pipe[0]);
	// dup2(g_data->fd_pipe, );
	if (pipe(link->pipe_fd) == -1)
		exit (-1);
	g_data->pid = fork();
	if (g_data->pid == 0)
	{
		g_data->link->path = get_path(link, g_data->envp);
		command();
	}
	parent_command(link);
}

void	parse_loop(char **checked_line)
{
	int	i;
	t_link	*temp;
	t_link	*new;

	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	i = 0;
	temp = g_data->link;
	while (g_data->buffer[i] != '\0')
	{
		while (g_data->buffer[i] == ' ' && *checked_line == NULL)
			i++;
		// if (g_data->buffer[i] == '&' || g_data->buffer[i] == ';' || g_data->buffer[i] == '\\'\
		// ||g_data->buffer[i] == '(' || g_data->buffer[i] == ')' || g_data->buffer[i] == '*')
		// 	syntax_error(g_data->link->cmd + i);
		if (g_data->buffer[i] == '|')
		{
			while (temp->next != NULL)
				temp = temp->next;
			new->cmd = ft_split(*checked_line, ' ');
			linked_list(temp, new);
			new = (t_link *) malloc (sizeof(t_link));
			init_linked_list(new);
			*checked_line = NULL;
			i++;
		}
		
		else if (g_data->buffer[i] != '\0')
			*checked_line = char_join(*checked_line, g_data->buffer[i++]);
	}
		if (*checked_line != NULL)
		{
			while (temp->next != NULL)
				temp = temp->next;
			new->cmd = ft_split(*checked_line, ' ');
			linked_list(temp, new);
			new = (t_link *) malloc (sizeof(t_link));
			init_linked_list(new);
			*checked_line = NULL;
			temp = g_data->link;
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
	//printf("%s %s\n%s %s\n%s %s\n", g_data->link->cmd[0], g_data->link->cmd[1], g_data->link->next->cmd[0], g_data->link->next->cmd[1], g_data->link->next->next->cmd[0], g_data->link->next->next->cmd[1]);
	
	// process(link);
	// if (checked_line != NULL)
	// 	new->cmd = get_cmd(checked_line);
	// free (checked_line);
	// linked_list(link, new);
	// if (link->cmd == NULL)
	// 	g_data->error = 1;
}

void	linked_list(t_link *link, t_link *new)
{
	if (link->cmd == NULL)
	{
		link->cmd = new->cmd;
		// link->next = new->next;
		link->path = new->path;
		link->next = NULL;
		//o ultimo elemnto da lista linkada precisa ser nulo!!
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
