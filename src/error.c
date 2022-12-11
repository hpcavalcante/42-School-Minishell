/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/11 20:13:26 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/11 20:13:45 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	syntax_error(char c)
{
	ft_putstr_fd(SYNTAX_ERROR, STDERR);
	ft_putchar_fd(c, STDERR);
	write(STDERR,"'\n", 3);
	g_data->exitcode = STDERR;
	g_data->error = STDOUT;
}