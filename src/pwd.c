/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 15:31:40 by hepiment          #+#    #+#             */
/*   Updated: 2022/12/12 18:54:43 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin()
{
	char	*pwd_path;
	
	pwd_path = find_env("PWD");
	write(1, pwd_path, ft_strlen(pwd_path));	
	write(1, "\n", 1);	
}