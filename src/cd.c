/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/12 13:55:09 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/12 17:08:54 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	change_pwd()
{
	char	*buf;
	char	*old_pwd;
	char	*cwd;

	if (find_env("PWD") == NULL)
		return ;
	buf = malloc (1024);
	old_pwd = ft_strjoin(ft_strdup("OLDPWD="), find_env("PWD"));
	cwd = ft_strjoin(ft_strdup("PWD="), getcwd(buf, 1024));
	do_export(cwd);
	do_export(old_pwd);
	free (cwd);
	free (old_pwd);
	free (buf);
}

void cd_oldpwd()
{
	if (find_env("OLDPWD") == NULL)
	{
		write(STDERR, "cd: OLDPWD not set\n", 19);
		return ;
	}
	chdir(find_env("OLDPWD"));
	ft_putstr_fd(find_env("OLDPWD"), STDOUT);
	write (1, "\n", 1);
}

void	cd_builtin(char **cmd)
{
	g_data->exitcode = 0;
	if (cmd[1] == NULL || ft_str_check(cmd[1], "~"))
	{
		if (find_env("HOME") == NULL)
			return ;
		chdir(find_env("HOME"));
		change_pwd();
	}
	else if (cmd[2] != NULL)
	{
		g_data->exitcode = 1;
		write(STDERR, "cd: too many arguments\n", 23); 
	}
	else
	{
		if (ft_str_check(cmd[1], "-"))
			cd_oldpwd();
		else if (access(cmd[1], F_OK) == 0)
			chdir(cmd[1]);
		else
			dir_error(cmd);
		change_pwd();
	}
}