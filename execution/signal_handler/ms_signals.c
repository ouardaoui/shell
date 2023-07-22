/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/09 11:49:12 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/22 21:28:01 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	int_handler(int num)
{
	(void)num;
	write (2, "\n", 1);
	//rl_replace_line("", 0);
	//rl_on_new_line();
	//rl_redisplay();
	g_exit_status = 1;
}

void	shell_signals(void)
{
	signal(SIGINT, int_handler);
	signal(SIGQUIT, SIG_IGN);
}
