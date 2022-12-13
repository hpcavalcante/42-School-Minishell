/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   red_error.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/01 18:56:46 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/13 13:46:04 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	write_error_red_3_signs(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, cmd, 1);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	write_error_red_2_signs(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	write_error_red_1_sign(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	write_error_red_NL()
{
	write (STDERR, ERROR_HD_NL, 46);
	g_data->error = 1;
	g_data->exitcode = 2;
}

void	redirection_error(char *cmd)
{
	int	i;

	i = 0;
	if (cmd[i + 5] == '<')
		write_error_red_3_signs(cmd);
	else if (cmd[i + 4] == '<')
		write_error_red_2_signs(cmd);
	else if (cmd[i + 3] == '<')
		write_error_red_1_sign(cmd);
	else if (cmd[i + 3] == '>')
	{
		write_error_red_2_signs(cmd);
		printf("gsilva\n");

	}
	else if (cmd[i + 2] == '>')
	{
		write_error_red_1_sign(cmd);
		printf("sera\n");
	}
	else if ((cmd[i] == '>' || cmd[i + 1] == '>') || (cmd[i + 2] == '<'))
	{
		write_error_red_NL(cmd);
		printf("aqui\n");
	}
	// else if ((cmd[i] == '<' || cmd[i + 1] == '<') && cmd[i + 2] == '\0')
	// 	write_error_red_NL(cmd);
	else if (cmd[i] == '&' && cmd[i + 1] == '>')
	{
		write_error_red_NL(cmd);
		printf("neste\n");
	}
	else if (cmd[i] == '&' || cmd[i] == ';'|| cmd[i] == '|' || cmd[i] == '(' || cmd[i] == ')')
		write_error_red_1_sign(cmd);
}
