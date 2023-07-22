/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 21:46:12 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/18 17:00:19 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

long long	exit_return(char *value)
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
		return (-1);
	while (value[i] >= '0' && value[i] <= '9')
		result = result * 10 + value[i++] - '0';
	if (value[i] || result > LLONG_MAX)
		return (-1);
	return ((long long)(result * sign) % 256);
}

int	execute_exit(char **args)
{
	if (!args[1])
		exit(0);
	else if (args[2])
	{
		ft_putstr_fd("exit\nbash: exit: too many arguments\n", 2);
		return (g_exit_status = 1);
	}
	if (exit_return(args[1]) == -1)
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(args[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	exit(exit_return(args[1]));
}
