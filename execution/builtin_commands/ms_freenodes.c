/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_freenodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 16:45:06 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/23 18:43:25 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_nodes_content(t_env **node)
{
	if ((*node)->content)
		free ((*node)->content);
	if ((*node)->variable)
		free ((*node)->variable);
}

void	free_the_whole_node(t_env **node)
{
	free_nodes_content(node);
	if ((*node)->var_name)
		free((*node)->var_name);
	free (*node);
}

void	free_list(t_env **list)
{
	if (!*list)
		return ;
	while (*list)
	{
		free_the_whole_node(list);
		*list = (*list)->next;
	}
}

void	free_w_token(t_w_token **w_token)
{
	if (!*w_token)
		return ;
	free((*w_token)->string);
	free_w_token(&(*w_token)->next);
	free(*w_token);
	*w_token = NULL;
}

void	free_cmd(t_cmd **head)
{
	t_cmd	*tmp;

	while (*head)
	{
		tmp = (*head)->next;
		if ((*head)->string)
		{
			free((*head)->string);
			(*head)->string = NULL;
		}
		if ((*head)->word)
			ft_free_word(&(*head)->word);
		if ((*head)->fd > 2)
			close((*head)->fd);
		if ((*head)->fd_out > 2)
			close ((*head)->fd_out);
		free(*head);
		*head = tmp;
	}
}
