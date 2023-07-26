/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utile_quote.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:08:24 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/26 16:18:37 by aouardao         ###   ########.fr       */
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
	while (word->string[*end] && word->string[*end] != '$'
		&& word->string[*end] != '"')
		*end = *end + 1;
	if (*end != *start)
	{
		str = ft_join(str, word->string, *start, *end);
		if (!str)
			return (NULL);
		*start = *end;
	}
	return (str);
}

void	ft_chunk_two(t_w_token *word, int *start, int *end)
{
	word->is_expand = 1;
	*start = *start + 1;
	*end = *end + 1;
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
			ft_chunk_two(word, &st, e);
			if (word->string[*e] == '?' && ++(*e))
				s = dunder(s);
			else if (word->string[*e] >= '0' && word->string[*e] <= '9'
				&& ++(*e))
				s = ft_join_dollar(s, word->string + st, *e - st, ex);
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
