/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:36:58 by hepiment          #+#    #+#             */
/*   Updated: 2022/10/26 12:26:26 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	tokenizer()
{
	int	i;

	i = 1;
	while (g_data->buffer[i] != '\0')
	{
		while (g_data->buffer[i] == ' ')
			i++;
		if (g_data->buffer[i] == '|')
		{
			printf("bash: syntax error near unexpected token `|'\n");
		}
		i--;
	}
}