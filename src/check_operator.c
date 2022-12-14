/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_operator.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 22:23:25 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/13 22:24:12 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_operator(t_link *new, char c, char *buffer)
{
	int	j;

	j = 0;
	c = '>';
	if (buffer[j] == c && buffer[j + 1] == c)
		new->append = 1;
}

void	check_operator2(t_link *new, char c, char *buffer)
{
	int	j;

	j = 0;
	c = '<';
	if (buffer[j] == c && buffer[j + 1] == c)
		new->delimiter = 1;
}
