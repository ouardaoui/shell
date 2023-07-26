/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 14:35:09 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/25 13:26:47 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	delete_env_var(t_env **env, char *var_name)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strncmp(curr->var_name, var_name, ft_strlen(var_name) + 1))
		{
			if (prev)
			{
				prev->next = curr->next;
				free_the_whole_node(&curr);
				return ;
			}
			*env = curr->next;
			free_the_whole_node(&curr);
			return ;
		}
		prev = curr;
		curr = curr->next;
	}
}

int	execute_unset(t_env **env, t_env **export, char **args)
{
	int	i;

	i = 1;
	while (args[i])
	{
		if (check_valid_export(args[i], "unset"))
		{
			i++;
			continue ;
		}
		if (find_env_var(env, args[i]))
		{
			delete_env_var(export, args[i]);
			delete_env_var(env, args[i]);
		}
		else
			delete_env_var(export, args[i]);
		i++;
	}
	return (0);
}
