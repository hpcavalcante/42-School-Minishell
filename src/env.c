/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 15:53:17 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/12 13:56:30 by hepiment         ###   ########.fr       */
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