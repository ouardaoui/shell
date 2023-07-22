/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 17:15:01 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/21 11:11:04 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	find_env_var(t_env **env, char *var_name)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->var_name, var_name, ft_strlen(var_name)) == 0)
			return (1);
		temp = temp->next;
	}
	return (0);
}

int	update_env_var(t_env **env, char *name, char *content)
{
	t_env	*temp;
	char	*var_holder;

	temp = *env;
	var_holder = NULL;
	while (temp)
	{
		if (strncmp(temp->var_name, name, ft_strlen(name)) == 0)
		{
			free_nodes_content(&temp);
			temp->content = ft_strdup(content);
			var_holder = ft_strjoin(temp->var_name, "=");
			temp->variable = ft_strjoin(var_holder, temp->content);
			return (free (var_holder), 0);
		}
		temp = temp->next;
	}
	return (1);
}

void	free_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		free(split[i++]);
	free (split);
}

char	**equal_split(char *var)
{
	int		i;
	char	**split;

	i = 0;
	if (ft_strchr(var, '=') == NULL)
	{
		split = malloc (sizeof(char *) * 2);
		split[0] = ft_strdup(var);
		split[1] = NULL;
		return (split);
	}
	split = malloc(sizeof(char *) * 3);
	while (var[i])
	{
		if (var[i] == '=')
		{
			split[0] = ft_substr(var, 0, i);
			i++;
			split[1] = ft_substr(var, i, ft_strlen(var) + i);
			split[2] = NULL;
			return (split);
		}
		i++;
	}
	return (split);
}

void	sort_env(t_env **env)
{
	int		flag;
	t_env	*temp1;
	t_env	*temp2;

	flag = 1;
	if (*env == NULL || (*env)->next == NULL)
		return ;
	while (flag == 1)
	{
		flag = 0;
		temp1 = *env;
		temp2 = NULL;
		while (temp1->next != temp2)
		{
			if (ft_strcmp(temp1->var_name, temp1->next->var_name) > 0)
			{
				swap_env(&temp1, &temp1->next);
				flag = 1;
			}
			temp1 = temp1->next;
		}
		temp2 = temp1;
	}
	return ;
}
