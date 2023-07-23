/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/23 19:05:04 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 20:21:00 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	ft_fd_out(t_w_token *node, t_cmd *cmd)
{
	if (node->token == OUTPUT_FILE)
	{
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd->fd_out = open(node->string, O_CREAT | O_RDWR, 0644);
		if (cmd->fd_out == -1)
			return (1);
	}
	if (node->token == APPEND_FILE)
	{
		if (cmd->fd_out > 2)
			close(cmd->fd_out);
		cmd->fd_out = open(node->string, O_CREAT | O_RDWR | O_APPEND, 0644);
		if (cmd->fd_out == -1)
			return (1);
	}
	return (0);
}

int	ft_file(char *s, int fd)
{
	int	f;

	f = -1;
	close(fd);
	f = open(s, O_RDONLY);
	if (s)
	{
		free(s);
		unlink(s);
		s = NULL;
	}
	return (f);
}

int	ft_handle_fd(t_w_token *node, t_cmd *cmd, t_env *export)
{
	char	*s;

	if (ft_fd_out(node, cmd))
		return (-1);
	if (node->token == INPUT_FILE)
	{
		if (cmd->fd > 2)
			close(cmd->fd);
		cmd->fd = open(node->string, O_RDONLY);
		if (cmd->fd == -1)
			return (-1);
	}
	if (node->token == DELIMITER)
	{
		if (cmd->fd > 2)
			close(cmd->fd);
		s = ft_herdoc(node, cmd, export);
		cmd->fd = ft_file(s, cmd->fd);
		if (cmd->fd == -1)
			return (-1);
	}
	return (0);
}
