/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_execute_pipes.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/16 17:08:20 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/25 12:46:05 by mlagrini         ###   ########.fr       */
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
	if (args && args[0] && (args[0][0] == '/' || args[0][0] == '.'))
		path = is_path_valid(args[0]);
	else
	{
		if (is_path_env(env, &paths, args[0]))
			exit(g_var.exit_status = 127);
		if (does_path_exist(&path, paths, args))
			exit(g_var.exit_status = 127);
	}
	if (fd_in > 2)
		dup2(fd_in, STDIN_FILENO);
	if (fd_out > 2)
		dup2(fd_out, STDOUT_FILENO);
	if (execve(path, args, environ) < 0)
		print_command_error(path, strerror(errno));
	return (g_var.exit_status = 0);
}

void	child_job(t_cmd *cmd, int *fd, t_env **env, t_env **export)
{
	char	**args;

	cmd_signals();
	args = args_array(&cmd);
	if (cmd->next)
		dup2(fd[1], STDOUT_FILENO);
	close (fd[0]);
	close (fd[1]);
	if (cmd->word->token == BUILTIN)
		execute_builtins(env, &cmd, export);
	else
	{
		if (!args[0][0])
			exit(g_var.exit_status);
		execute_command(env, args, cmd->fd, cmd->fd_out);
	}
	free_split(args);
	exit(g_var.exit_status);
}

void	parent_job(pid_t id, int *fd_holder, int *fd)
{
	shell_signals();
	close (fd[1]);
	if (*fd_holder)
		close (*fd_holder);
	*fd_holder = fd[0];
	waitpid(id, &g_var.exit_status, 0);
}

int	exec_pipes(t_env **env, t_cmd **cmd, t_env **export)
{
	t_cmd	*temp;
	int		fd[2];
	pid_t	id;
	int		fd_holder;

	fd_holder = 0;
	temp = *cmd;
	while (temp)
	{
		pipe(fd);
		id = fork();
		if (id < 0)
			break ;
		if (id == 0)
		{
			dup2(fd_holder, STDIN_FILENO);
			child_job(temp, fd, env, export);
		}
		else
			parent_job(id, &fd_holder, fd);
		temp = temp->next;
	}
	close (fd[0]);
	close (fd[1]);
	return (g_var.exit_status = WEXITSTATUS(g_var.exit_status));
}
