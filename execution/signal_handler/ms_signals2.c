/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/24 19:05:05 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 20:36:20 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sigint_handler(int num)
{
	if (num == SIGINT)
		exit(g_var.exit_status = 130);
}

void	sigquit_handler(int num)
{
	if (num == SIGQUIT)
	{
		ft_putstr_fd("Quit\n", 2);
		exit(g_var.exit_status = 131);
	}
}

void	cmd_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
