/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 17:03:23 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/24 17:19:52 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**find_env(char **path_env)
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

char	*get_path(char **path_env)
{
	int		count;
	char	*path;
	char	**matrix;
	char	*temp;

	matrix = find_env(path_env);
	count = 0;
	while (matrix[count] != 0)
	{
		temp = ft_strjoin(matrix[count], "/");
		path = ft_strjoin(temp, g_data->cmd[0]);
		free (temp);
		if (access(path, F_OK | X_OK) == 0)
		{
			return (path);
		}
		free (path);
		count++;
	}
	exit (127);
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
