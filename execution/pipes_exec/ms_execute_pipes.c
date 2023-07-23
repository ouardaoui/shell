/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:08:20 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/23 19:43:42 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_arr(t_env **env)
{
	t_env	*temp;
	char	**env_arr;
	int		len;
	int		i;

	temp = *env;
	env_arr = NULL;
	len = 0;
	while (temp)
	{
		len++;
		temp = temp->next;
	}
	env_arr = malloc (sizeof(char *) * (len + 1));
	i = 0;
	temp = *env;
	while (temp)
	{
		env_arr[i++] = ft_strdup(temp->variable);
		temp = temp->next;
	}
	env_arr[i] = NULL;
	return (env_arr);
}

int	execute_command(t_env **env, char **args, int fd_in, int fd_out)
{
	char	**paths;
	char	*path;
	char	**environ;

	paths = NULL;
	path = NULL;
	environ = env_to_arr(env);
	if ( args && args[0] && (args[0][0] == '/' || args[0][0] == '.'))
		path = is_path_valid(args[0]);
	else
	{
		if (is_path_env(env, &paths, args[0]))
			exit(g_exit_status = 127);
		if (does_path_exist(&path, paths, args))
			exit(g_exit_status = 127);
	}
	if (fd_in > 2)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out > 2)
		dup2(fd_out, STDOUT_FILENO);	
	if (execve(path, args, environ) < 0)
	{
		free_split(paths);
		free(path);
	}
	return (g_exit_status = 0);
}

int	exec_pipes(t_env **env, t_cmd **cmd, t_env **export)
{
	t_cmd	*temp;
	int		fd[2];
	pid_t	id;
	int		fd_holder;
	char	**args;

	fd_holder = 0;
	temp = *cmd;
	args = NULL;
	while (temp)
	{
		pipe(fd);
		id = fork();
		if (id == 0)
		{
			args = args_array(&temp);
			dup2(fd_holder, STDIN_FILENO);
			if (temp->next)
				dup2(fd[1], STDOUT_FILENO);
			close(fd[0]);
			close(fd[1]);
			if (temp->word->token == BUILTIN)
				execute_builtins(env, &temp, export);
			else
				execute_command(env, args, temp->fd, temp->fd_out);
			free(args);
			exit(0);
		}
		else
		{
			close(fd[1]);
			if (fd_holder)
				close(fd_holder);
			fd_holder = fd[0];
			waitpid(id, &g_exit_status, 0);
		}
		temp = temp->next;
	}
	close (fd[0]);
	close (fd[1]);
	return (g_exit_status = WEXITSTATUS(g_exit_status));
}
