/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/08 17:13:26 by mlagrini          #+#    #+#             */
/*   Updated: 2022/10/15 21:01:23 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char			*dst;
	unsigned int	i;

	i = 0;
	dst = malloc ((ft_strlen(s) + 1) * sizeof(char));
	if (dst == NULL)
		return (NULL);
	dst = ft_memmove(dst, (char *)s, (ft_strlen(s) + 1));
	while (dst[i] != '\0')
	{
		dst[i] = f(i, dst[i]);
		i++;
	}
	return (dst);
}
