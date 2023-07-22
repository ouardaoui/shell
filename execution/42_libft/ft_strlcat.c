/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 18:52:08 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/13 19:31:44 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	dstlen;
	size_t	srclen;

	i = 0;
	if (dstsize == 0)
	{
		srclen = ft_strlen(src);
		return (srclen);
	}
	dstlen = ft_strlen(dst);
	srclen = ft_strlen(src);
	if (dstlen > dstsize)
		return (srclen + dstsize);
	if (dstlen < dstsize)
	{
		while (src[i] != '\0' && (dstlen + i) < (dstsize - 1))
		{
			dst[dstlen + i] = src [i];
			i++;
		}
	dst[dstlen + i] = '\0';
	}
	return (dstlen + srclen);
}
/*
int	main()
{
	char dest[30]; memset(dest, 0, 30);
	char * src = (char *)"AAAAAAAAA";
	dest[0] = 'B';

	printf("%lu\n", strlcat(dest, "123", 0));
	printf("%lu\n", ft_strlcat(dest, "123", 0));
	return (0);
}*/
