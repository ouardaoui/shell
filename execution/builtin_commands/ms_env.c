/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:50:06 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/21 11:04:34 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	env_errors(int errno, char *arg)
{
	if (errno == 1)
	{
		ft_putstr_fd("env: illegal option\n", 2);
		return (g_exit_status = 1);
	}
	ft_putstr_fd("env: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(" No such file or directory\n", 2);
	return (g_exit_status = 127);
}

int	execute_env(t_env *env, char **args, int fd)
{
	t_env	*curr;

	curr = env;
	if (args[1])
	{
		if (!ft_strncmp(args[1], "-", 1))
			return (env_errors(1, args[1]));
		return (env_errors(127, args[1]));
	}
	if (env == NULL)
		return (0);
	while (curr)
	{
		if (curr->var_name)
		{
			ft_putstr_fd(curr->variable, fd);
			ft_putstr_fd("\n", fd);
		}
		curr = curr->next;
	}
	return (g_exit_status = 0);
}

void	create_envnode(t_env **head, char *name, char *var, char *env_var)
{
	t_env	*new_node;
	t_env	*last;

	last = NULL;
	new_node = malloc (sizeof(t_env));
	new_node->var_name = ft_strdup(name);
	new_node->content = ft_strdup(var);
	new_node->variable = ft_strdup(env_var);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	last = *head;
	while (last->next != NULL)
		last = last->next;
	last->next = new_node;
}

void	add_env_element(t_env **node, char *var)
{
	int		i;
	char	**split;

	i = 0;
	split = equal_split(var);
	if (split[1] == NULL)
	{
		create_envnode(node, split[0], "", var);
		free_split(split);
		return ;
	}
	create_envnode(node, split[0], split[1], var);
	free_split(split);
}

void	fill_envlist(t_env **env, t_env **export, t_data *data, char **environ)
{
	int			i;

	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "OLDPWD=", 7) != 0)
		{
			if (ft_strncmp(environ[i], "HOME=", 5) == 0)
				data->home_dir = ft_strdup(&environ[i][5]);
			add_env_element(env, environ[i]);
		}
		i++;
	}
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], "OLDPWD=", 7) == 0)
			add_env_element(export, "OLDPWD");
		else
			add_env_element(export, environ[i]);
		i++;
	}
}
