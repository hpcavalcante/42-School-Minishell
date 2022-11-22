/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cond.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 16:09:32 by gissao-m          #+#    #+#             */
/*   Updated: 2022/11/22 12:50:00 by gissao-m         ###   ########.fr       */
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
	int	i;

	i = 0;
	if (cmd[i + 5] == '<')
	{
		write(STDERR, SYNTAX_ERROR, 36);
		write(STDERR, cmd, 1);
		write(STDERR, cmd, 1);
		write(STDERR, cmd, 1);
		write(STDERR, "'\n", 3);
		g_data->error = 1;
		g_data->exitcode = 2;
	}

	else if (cmd[i + 4] == '<')
	{
		write(STDERR, SYNTAX_ERROR, 36);
		write(STDERR, cmd, 1);
		write(STDERR, cmd, 1);
		write(STDERR, "'\n", 3);
		g_data->error = 1;
		g_data->exitcode = 2;
	}

	else if (cmd[i + 3] == '<')
	{
		write(STDERR, SYNTAX_ERROR, 36);
		write(STDERR, cmd, 1);
		write(STDERR, "'\n", 3);
		g_data->error = 1;
		g_data->exitcode = 2;
	}

	else if (cmd[i + 3] == '>')
	{
		printf ("AQUI!");
		write(STDERR, SYNTAX_ERROR, 36);
		write(STDERR, cmd, 1);
		write(STDERR, cmd, 1);
		write(STDERR, "'\n", 3);
		g_data->error = 1;
		g_data->exitcode = 2;
	}
	
	else if (cmd[i + 2] == '>')
	{
		printf ("AQUI!\n");
		write(STDERR, SYNTAX_ERROR, 36);
		write(STDERR, cmd, 1);
		write(STDERR, "'\n", 3);
		g_data->error = 1;
		g_data->exitcode = 2;
	}
	else if ((cmd[i] == '>' || cmd[i + 1] == '>') || (cmd[i] == '<' || cmd[i + 1] == '<' || cmd[i + 2] == '<'))
	{
		// for (i; cmd[i]; i++)
		// 	printf("cmd: %s\n", cmd);
		write (STDERR, ERROR_HD_NL, 46);
		g_data->error = 1;
		g_data->exitcode = 2;
	}
	check_syntax_red(cmd);
	
}

void	check_syntax_red(char *cmd)
{
	int i;

	i = 0;
	if (cmd[i] == '&' || cmd[i] == ';'|| cmd[i] == '|' || cmd[i] == '(' || cmd[i] == ')')
	{
		write(STDERR, SYNTAX_ERROR, 37);
		write(STDERR, cmd, 1);
		write(STDERR, "'\n", 3);
	}

}