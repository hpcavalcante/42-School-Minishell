/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_in.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 21:07:25 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/13 21:08:16 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	check_built_in(t_link *link)
{
	if (ft_str_check(link->cmd[0], "echo"))
		return (1);
	else if (ft_str_check(link->cmd[0], "pwd"))
		return (1);
	else if (ft_str_check(link->cmd[0], "export"))
		return (1);
	else if (ft_str_check(link->cmd[0], "env"))
		return (1);
	else if (ft_str_check(link->cmd[0], "exit"))
		return (1);
	else if (ft_str_check(link->cmd[0], "unset"))
		return (1);
	else if (ft_str_check(link->cmd[0], "cd"))
		return (1);
	else
		return (0);
}
