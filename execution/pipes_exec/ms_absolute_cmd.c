/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_absolute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:52:35 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/24 18:14:32 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_command_error(char *str, char *err_msg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(" ", 2);
	ft_putstr_fd(err_msg, 2);
	ft_putstr_fd("\n", 2);
}

char	*is_path_valid(char *path)
{
	char	*result;

	if (!access(path, F_OK) && !access(path, X_OK))
	{
		result = ft_strdup(path);
		return (result);
	}
	print_command_error(path, strerror(errno));
	exit (g_var.exit_status = 127);
}
