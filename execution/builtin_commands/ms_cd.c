/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:33:37 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 18:16:45 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	update_wd(t_env **env, char *curr_pwd)
{
	char	*pwd;
	char	*temp;
	char	*cwd;

	pwd = NULL;
	temp = NULL;
	cwd = malloc(PATH_MAX * sizeof(char));
	cwd = getcwd(cwd, PATH_MAX);
	if (update_env_var(env, "PWD", cwd))
	{
		temp = ft_strjoin("PWD", "=");
		pwd = ft_strjoin(temp, cwd);
		add_env_element(env, pwd);
		free (pwd);
		free (temp);
	}
	if (update_env_var(env, "OLDPWD", curr_pwd))
	{
		temp = ft_strjoin("OLDPWD", "=");
		pwd = ft_strjoin(temp, curr_pwd);
		add_env_element(env, pwd);
		free (pwd);
		free (temp);
	}
	free (cwd);
}

int	prev_dir(t_env **env, char *curr_pwd)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->var_name, "OLDPWD", 7) == 0)
		{
			if (chdir(temp->content) == 0)
				return (0);
			perror("minishell");
			free (curr_pwd);
			return (1);
		}
		temp = temp->next;
	}
	ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2);
	free (curr_pwd);
	return (1);
}

int	execute_home_cd(t_env **env, t_env **export, char *curr_pwd)
{
	t_env	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strncmp(temp->var_name, "HOME", 5) == 0)
		{
			if (!(chdir(temp->content)))
			{
				update_wd(env, curr_pwd);
				update_wd(export, curr_pwd);
				return (0);
			}
			perror("cd");
			return (1);
		}
		temp = temp->next;
	}
	ft_putstr_fd("minishell: cd: HOME not set\n", 2);
	return (1);
}

int	execute_cd(t_env **env, t_env **export, char **args)
{
	char	*curr_pwd;

	curr_pwd = malloc (PATH_MAX * sizeof(char));
	curr_pwd = getcwd(curr_pwd, PATH_MAX);
	if (args[1])
	{
		if (!ft_strncmp(args[1], "-", 2) && prev_dir(env, curr_pwd))
			return (g_var.exit_status = 1);
		else if (ft_strncmp(args[1], "-", 2))
		{
			if (chdir(args[1]))
				return (free(curr_pwd), perror("minishell"), \
				g_var.exit_status = 1);
		}
		update_wd(env, curr_pwd);
		update_wd(export, curr_pwd);
		free (curr_pwd);
		return (g_var.exit_status = 0);
	}
	g_var.exit_status = execute_home_cd(env, export, curr_pwd);
	return (free(curr_pwd), g_var.exit_status);
}
