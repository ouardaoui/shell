/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipes.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/23 19:53:57 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 20:12:20 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**split_path(t_env **env)
{
	t_env	*temp;
	char	**path_split;
	char	*path;

	if (*env == NULL)
		return (NULL);
	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->var_name, "PATH", 5) == 0)
		{
			path = ft_strdup(temp->content);
			path_split = ft_split(path, ':');
			free (path);
			return (path_split);
		}
		temp = temp->next;
	}
	return (NULL);
}

char	*find_path(char **paths, char **args)
{
	int		i;
	char	*path;
	char	*temp;
	char	*temp2;

	i = 0;
	while (paths[i])
	{
		temp = ft_strdup(paths[i]);
		temp2 = ft_strjoin(temp, "/");
		path = ft_strjoin(temp2, args[0]);
		if (access(path, X_OK) == 0)
			return (free(temp), free(temp2), path);
		i++;
		free (path);
		free (temp);
		free (temp2);
	}
	return (NULL);
}

int	is_path_env(t_env **env, char ***paths, char *arg)
{
	*paths = split_path(env);
	if (!*paths)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (g_var.exit_status = 127);
	}
	return (0);
}

int	does_path_exist(char **path, char **paths_arr, char **args)
{
	*path = find_path(paths_arr, args);
	if (!*path)
	{
		ft_putstr_fd("bash: ", 2);
		ft_putstr_fd(args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		free_split(paths_arr);
		return (g_var.exit_status = 127);
	}
	return (0);
}
