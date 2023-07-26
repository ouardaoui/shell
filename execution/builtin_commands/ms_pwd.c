/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 13:21:41 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 18:14:32 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_pwd(char **args, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		return (1);
	}
	else if (pid == 0)
		exit (execute_pwd(args, fd));
	else
		wait(NULL);
	return (0);
}

int	execute_pwd(char **args, int fd)
{
	char	*curr_pwd;

	curr_pwd = malloc (PATH_MAX * sizeof(char));
	curr_pwd = getcwd(curr_pwd, PATH_MAX);
	if (args[1] && !ft_strncmp(args[1], "-", 1))
	{
		ft_putstr_fd("bash: pwd: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": invalid option\n", 2);
		free (curr_pwd);
		return (g_var.exit_status = 1);
	}
	if (curr_pwd)
	{
		ft_putstr_fd(curr_pwd, fd);
		ft_putstr_fd("\n", fd);
		free (curr_pwd);
		return (g_var.exit_status = 0);
	}
	perror("pwd");
	free (curr_pwd);
	return (g_var.exit_status = 1);
}
