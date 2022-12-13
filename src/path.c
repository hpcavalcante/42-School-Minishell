/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:07:47 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 16:46:18 by hepiment         ###   ########.fr       */
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
	if (count == 0 && (ft_strncmp(path_env[count], "PATH=", 5) == 0))
		return (NULL);
	row = path_env[count] + 5;
	matrix = ft_split(row, ':');
	return (matrix);
}

char	*exit_error_path(char **path, t_link *list)
{
	if (path != NULL)
		free_matrix(path);
	write (STDERR, list->cmd[0], ft_strlen(list->cmd[0]));
	write (STDERR, ": command not found\n", 20);
	close (list->pipe_fd[1]);
	free_all();
	exit(127);
	return (NULL);
}

char	*get_path(t_link *link, char **path_env)
{
	int		count;
	char	*path;
	char	**matrix;
	char	*temp;

	if (find_env("PATH") == NULL)
		exit_error_path(NULL, link);
	matrix = find_path_env(path_env);
	count = -1;
	while (matrix[++count] != NULL)
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
	}
	return (exit_error_path(matrix, link));
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
