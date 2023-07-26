/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:49:12 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 20:36:05 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	int_handler(int num)
{
	(void)num;
	if (g_var.her == 0)
		write (2, "\n", 1);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	//rl_redisplay();
	g_var.exit_status = 1;
}

void	handler(int num)
{
	if (num == 2)
	{
		g_var.her = 1;
		g_var.exit_status = 1;
		close(0);
	}
}

void	shell_signals(void)
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	her_signals(void)
{
	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
}
