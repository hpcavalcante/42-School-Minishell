/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:07:47 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/14 16:10:19 by gissao-m         ###   ########.fr       */
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
	if (ft_strnstr(g_data->buffer, "/", ft_strlen(g_data->buffer)))
	{
		write(STDERR, ": Not a directory\n", 18);
		close (list->pipe_fd[1]);
		free_all();
		exit(126);
	}
	write (STDERR, list->cmd[0], ft_strlen(list->cmd[0]));
	write (STDERR, ": command not found\n", 20);
	close (list->pipe_fd[1]);
	free_all();
	exit(127);
	return (NULL);
}

char	*matrix_join(t_link	*link, char **matrix, int count)
{
	char	*path;
	char	*temp;

	if (access(link->cmd[0], F_OK | X_OK) == 0)
	{
		free_matrix(matrix);
		return (link->cmd[0]);
	}
	temp = ft_strjoin(matrix[count], "/");
	path = ft_strjoin(temp, link->cmd[0]);
	free (temp);
	if (access(path, F_OK | X_OK) == 0)
	{
		free_matrix(matrix);
		return (path);
	}
	free (path);
	return (NULL);
}

char	*get_path(t_link *link, char **path_env)
{
	int		count;
	char	**matrix;
	char	*aux;

	if (find_env("PATH") == NULL)
		exit_error_path(NULL, link);
	matrix = find_path_env(path_env);
	count = -1;
	while (matrix[++count] != NULL)
	{
		aux = matrix_join(link, matrix, count);
		if (aux != NULL)
			return (aux);
	}
	return (exit_error_path(matrix, link));
}
