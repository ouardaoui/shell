/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 16:26:29 by mlagrini          #+#    #+#             */
/*   Updated: 2022/10/15 15:12:36 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	if (c == 0 && n == 0)
		return (0);
	while (((unsigned char *)s)[i] != (unsigned char)c)
	{
		if (count >= (int )n)
			return (0);
		i++;
		count++;
	}
	return ((unsigned char *)s + i);
}
