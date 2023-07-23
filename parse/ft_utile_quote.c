/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utile_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:08:24 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/24 00:08:05 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

char	*ft_chunk(t_w_token *word, int *start, int *end, char *str)
{
	int	i;
	int	j;

	while (word->string[*end] && word->string[*end] != '$')
		*end = *end + 1;
	if (*end != *start)
	{
		i = *start;
		j = *end;
		str = ft_join(str, word->string, i, j);
		if (!str)
			return (NULL);
		*start = *end;
	}
	return (str);
}

char	*ft_chunk_double(t_w_token *word, int *start, int *end, char *str)
{
	int	i;
	int	j;

	while (word->string[*end] && word->string[*end] != '$'
		&& word->string[*end] != '"')
		*end = *end + 1;
	if (*end != *start)
	{
		i = *start;
		j = *end;
		str = ft_join(str, word->string, i, j);
		if (!str)
			return (NULL);
		*start = *end;
	}
	return (str);
}

char	*ft_chunk_two(t_w_token *word, int *start, int *end, char *str)
{
	char	*pt;

	word->is_expand = 1;
	*start = *start + 1;
	*end = *end + 1;
	if (word->string[*end] == '?')
	{
		*end = *end + 1;
		pt = ft_itoa(g_exit_status);
		str = ft_join(str, pt, 0, ft_strlen(pt));
		free(pt);
	}
	return (str);
}

int	ft_check(t_w_token *word, char *str, int i)
{
	if ((int)ft_strlen(word->string) == i)
	{
		free(word->string);
		word->string = str;
		return (1);
	}
	return (0);
}

char	*ft_loopfct(t_w_token *word, int *e, char *s, t_env *ex)
{
	int	st;

	st = *e;
	while (word->string[*e])
	{
		s = ft_chunk(word, &st, e, s);
		if (word->string[*e] == '$')
		{
			s = ft_chunk_two(word, &st, e, s);
			if (word->string[*e] > '0' && word->string[*e] < '9')
			{
				*e = *e + 1;
				s = ft_join_dollar(s, word->string + st, *e - st, ex);
			}
			else
			{
				while (word->string[*e] && is_alph_num(word->string[*e])
					&& ++(*e))
					;
				s = ft_join_dollar(s, word->string + st, *e - st, ex);
			}
			st = *e;
		}
	}
	return (s);
}
