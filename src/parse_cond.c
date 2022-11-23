/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cond.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:09:32 by gissao-m          #+#    #+#             */
/*   Updated: 2022/11/23 17:26:24 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int		redirection(t_link *new, char operator)
{
	char	*cmd;
	int		i;
	int		jump_space;
	int		j;

	i = 0;
	cmd = g_data->buffer;
	while (cmd[i] == ' ' || (cmd[i] == operator && i < 2))
		i++;
	jump_space = i;
	while (cmd[i] != '<' && cmd[i] != '>' && cmd[i] != ' ' && cmd[i] != '|' \
	&& cmd[i] != '&' && cmd[i] != ';' && cmd[i] != '\0' && cmd[i] != '(' && cmd[i] != ')')
		i++;
	if (i == jump_space)
	{
		redirection_error(cmd);
	}
	j = 0;
	if (cmd[j] == '>' && cmd[j + 1] == '>')
		new->append = 1;
	// else if (cmd[0] == '<' && cmd[1] == '<')
	// 	new->delimiter = 1;
	return (i);
}

void	redirection_error(char *cmd)
{
	check_signs(cmd);
	// check_syntax_red(cmd);
}

// void	check_syntax_red(char *cmd)
// {
// 	int i;

// 	i = 0;
// 	if (cmd[i] == '&' && cmd[i + 1] == '>')
// 		write_error_red_NL(cmd);
// 	else if (cmd[i] == '&' || cmd[i] == ';'|| cmd[i] == '|' || cmd[i] == '(' || cmd[i] == ')')
// 		write_error_red_1_sign(cmd);
// }

void	check_signs(char *cmd)
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
		write_error_red_2_signs(cmd);
	else if (cmd[i + 2] == '>')
		write_error_red_1_sign(cmd);
	else if ((cmd[i] == '>' || cmd[i + 1] == '>') ||\
	(cmd[i] == '<' || cmd[i + 1] == '<' || cmd[i + 2] == '<'))
		write_error_red_NL(cmd);
	else if (cmd[i] == '&' && cmd[i + 1] == '>')
	{
		printf("entro aqui");
		write_error_red_NL(cmd);
	}
	else if (cmd[i] == '&' || cmd[i] == ';'|| cmd[i] == '|' || cmd[i] == '(' || cmd[i] == ')')
		write_error_red_1_sign(cmd);
}

void	write_error_red_NL()
{
	write (STDERR, ERROR_HD_NL, 46);
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

void	write_error_red_2_signs(char *cmd)
{
	write(STDERR, SYNTAX_ERROR, 36);
	write(STDERR, cmd, 1);
	write(STDERR, cmd, 1);
	write(STDERR, "'\n", 3);
	g_data->error = 1;
	g_data->exitcode = 2;
}

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
