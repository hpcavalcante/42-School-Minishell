/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:56:46 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/14 17:18:10 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_error_red_1_sign(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	write_error_red_nl(void)
{
	write (STDERR, ERROR_HD_NL, 46);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	redirection_error(char *cmd)
{
	char	aux;

	if (cmd[0] != '\0')
	{
		aux = cmd[0];
		if (aux == '&' || aux == ';' || aux == '|' \
		|| aux == '(' || aux == ')')
			write_error_red_1_sign(cmd);
		else if (aux == '>' || aux == '<')
			write_error_red_nl();
	}
}
