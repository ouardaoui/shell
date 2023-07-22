/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:18:27 by mlagrini          #+#    #+#             */
/*   Updated: 2023/02/24 12:35:52 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (0);
	while (i < ((int )n - 1)
		&& ((unsigned char *)s1)[i] == ((unsigned char *)s2)[i])
			i++;
	return (((unsigned char *)s1)[i] - ((unsigned char *)s2)[i]);
}
