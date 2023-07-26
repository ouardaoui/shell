/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 17:43:02 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/24 13:00:36 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	ft_alloc_cmd(t_cmd **cmd)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!*cmd)
		return (1);
	(*cmd)->next = NULL;
	(*cmd)->word = NULL;
	return (0);
}

void	ft_loop(char *str, int *i)
{
	t_e_token	quote;

	quote = ARG;
	while (str[*i] != '\0')
	{
		if (quote == ARG && str[*i] == '|')
			return ;
		if (str[*i] == '"' && quote == ARG)
			quote = IN_D_QUOTE;
		else if (str[*i] == '\'' && quote == ARG)
			quote = IN_QUOTE;
		else if (str[*i] == '"' && quote == IN_D_QUOTE)
			quote = ARG;
		else if (str[*i] == '\'' && quote == IN_QUOTE)
			quote = ARG;
		*i = *i + 1;
	}
	return ;
}

int	ft_create_list_cmd(char *str, t_cmd **cmd_line)
{
	int		start;
	int		end;
	char	*string;
	t_cmd	*node;

	start = 0;
	end = 0;
	while (str[end])
	{
		if (ft_alloc_cmd(&node))
			return (1);
		ft_loop(str, &end);
		string = ft_substr(str, start, end - start);
		if (!string)
			return (1);
		node->string = string;
		node->fd = 0;
		node->fd_out = -2;
		if (str[end] == '|')
			end++;
		start = end;
		ft_add_end(cmd_line, node);
	}
	return (0);
}
