/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/14 17:26:05 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 20:38:19 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

char	*ft_join(char *str, char *word, int start, int end)
{
	char	*s;
	int		len;
	int		i;

	len = ft_strlen(str) + end - start + 1;
	s = (char *)malloc(sizeof(char) * len);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i])
	{
		s[i] = str[i];
		i++;
	}
	free(str);
	while (start < end)
	{
		s[i] = word[start];
		start++;
		i++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_join_env(char *s1, char *s2)
{
	int		i;
	int		j;
	int		len;
	char	*s;

	len = ft_strlen(s1) + ft_strlen(s2) + 1;
	s = (char *)malloc(sizeof(char) * len);
	if (!s)
		return (NULL);
	i = 0;
	while (s1[i])
	{
		s[i] = s1[i];
		i++;
	}
	free(s1);
	j = 0;
	while (s2[j])
	{
		s[i] = s2[j];
		i++;
		j++;
	}
	s[i] = '\0';
	return (s);
}

char	*ft_join_dollar(char *str, char *word, int len, t_env *export)
{
	int		j;
	char	*s;

	j = 0;
	s = (char *)malloc(sizeof(char) * len + 1);
	if (!s)
		return (NULL);
	while (j < len)
	{
		s[j] = word[j];
		j++;
	}
	s[j] = '\0';
	while (export)
	{
		if (!ft_strcmp(export->var_name, s))
		{
			free(s);
			return (ft_join(str, export->content, 0,
					ft_strlen(export->content)));
		}
		export = export->next;
	}
	free(s);
	return (str);
}

t_e_token	ft_update_redir(int *i, char *str, char c)
{
	int	len;

	len = (*i)++;
	while (str[*i] && str[*i] == c)
		(*i)++;
	len = *i - len;
	if (len == 1 && c == '>')
		return (RED_OUTPUT);
	if (len == 2 && c == '>')
		return (APPEND_OUTPUT);
	if (len == 1 && c == '<')
		return (RED_INPUT);
	if (len == 2 && c == '<')
		return (HER_DOC);
	return (REDIRECTION);
}

t_e_token	ft_update_arg(int *i, char *str)
{
	while (str[*i] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\''
		&& str[*i] != '"' && str[*i] != '<' && str[*i] != '>')
		(*i)++;
	return (ARG);
}
