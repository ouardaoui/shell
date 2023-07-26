/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:47:13 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/26 16:22:35 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

t_e_token	ft_update_white_space(int *i, int *j, char *str)
{
	while (str[*i] == ' ' || str[*i] == '\t')
	{
		(*i)++;
		(*j)++;
	}
	return (WHITE_SPACE);
}

int	ft_create_node(t_cmd *cmd, int s, int e, int quote)
{
	t_w_token	*node;

	node = (t_w_token *)malloc(sizeof(t_w_token));
	if (!node)
		return (1);
	node->string = ft_substr(cmd->string, s, e - s);
	if (!node->string)
		return (1);
	node->token = quote;
	node->is_expand = 0;
	node->next = NULL;
	if (cmd->string[e] == ' ' || cmd->string[e] == '\0' || cmd->string[e] == '>'
		|| cmd->string[e] == '<' || cmd->string[e - 1] == '>'
		|| cmd->string[e - 1] == '<')
		node->is_link = 0;
	else
		node->is_link = 1;
	add_tree_end(&(*cmd).word, node);
	return (0);
}

int	ft_split_word(t_cmd *node, int start, int end)
{
	char	*str;
	int		len;
	int		quote;

	str = node->string;
	len = ft_strlen(str);
	while (end < len && str[end])
	{
		quote = ARG;
		if (str[end] == ' ')
			quote = ft_update_white_space(&start, &end, str);
		else if (str[end] == '"' || str[end] == '\'')
			quote = ft_update_quote(&end, str, str[end]);
		else if (str[end] == '<' || str[end] == '>')
			quote = ft_update_redir(&end, str, str[end]);
		else
			quote = ft_update_arg(&end, str);
		if (quote != WHITE_SPACE && ft_create_node(node, start, end, quote))
			return (1);
		start = end;
	}
	return (0);
}

int	ft_create_tree(t_cmd **cmd_line)
{
	t_cmd	*node;

	node = *cmd_line;
	while (node)
	{
		if (ft_split_word(node, 0, 0))
			return (1);
		node = node->next;
	}
	return (0);
}
