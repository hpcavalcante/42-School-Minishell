/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 09:46:55 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/21 17:19:40 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_data *g_data;

void	kill_loop(int signal)
{
	(void) signal;
	printf("\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	g_data->exitcode = 130;
}

int	ft_str_check(const char *s1, const char *s2)
{
	int	a;

	a = 0;
	while (s1[a] == s2[a] && s1[a] != '\0')
		a++;
	if (s1[a] == '\n' && s2[a] == '\0')
		return (1);
	else if (s1[a] == s2[a])
		return (1);
	else
		return (0);
}

void	parse()
{
	if (ft_str_check(g_data->buffer, "exit"))
		exit(0);
	execve(g_data->path, g_data->cmd, g_data->envp);
}

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



void	command()
{
	g_data->pid = fork();
	if (g_data->pid == 0)
	{	
		g_data->cmd = get_cmd(g_data->buffer);
		g_data->path = get_path(g_data->envp);
		parse();
	}
	waitpid(g_data->pid, NULL, 0);
	parse();
}

void	init_shell()
{	
	clear();
	signal(SIGINT, kill_loop);
	g_data->pid = getpid();
	while (1)
	{
		g_data->buffer = readline("\e[1;32mminishell: \e[0m");
		if (g_data->buffer)
		{
			add_history(g_data->buffer);
			command();
		}
	}
}

int	main(int argc, char **argv, char **envp)
{
	if (argc != 1)
	{
		printf("Invalid argument\n");
		exit(0);
	}
	g_data = malloc(sizeof(t_data));
	g_data->buffer = NULL;
	g_data->envp = envp;
	init_shell();
}