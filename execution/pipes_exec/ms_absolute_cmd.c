/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_absolute_cmd.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/21 17:52:35 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/21 19:50:33 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*is_path_valid(char *path)
{
	char	*result;

	if (!access(path, F_OK) && !access(path, X_OK))
	{
		result = ft_strdup(path);
		return (result);
	}
	exit (g_exit_status = 127);
}
