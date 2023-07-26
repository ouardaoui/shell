/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_utiles2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 21:54:34 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 20:29:12 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	is_redir(t_w_token *word)
{
	if (word->token != REDIRECTION && word->token != RED_INPUT \
		&& word->token != RED_OUTPUT && word->token != HER_DOC \
		&& word->token != OUTPUT_FILE && word->token != APPEND_FILE \
		&& word->token != DELIMITER && word->token != APPEND_OUTPUT \
		&& word->token != INPUT_FILE)
		return (1);
	return (0);
}

int	args_counter(t_w_token **words)
{
	int			i;
	t_w_token	*temp;

	i = 0;
	temp = *words;
	while (temp)
	{
		if (is_redir(temp))
			i++;
		temp = temp->next;
	}
	return (i);
}

char	**args_array(t_cmd **cmd)
{
	char		**args;
	int			len;
	t_w_token	*temp;
	int			i;

	i = 0;
	temp = (*cmd)->word;
	len = args_counter(&(*cmd)->word);
	i = ft_handle_expand(&len, (*cmd)->word, &args);
	if (i)
	{
		temp = temp->next;
		i = 2;
	}
	else
		i = 0;
	while (temp)
	{
		if (is_redir(temp))
			args[i++] = ft_strdup(temp->string);
		temp = temp->next;
	}
	args[i] = NULL;
	return (args);
}
