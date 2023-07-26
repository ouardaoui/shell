/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 13:14:03 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/25 13:25:29 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_valid_export(char *arg, char *cmd)
{
	int	len;

	len = ft_strlen(arg) - 1;
	if ((arg[0] != '_' && !ft_isalpha(arg[0])) || \
		(!ft_isalnum(arg[len]) && arg[len] != '_'))
	{
		ft_putstr_fd(cmd, 2);
		ft_putstr_fd(": '", 2);
		ft_putstr_fd(arg, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
		return (2);
	}
	return (0);
}
