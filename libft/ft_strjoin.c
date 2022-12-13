/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hepiment <hepiment@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/03 15:47:51 by gissao-m          #+#    #+#             */
/*   Updated: 2022/12/13 07:54:43 by hepiment         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		count_s1;
	int		count_s2;
	char	*join;
	size_t	lenght;

	count_s1 = -1;
	count_s2 = -1;
	if (s1 == 0 || s2 == 0)
		return (NULL);
	lenght = ft_strlen(s1) + ft_strlen(s2) + 1;
	join = (char *)malloc(lenght);
	if (join == 0)
		return (NULL);
	while (s1[++count_s1] != '\0')
		join[count_s1] = s1[count_s1];
	while (s2[++count_s2] != '\0')
		join[count_s1 + count_s2] = s2[count_s2];
	join[count_s1 + count_s2] = '\0';
	return (join);
}

char	*ft_my_strjoin(char *s1, char *s2)
{
	char	*s;
	int		count;
	int		count2;

	count = -1;
	count2 = 0;
	if (s1 == NULL && s2 != NULL)
		return (ft_strdup(s2));
	s = malloc ((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (s == NULL || s2 == NULL)
		return (NULL);
	while (s1[++count] != '\0')
		s[count] = s1[count];
	while (s2[count2] != '\0')
	{
		s[count] = s2[count2];
		count++;
		count2++;
	}
	s[count] = '\0';
	free (s1);
	return (s);
}