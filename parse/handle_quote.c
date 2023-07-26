/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 23:56:39 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/26 16:19:24 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	ft_init_str(char **str)
{
	*str = (char *)malloc(sizeof(char) * 1);
	if (!*str)
		return (1);
	(*str)[0] = '\0';
	return (0);
}

int	is_alph_num(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	handle_double_quote(t_w_token *word, t_env *export)
{
	int		start;
	int		end;
	char	*str;

	start = 1;
	end = 1;
	if (ft_init_str(&str))
		return (1);
	if (ft_check(word, str, 2))
		return (0);
	str = ft_loopfct_double(word, &end, str, export);
	if (!str)
		return (1);
	free(word->string);
	word->string = str;
	return (0);
}

int	handle_arg(t_w_token *word, t_env *export)
{
	int		start;
	int		end;
	char	*str;

	start = 0;
	end = 0;
	if (ft_init_str(&str))
		return (1);
	if (ft_check(word, str, 0))
		return (0);
	str = ft_loopfct(word, &end, str, export);
	if (!str)
		return (1);
	free(word->string);
	word->string = str;
	return (0);
}

char	*ft_loopfct_double(t_w_token *word, int *e, char *s, t_env *ex)
{
	int	st;

	st = *e;
	while (word->string[*e] && word->string[*e] != '"')
	{
		s = ft_chunk_double(word, &st, e, s);
		if (word->string[*e] == '$')
		{
			ft_chunk_two(word, &st, e);
			if (word->string[*e] == '?' && ++(*e))
				s = dunder(s);
			else if (word->string[*e] >= '0' && word->string[*e] <= '9'
				&& ++(*e) && st++)
				s = ft_join_dollar(s, word->string + st, *e - st, ex);
			else
			{
				while (word->string[*e] && is_alph_num(word->string[*e]))
					*e = *e + 1;
				s = ft_join_dollar(s, word->string + st, *e - st, ex);
			}
			st = *e;
		}
	}
	return (s);
}
