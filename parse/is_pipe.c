/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 16:55:49 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/26 16:23:15 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	is_pipe(char *str, int is_red)
{
	int	is_valid;

	is_valid = 1;
	while (*str && *str == ' ')
		str++;
	if (*str == '|')
		return (is_valid);
	while (*str)
	{
		if (*str == '|' && !is_red)
		{
			if (is_valid == -1)
				return (-1);
			is_valid = -1;
		}
		else if (*str != ' ')
			is_valid = 0;
		if (*str == '>' || *str == '<')
			is_red = 1;
		else if (*str != ' ' && *str != '|')
			is_red = 0;
		str++;
	}
	return (is_valid);
}

int	check_pipe(int rslt)
{
	if (rslt)
	{
		rslt > 0 && write(2, "bash: syntax error near unexpected token `|'\n",
			ft_strlen("bash: syntax error near unexpected token `|'\n"));
		rslt < 0 && write(2, "bash: syntax error \n",
			ft_strlen("bash: syntax error '\n"));
		g_var.exit_status = 1;
		return (1);
	}
	return (0);
}

char	*dunder(char *s)
{
	char	*pt;

	pt = ft_itoa(g_var.exit_status);
	s = ft_join(s, pt, 0, ft_strlen(pt));
	free(pt);
	return (s);
}
