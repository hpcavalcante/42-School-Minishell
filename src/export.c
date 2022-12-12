/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:23:09 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/12 16:47:43 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	export_add(char *var)
{
	int		size;
	int		i;
	char	**str;

	size = 0;
	i = -1;
	while (g_data->envp[size] != NULL)
		size++;
	str = (char **) malloc (sizeof(char *) * (size + 2));
	while (g_data->envp[++i] != NULL)
	{
		if (i == size - 2)
		{
			str[i] = ft_strdup(g_data->envp[i]);
			i++;
			str[i] = ft_strdup(var);
			i++;
			str[i] = ft_strdup(g_data->envp[i - 1]);
			break ;
		}
		str[i] = ft_strdup(g_data->envp[i]);
	}
	str[size + 1] = NULL;
	free_matrix (g_data->envp);
	g_data->envp = str;
}

void	export_list(void)
{
	char	**sorted_env;
	int		i;
	int		j;

	i = -1;
	sorted_env = get_sorted_env();
	while (sorted_env[++i] != NULL)
	{
		j = -1;
		if (ft_isalpha(sorted_env[i][0]))
		{
			ft_putstr_fd("declare -x ", STDOUT);
			while (sorted_env[i][++j] != '=' && sorted_env[i][j] != '\0')
				ft_putchar_fd(sorted_env[i][j], STDOUT);
			if (sorted_env[i][j] == '=')
			{
				ft_putchar_fd('=', STDOUT);
				ft_putchar_fd('\"', STDOUT);
				ft_putstr_fd(sorted_env[i] + j + 1, STDOUT);
				ft_putchar_fd('\"', STDOUT);
			}
			ft_putchar_fd('\n', STDOUT);
		}
	}
	free_matrix (sorted_env);
}

void	do_export(char	*str)
{
	int		i;
	char	*temp;

	i = 0;
	while (str[i] != '=' && str[i] != '\0')
		i++;
	temp = ft_substr(str, 0, i);
	if (ft_strchr(str, '=') != NULL && find_env(temp) != NULL)
		env_remove(temp);
	if (find_env(temp) == NULL)
		export_add(str);
	free (temp);
}

int	check_export_var(char *var)
{
	int	i;

	if (ft_isalpha(var[0]) == 0)
		return (0);
	i = -1;
	while (var[++i] != '\0' && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
	}
	return (1);
}

void	export_builtin(char **cmd)
{
	int	i;

	i = 0;
	g_data->exitcode = 0;
	if (cmd[1] == NULL)
	{
		export_list();
		return ;
	}
	while (cmd[++i] != NULL)
	{
		if (check_export_var(cmd[i]))
			do_export(cmd[i]);
		else
		{
			write(STDERR, "export: `", 9);
			write(STDERR, cmd[i], ft_strlen(cmd[i]));
			write(STDERR, "\': not a valid identifier\n", 27);
			g_data->exitcode = 1;
		}
	}
}
