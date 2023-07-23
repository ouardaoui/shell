/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_red_handle.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:18:38 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 18:29:58 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

t_e_token	ft_update_token(int *i, t_e_token type, int k)
{
	if (k == 0)
	{
		*i = 1;
		return (type);
	}
	else
	{
		*i = 0;
		return (update_token(type));
	}
}

int	red_handle(t_cmd **cmd_line, char *str, int handler)
{
	t_cmd		*node;
	t_w_token	*word;
	t_e_token	type;

	node = *cmd_line;
	while (node)
	{
		word = node->word;
		while (word)
		{
			if (!handler && is_red(word->token))
				type = ft_update_token(&handler, word->token, 0);
			else if (handler && is_red(word->token))
				return (print_error(word->token, 0));
			else if (handler && word->string && word->string[0] != '\0')
				word->token = ft_update_token(&handler, type, 1);
			word = word->next;
		}
		if (handler && ft_strchr(str, '|'))
			return (print_error(0, 2));
		else if (handler && !node->next)
			return (print_error(0, 1));
		node = node->next;
	}
	return (0);
}
