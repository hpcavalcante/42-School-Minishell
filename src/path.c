/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:07:47 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 07:48:59 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	**find_path_env(char **path_env)
{
	int		count;
	char	**matrix;
	char	*row;

	count = 0;
	while (ft_strncmp(path_env[count], "PATH=", 5))
		count++;
	row = path_env[count] + 5;
	matrix = ft_split(row, ':');
	return (matrix);
}

void	exit_error_path(char **path, t_link *list)
{
	if (path != NULL)
		free_matrix(path);
	write (STDERR, list->cmd[0], ft_strlen(list->cmd[0]));
	write (STDERR, ": command not found\n", 20);
	close (list->pipe_fd[1]);
	free_all();
	exit (127);
}

char	*get_path(t_link *link, char **path_env)
{
	int		count;
	char	*path;
	char	**matrix;
	char	*temp;

	matrix = find_path_env(path_env);
	count = 0;
	while (matrix[count] != 0)
	{
		if (access(link->cmd[0], F_OK | X_OK) == 0)
			return (link->cmd[0]);
		temp = ft_strjoin(matrix[count], "/");
		path = ft_strjoin(temp, link->cmd[0]);
		free (temp);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_matrix(matrix);
			return (path);
		}
		free (path);
		count++;
	}
	exit_error_path(matrix, link);
	exit (130);
}

int	count_find(char *str_cmd)
{
	int		count;
	int		find;

	count = 0;
	find = 0;
	while (str_cmd[count] == ' ')
		count++;
	while (count < ft_strlen(str_cmd))
	{
		if (str_cmd[count] == '\'')
			find++;
		count++;
	}
	return (find);
}

char	**matrix_cmd(char *cmd)
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
		while (matrix[y][x] && matrix[y][x] != '\'')
			x++;
		if (matrix[y][x] && matrix[y][x + 1])
			x++;
		while (matrix[y][x] && matrix[y][x] != '\'')
		{
			if (matrix[y][x] == 1)
				matrix[y][x] = ' ';
			x++;
		}
		y++;
	}
	return (matrix);
}

char	**get_cmd(char *cmd)
{
	char	**matrix;
	int		count;

	count = 0;
	if (count_find(cmd) % 2 != 0)
		write(2, "Error:", 7);
	else
	{
		while (cmd[count] && cmd[count] != '\'')
			count++;
		if (cmd[count] == '\'' && cmd[count + 1])
			count++;
		while (cmd[count] && cmd[count] != '\'')
		{
			if (cmd[count] == ' ')
				cmd[count] = 1;
			count++;
		}
	}
	matrix = matrix_cmd(cmd);
	return (matrix);
}
