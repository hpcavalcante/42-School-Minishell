/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/11/12 23:09:29 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parent_process(t_link *link)
{
	int	wstatus;

	if (ft_str_check(g_data->buffer, "exit"))
	{
		g_data->exitcode = 1;
		exit(g_data->exitcode);
	}
	close(link->pipe_fd[1]);
	if (link->next != NULL)
	{
		dup2(link->pipe_fd[0], 0);
		waitpid(g_data->pid, &wstatus, 0);
		g_data->exitcode = WEXITSTATUS(wstatus);
	}
	else
	{
		waitpid(g_data->pid, &wstatus, 0);
		g_data->exitcode = WEXITSTATUS(wstatus);
	}
	close (link->pipe_fd[0]);
}

void	process(t_link *link)
{
	
	// close(g_data->fd_pipe[0]);
	// dup2(g_data->fd_pipe, );
	g_data->in_exec = 1;
	if (pipe(link->pipe_fd) == -1)
		exit (-1);
	g_data->pid = fork();
	if (g_data->pid == 0)
	{
		g_data->link->path = get_path(link, g_data->envp);
		child_process();
	}
	parent_process(link);
}

void	syntax_error(char c)
{
	// char	temp;

	// temp = str[0];
	ft_putstr_fd(SYNTAX_ERROR, STDERR);
	ft_putchar_fd(c, STDERR);
	write(STDERR,"'\n", 3);
	g_data->exitcode = STDERR;
	g_data->error = STDOUT;
}

void	parse_pipe(char **checked_line)
{
	t_link	*temp;
	t_link	*new;

	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	temp = g_data->link;
	if (g_data->buffer[0] == '|')
	{
		syntax_error(0);
		return ;
	}
	while (temp->next != NULL)
		temp = temp->next;
	//printf("LINE 0: %s\n", *checked_line);
	new->cmd = ft_split(*checked_line, ' ');
	linked_list(temp, new);
	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
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

int	check_quotes(char *str)
{
	if (strchr_count(g_data->buffer, '\'') % 2 != 0 || strchr_count(g_data->buffer, '\"') % 2 != 0)
	{	
		write(STDERR, "Error: unclosed quotes\n", 24);
		g_data->error = 1;
		g_data->exitcode = 1;
		return (0);
	}
	return (1);
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

int		parse_loop(char **checked_line)
{
	int	i;
	char	quote;

	i = 0;
	while (g_data->buffer[i] != '\0')
	{
		while (g_data->buffer[i] == ' ' && *checked_line == NULL)
			i++;
		if (g_data->buffer[i] == '\'' || g_data->buffer[i] == '\"')
		{
			quote = g_data->buffer[i];
			i++;
			while (g_data->buffer[i] != quote)
			{
				*checked_line = char_join(*checked_line, g_data->buffer[i]);
				if (g_data->buffer[i] == ' ')
					*checked_line = char_join(*checked_line, 1);
				i++;
			}
			if (g_data->buffer[i] == quote)
				i++;
			if (g_data->buffer[i] == '\0')
				break;
		}
		if (!check_syntax(g_data->buffer[i]))
		 	return (0);
		if (g_data->buffer[i] == '|')
		{
			parse_pipe(checked_line);
			*checked_line = NULL;
			i++;
		}
		else
			*checked_line = char_join(*checked_line, g_data->buffer[i++]);
	}
	if (*checked_line != NULL)
		command(*checked_line);
	return (1);
}

int	parse(t_link *link)
{
	char	*checked_line;
	t_link	*new;

	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	checked_line = NULL;
	if (!check_quotes(g_data->buffer))
		return (0);
	if (!parse_loop(&checked_line))
		return (0);
	return (1);
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
