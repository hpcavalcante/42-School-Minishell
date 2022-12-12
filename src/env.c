/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:53:17 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/12 16:37:33 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*find_env(char *var)
{
	int		i;

	i = 0;
	while (g_data->envp[i] != NULL)
	{
		if (ft_strncmp(var, g_data->envp[i], ft_strlen(var)) == 0 \
		&& (g_data->envp[i][ft_strlen(var)] == '=' \
		|| g_data->envp[i][ft_strlen(var)] == '\0'))
		{
			if (g_data->envp[i][ft_strlen(var)] == '=')
				return (g_data->envp[i] + ft_strlen(var) + 1);
			else
				return ("\0");
		}
		i++;
	}
	return (NULL);
}

char	**get_sorted_env()
{
	int		env_size;
	char	**env;
	int		i;
	char	*temp;

	env = fill_env(g_data->envp);
	env_size = 0;
	while (env[env_size] != NULL)
		env_size++;
	while (env_size > 0)
	{
		i = 0;
		while (i < env_size - 1)
		{
			if (ft_strncmp(env[i], env[i + 1], ft_strlen(env[i])) > 0)
			{
				temp = env[i];
				env[i] = env[i + 1];
				env[i + 1] = temp;
			}
			i++;
		}
		env_size--;
	}
	return (env);
}

void	env_remove(char	*var)
{
	int		i;
	int		n;
	char	**str;
	int		size;

	i = -1;
	n = -1;
	str = NULL;
	size = 0;
	if (find_env(var) == NULL)
		return ;
	while (g_data->envp[size] != NULL)
		size++;
	str = (char **) malloc (sizeof(char *) * size);
	while (g_data->envp[++i] != NULL)
	{
		if (!(ft_strncmp(var, g_data->envp[i], ft_strlen(var)) == 0 \
			&& (g_data->envp[i][ft_strlen(var)] == '=' \
			|| g_data->envp[i][ft_strlen(var)] == '\0')))
			str[++n] = ft_strdup(g_data->envp[i]);
	}
	str[n + 1] = NULL;
	free_matrix(g_data->envp);
	g_data->envp = str;
}

char	**fill_env(char **env)
{
	char	**ret;
	int		i;
	int		n;

	i = -1;
	n = 0;
	while (env[++i] != NULL)
	{
		if (ft_strnstr(env[i], "WORKSPACE", ft_strlen(env[i])) == NULL)
			n++;
	}
	ret = (char **) malloc (sizeof(char *) * (n + 1));
	n = -1;
	i = 0;
	while (env[++n] != NULL)
	{
		if (ft_strnstr(env[n], "WORKSPACE", ft_strlen(env[n])) == NULL)
			ret[i++] = ft_strdup(env[n]);
	}
	ret[i] = NULL;
	return (ret);
}

void	env_builtin(char **cmd)
{
	int	i;

	if (cmd[1] != NULL)
	{
		write(STDERR, "env: too many arguments\n", 24);
		g_data->exitcode = 1;
		return ;
	}
	else
	{
		i = -1;
		while (g_data->envp[++i] != NULL)
		{
			if (ft_strchr(g_data->envp[i], '=') != NULL)
				printf ("%s\n", g_data->envp[i]);
		}
		g_data->exitcode = 0;
		return ;
	}
}