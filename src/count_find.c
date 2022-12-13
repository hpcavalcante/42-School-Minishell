/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_find.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:57:29 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/13 15:00:05 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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
