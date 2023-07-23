/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 18:35:16 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 18:44:57 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	handle_single_quote(t_w_token *word, char c)
{
	char	*str;
	int		i;
	int		len;

	len = ft_strlen(word->string);
	if (len < 2)
		return (1);
	str = (char *)malloc(sizeof(char) * (len - 2 + 1));
	if (!str)
		return (1);
	i = 1;
	while (word->string[i] != c && word->string[i])
	{
		str[i - 1] = word->string[i];
		i++;
	}
	str[i - 1] = '\0';
	free(word->string);
	word->string = str;
	return (0);
}

int	ft_expand(t_w_token *word, t_env *export)
{
	int	k;

	k = 0;
	while (word)
	{
		if (word->token == DELIMITER)
		{
			if (word->string[0] == '\'')
				k = handle_single_quote(word, '\'');
			else if (word->string[0] == '"')
				k = handle_single_quote(word, '"');
			if (k)
				return (1);
		}
		else if (word->string[0] == '\'' && handle_single_quote(word, '\''))
			return (1);
		else if (word->string[0] == '"' && handle_double_quote(word, export))
			return (1);
		else if (word->token == ARG && handle_arg(word, export))
			return (1);
		word = word->next;
	}
	return (0);
}

int	expand(t_cmd **cmd_line, t_env *export, int rslt)
{
	t_cmd	*node;

	node = *cmd_line;
	while (node)
	{
		rslt = ft_expand(node->word, export);
		if (rslt)
			return (rslt);
		node = node->next;
	}
	return (rslt);
}
