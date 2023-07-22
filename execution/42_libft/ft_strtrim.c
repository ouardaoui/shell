/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/06 12:57:23 by mlagrini          #+#    #+#             */
/*   Updated: 2022/10/15 21:11:35 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*trimlead(char *s1, char *set)
{
	int	j;
	int	count;

	count = 0;
	j = 0;
	while (set[j] != '\0')
	{
		while (s1[count] == set[j])
		{
			count++;
			j = 0;
		}
		j++;
	}
	return (s1 + count);
}

static char	*trimtrail(char *s1, char *set)
{
	int	j;
	int	len;

	j = 0;
	len = ft_strlen(s1) - 1;
	while (set[j] != '\0')
	{
		while (s1[len] == set[j])
		{
			len--;
			j = 0;
		}
		j++;
	}
	s1[len + 1] = '\0';
	return (s1);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trimmed;
	char	*dst;

	trimmed = trimlead((char *)s1, (char *)set);
	if (*trimmed == '\0')
		return (ft_strdup(""));
	dst = ft_calloc((ft_strlen(trimmed) + 1), sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst = ft_memmove(dst, trimmed, (ft_strlen(trimmed) + 1));
	dst = trimtrail(dst, (char *)set);
	return (dst);
}
