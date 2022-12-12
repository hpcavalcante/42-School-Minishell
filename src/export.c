/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:23:09 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/12 13:24:09 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
			ft_putstr_fd("export: `", STDERR);
			ft_putstr_fd(cmd[i], STDERR);
			ft_putstr_fd("\': not a valid identifier\n", STDERR);
			g_data->exitcode = 1;
		}
	}
}
