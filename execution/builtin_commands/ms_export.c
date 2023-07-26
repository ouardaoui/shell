/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/11 17:50:02 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/25 13:25:39 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	swap_env(t_env **a, t_env **b)
{
	char	*temp_var;
	char	*temp_var_name;
	char	*temp_var_content;

	temp_var = ft_strdup((*a)->variable);
	temp_var_name = ft_strdup((*a)->var_name);
	temp_var_content = ft_strdup((*a)->content);
	free_nodes_content(a);
	free ((*a)->var_name);
	(*a)->variable = ft_strdup((*b)->variable);
	(*a)->var_name = ft_strdup((*b)->var_name);
	(*a)->content = ft_strdup((*b)->content);
	free_nodes_content(b);
	free ((*b)->var_name);
	(*b)->variable = ft_strdup(temp_var);
	(*b)->var_name = ft_strdup(temp_var_name);
	(*b)->content = ft_strdup(temp_var_content);
	free (temp_var);
	free (temp_var_name);
	free (temp_var_content);
}

void	add_export_var(t_env **env, t_env **export, char *args)
{
	if (ft_strrchr(args, '='))
	{
		add_env_element(export, args);
		add_env_element(env, args);
		return ;
	}
	add_env_element(export, args);
}

int	check_and_update(t_env **env, t_env **export, char *args)
{
	char	**split;

	if (check_valid_export(args, "export"))
		return (2);
	if (ft_strchr(args, '='))
	{
		split = equal_split(args);
		if (update_env_var(export, split[0], split[1]) == 0)
		{
			if (update_env_var(env, split[0], split[1]))
				return (add_env_element(env, \
				args), free_split(split), 1);
			free_split(split);
			return (1);
		}
		free_split(split);
	}
	if (find_env_var(export, args))
		return (1);
	return (0);
}

void	print_export_list(t_env **export, int fd)
{
	t_env	*temp;

	if (!*export)
		return ;
	temp = *export;
	while (temp)
	{
		ft_putstr_fd("declare -x ", fd);
		ft_putstr_fd(temp->var_name, fd);
		ft_putstr_fd("=\"", fd);
		ft_putstr_fd(temp->content, fd);
		ft_putstr_fd("\"\n", fd);
		temp = temp->next;
	}
}

int	execute_export(t_env **env, t_env **export, char **args, int fd)
{
	t_env	*temp;
	int		i;

	temp = *export;
	i = 0;
	while (args[++i])
	{
		if (check_and_update(env, export, args[i]) == 2)
			g_var.exit_status = 1000;
		else if (check_and_update(env, export, args[i]) == 1)
			continue ;
		else
			add_export_var(env, export, args[i]);
	}
	if (args[1] && g_var.exit_status == 1000)
		return (g_var.exit_status = 1);
	else if (args[1])
		return (g_var.exit_status = 0);
	sort_env(export);
	print_export_list(export, fd);
	return (g_var.exit_status = 0);
}
