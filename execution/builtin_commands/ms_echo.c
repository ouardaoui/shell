/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 14:04:17 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 18:14:32 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fork_echo(char **args, int fd)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
	{
		perror("Fork");
		return (1);
	}
	else if (pid == 0)
		exit (execute_echo(args, fd));
	else
		wait(NULL);
	return (0);
}

int	check_echo_flag(char *str)
{
	int	i;

	i = 0;
	if (str[i++] != '-')
		return (1);
	while (str[i])
	{
		if (str[i] != 'n')
			return (1);
		i++;
	}
	return (0);
}

int	execute_echo(char **args, int fd)
{
	int	i;
	int	flag;

	i = 1;
	flag = 0;
	while (args[i])
	{
		if (check_echo_flag(args[i]) == 1)
			break ;
		else
			flag = 1;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i++], fd);
		if (args[i])
			ft_putstr_fd(" ", fd);
	}
	if (flag == 0)
		ft_putstr_fd("\n", fd);
	return (g_var.exit_status = 0);
}
