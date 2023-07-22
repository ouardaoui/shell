/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_main.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:47:50 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/22 21:49:42 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_builtins(t_env **env, t_cmd **cmd, t_env **export)
{
	char	**args;

	args = args_array(cmd);
	if (!(ft_strncmp(args[0], "env", 4)) || !(ft_strncmp(args[0], "ENV", 4)))
		g_exit_status = execute_env(*env, args, (*cmd)->fd_out);
	else if (!(ft_strncmp(args[0], "pwd", 4)) \
			|| !(ft_strncmp(args[0], "PWD", 4)))
		g_exit_status = execute_pwd(args, (*cmd)->fd_out);
	else if ((ft_strncmp(args[0], "cd", 3) == 0))
		g_exit_status = execute_cd(env, export, args);
	else if (!(ft_strncmp(args[0], "export", 7)))
		g_exit_status = execute_export(env, export, args, (*cmd)->fd_out);
	else if (!(ft_strncmp(args[0], "unset", 6)))
		g_exit_status = execute_unset(env, export, args);
	else if (!(ft_strncmp(args[0], "echo", 5)) \
			|| !(ft_strncmp(args[0], "ECHO", 5)))
		g_exit_status = execute_echo(args, (*cmd)->fd_out);
	else if (!(ft_strncmp(args[0], "exit", 5)))
		g_exit_status = execute_exit(args);
	free_split(args);
}

void	start_execution(t_env **env, t_cmd **cmd, t_env **export)
{
	t_cmd	*temp;

	if (!*cmd)
		return ;
	temp = *cmd;
	if (temp->word->token == BUILTIN && !temp->next)
		execute_builtins(env, cmd, export);
	else
		exec_pipes(env, cmd, export);
}

void	read_phase(t_data *data, t_env **env, t_env **export, t_cmd **cmd)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	data->line = readline("\x1b[31m Minishell|🐚>: \x1b[0m");
	if (!data->line)
	{
		write (1, "\x1b[31m Minishell|🐚>: \x1b[0mexit\n", 33);
		exit(0);
	}
	add_history(data->line);
	while (data->line[i] && data->line[i] == ' ')
		i++;
	if (data->line[i] != '\0')
		k = parse(cmd, data->line, *export);
	if(!k)
		start_execution(env, cmd, export);
	free_cmd(cmd);
	free(data->line);
}

int	main(int ac, char **av, char **environ)
{
	t_env	*env;
	t_env	*export;
	t_data	data;
	t_cmd	*cmd;

	(void)av;
	env = NULL;
	export = NULL;
	cmd = NULL;
	if (ac != 1)
		return (1);
	fill_envlist(&env, &export, &data, environ);
	shell_signals();
	while (1)
		read_phase(&data, &env, &export, &cmd);
}
