/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_utiles.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 10:12:36 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 20:35:40 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	commands_counter(t_cmd **cmd)
{
	t_cmd	*temp;
	int		i;

	temp = *cmd;
	i = 0;
	while (temp)
	{
		i++;
		temp = temp->next;
	}
	return (i);
}

int	more_than(char *str)
{
	int	i;

	i = 0;
	while (*str)
	{
		while (*str && *str == ' ' )
			str++;
		if (*str && *str != ' ')
			i++;
		while (*str && *str != ' ')
			str++;
	}
	return (i);
}

void	ft_take_len(char *str, int *i, int *j)
{
	*i = 0;
	*j = 0;
	while (*str && *str == ' ')
		str++;
	while (str[*i] && str[*i] != ' ')
		*i = *i + 1;
	str = str + *i;
	while (*str && *str == ' ')
		str++;
	while (str[*j])
		*j = *j + 1;
}

int	ft_handle_expand(int *len, t_w_token *node, char ***args)
{
	int	k;
	int	len_1;
	int	len_2;
	int	key;

	k = 0;
	key = 0;
	if (node->is_expand && more_than(node->string) > 1 && ++key && ++k)
		*len = *len + 1;
	*args = (char **)malloc(sizeof(char *) * (*len + 1));
	if (k)
	{
		k = 0;
		ft_take_len(node->string, &len_1, &len_2);
		while (node->string[k] && node->string[k] == ' ')
			k++;
		args[0][0] = ft_substr(node->string, k, len_1);
		len_1 = len_1 + k;
		while (node->string[len_1] && node->string[len_1] == ' ')
			len_1++;
		args[0][1] = ft_substr(node->string, len_1, len_2);
	}
	return (key);
}
