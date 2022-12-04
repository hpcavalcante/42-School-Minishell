/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:02:50 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/04 17:12:21 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	parent_process(t_link *link)
{
	int	wstatus;

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

void	exec_builtin(t_link *link)
{
	if (link->file_out == NULL && link->next != NULL)
		dup2(link->pipe_fd[1], STDOUT);
	if (ft_str_check(link->cmd[0], "echo"))
		echo_builtin(link->cmd);
	else if (ft_str_check(link->cmd[0], "pwd"))
		pwd_builtin();
	else if (ft_str_check(link->cmd[0], "exit"))
		exit_builtin();
	dup2(link->pipe_fd[0], STDIN);
	dup2(g_data->save_stdout, STDOUT);
	close(link->pipe_fd[0]);
	close(link->pipe_fd[1]);
}


void	process(t_link *link)
{
	
	// close(g_data->fd_pipe[0]);
	// dup2(g_data->fd_pipe, );
	g_data->in_exec = 1;
	if (pipe(link->pipe_fd) == -1)
		exit (-1);
	if (check_built_in(link))
		exec_builtin(link);
	else
	{
		g_data->pid = fork();
		if (g_data->pid == 0)
		{
			g_data->link->path = get_path(link, g_data->envp);
			child_process();
		}
		parent_process(link);
	}
}

void	syntax_error(char c)
{
	ft_putstr_fd(SYNTAX_ERROR, STDERR);
	ft_putchar_fd(c, STDERR);
	write(STDERR,"'\n", 3);
	g_data->exitcode = STDERR;
	g_data->error = STDOUT;
}

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
	linked_list(temp, new);
	new = (t_link *) malloc (sizeof(t_link));
	init_linked_list(new);
	g_data->checked_line = NULL;
	i++;
	return (i);
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

int	check_quotes()
{
	if (strchr_count(g_data->buffer, '\'') % 2 != 0 || strchr_count(g_data->buffer, '\"') % 2 != 0)
	{	
		write(STDERR, "error: unclosed quotes\n", 24);
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
			printf("foi aqui\n");
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

int		parse_loop(t_link *new)
{
	int		i;

	i = 0;
	while (g_data->buffer[i] != '\0')
	{
		while (g_data->buffer[i] == ' ' && g_data->checked_line == NULL)
			i++;
		if (g_data->buffer[i] == '\'' || g_data->buffer[i] == '\"')
			i = parse_quotes(i);
		if (!check_syntax(g_data->buffer[i]))
		 	return (0);
		if (g_data->buffer[i] == '>')
		{
			printf("buffer: %s\n", g_data->buffer);
			i = redirection(new, '>', g_data->buffer + i);
			return(0);			
		}
		else if (g_data->buffer[i] == '<')
		{
			i = redirection(new, '<', g_data->buffer + i);
			return (0);
		}
		// printf("redirect: %d\n", redirection(link));
		if (g_data->buffer[i] == '|')
			i = parse_pipe(i);
		else
			g_data->checked_line = char_join(g_data->checked_line, g_data->buffer[i++]);
	}
	if (g_data->checked_line != NULL)
		command(g_data->checked_line);
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
	if (!parse_loop(new))
		return (0);
	return (1);
}

void	linked_list(t_link *link, t_link *new)
{
	if (link->cmd == NULL)
	{
		link->append = new->append;
		link->file_out = new->file_out;
		link->fd_out = new->fd_out;
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
	new->file_out = NULL;
	new->append = 0;
	new->fd_out = 0;
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
