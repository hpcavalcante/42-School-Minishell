/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 16:41:28 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 21:13:45 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	check_unset_var(char *var)
{
	int	i;

	if (ft_isalpha(var[0]) == 0)
		return (0);
	i = 0;
	while (var[++i] != '\0')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (0);
	}
	return (1);
}

void	unset_builtin(char **cmd)
{
	int	i;

	i = 0;
	g_data->exitcode = 0;
	if (cmd[1] == NULL)
		return ;
	while (cmd[++i] != NULL)
	{
		if (check_unset_var(cmd[i]))
			env_remove(cmd[i]);
		else
		{
			write(STDERR, "unset: `", 8);
			write(STDERR, cmd[i], ft_strlen(cmd[i]));
			write(STDERR, "\': not a valid identifier\n", 27);
			g_data->exitcode = 1;
		}
	}
}
