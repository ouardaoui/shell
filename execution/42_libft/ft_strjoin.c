/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/05 21:54:59 by mlagrini          #+#    #+#             */
/*   Updated: 2023/06/14 13:08:25 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_nulljoin(char *s1)
{
	char	*cat;
	int		i;

	i = 0;
	cat = malloc ((ft_strlen(s1) + 1) * sizeof(char));
	while (s1[i])
	{
		cat[i] = s1[i];
		i++;
	}
	cat[i] = '\0';
	return (cat);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*cat;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (s2 == NULL)
		return (ft_nulljoin((char *)s1));
	cat = malloc((ft_strlen(s1) + ft_strlen(s2) + 1) * sizeof(char));
	if (cat == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		cat[i] = ((char *)s1)[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		cat[i] = s2[j];
		j++;
		i++;
	}
	cat[i] = '\0';
	return (cat);
}
