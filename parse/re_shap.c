/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   re_shap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 12:25:44 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 18:51:21 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

char	*ft_join_str(char *s1, char *s2)
{
	int		len;
	char	*str;
	int		i;
	int		j;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	str = (char *)malloc(sizeof(char) * len);
	if (!str)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (s2[j])
		str[i++] = s2[j++];
	str[i] = '\0';
	free(s2);
	return (str);
}

int	word_count(char *str)
{
	int	c;
	int	i;

	c = 0;
	i = 0;
	while (str[i] == ' ')
		i++;
	while (str[i])
	{
		if (str[i] != '\0' && str[i] != ' ')
			c++;
		while (str[i] != '\0' && str[i] != ' ')
			i++;
		i++;
	}
	return (c);
}

char	**split_word(char *str)
{
	int		i;
	int		len;
	char	**split;

	i = 0;
	split = (char **)malloc(sizeof(char *) * 3);
	if (!split)
		return (NULL);
	split[2] = NULL;
	len = 0;
	while (str[i] && str[i] != ' ')
		len++;
	split[0] = ft_substr(str, i, len);
	while (str[i] && str[i] == ' ')
		i++;
	len = ft_strlen(str + i);
	split[1] = ft_substr(str, i, len);
	return (split);
}

void	ft_handle_shap(t_cmd **cmd)
{
	t_cmd		*cmd_line;
	t_w_token	*node;

	cmd_line = *cmd;
	while (cmd_line)
	{
		node = cmd_line->word;
		while (node)
		{
			if (is_builtin(node->string))
				node->token = BUILTIN;
			node = node->next;
		}
		cmd_line = cmd_line->next;
	}
	return ;
}

int	re_shap(t_cmd **cmd)
{
	t_w_token	*node;
	t_w_token	*tmp;
	t_cmd		*cmd_line;

	cmd_line = *cmd;
	while (cmd_line)
	{
		node = cmd_line->word;
		while (node)
		{
			if (node->is_link)
			{
				tmp = node->next;
				node->string = ft_join_str(node->string, tmp->string);
				node->is_link = tmp->is_link;
				node->next = tmp->next;
				free(tmp);
			}
			else
				node = node->next;
		}
		cmd_line = cmd_line->next;
	}
	return (0);
}
