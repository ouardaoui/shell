/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:46:12 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 18:53:12 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	exit_return(char *value, int *flag)
{
	unsigned long long	result;
	int					i;
	int					sign;

	i = 0;
	result = 0;
	sign = 1;
	while (value[i] == 32 || (value[i] >= 9 && value[i] <= 13))
		i++;
	if (value[i] == '-' || value[i] == '+')
	{
		if (value[i] == '-')
			sign *= -1;
		i++;
	}
	if (!ft_isdigit(value[i]))
		return (*flag = 1, -1);
	while (value[i] >= '0' && value[i] <= '9')
		result = result * 10 + value[i++] - '0';
	if (value[i] || result > LLONG_MAX)
		return (*flag = 1, -1);
	return ((long long)(result * sign) % 256);
}

int	execute_exit(char **args)
{
	int	flag;

	flag = 0;
	if (!args[1])
		exit(g_var.exit_status);
	if (exit_return(args[1], &flag) == -1 && flag == 1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	else if (args[2])
	{
		ft_putstr_fd("minishell: exit: too many arguments\n", 2);
		return (g_var.exit_status = 1);
	}
	exit(exit_return(args[1], &flag));
}
