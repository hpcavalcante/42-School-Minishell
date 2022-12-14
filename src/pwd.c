/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gissao-m <gissao-m@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:31:40 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/13 21:12:18 by gissao-m         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(void)
{
	char	*pwd_path;

	pwd_path = find_env("PWD");
	write(1, pwd_path, ft_strlen(pwd_path));
	write(1, "\n", 1);
}
