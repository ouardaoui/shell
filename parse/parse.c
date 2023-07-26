/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:16:01 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/24 20:17:13 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	is_quote(char *str)
{
	int	state;
	int	s_state;

	state = 0;
	s_state = 0;
	while (*str)
	{
		if (*str == '"' && !state && !s_state)
			state = 1;
		else if (*str == '"' && state == 1)
			state = 0;
		if (*str == '\'' && !s_state && !state)
			s_state = 1;
		else if (*str == '\'' && s_state)
			s_state = 0;
		str++;
	}
	return (state + s_state);
}

int	red_update(t_cmd **cmd)
{
	t_cmd	*node;

	node = *cmd;
	while (node)
	{
		if (!ft_strcmp(node->word->string, "<"))
		{
			write(2, "bash: No such file or directory\n",
				ft_strlen("bash: No such file or directory\n"));
			return (1);
		}
		node = node->next;
	}
	return (0);
}

int	check_tree(t_cmd **cmd_line)
{
	t_cmd		*cmd;
	t_w_token	*node;

	cmd = *cmd_line;
	while (cmd)
	{
		node = cmd->word;
		while (node)
		{
			if (node->token == REDIRECTION)
				return (1);
			node = node->next;
		}
		cmd = cmd->next;
	}
	return (0);
}

int	parse(t_cmd **cmd_line, char *str, t_env *export)
{
	int	rslt;

	rslt = is_pipe(str, 0);
	if (check_pipe(rslt))
		return (1);
	if (is_quote(str))
	{
		write(2, "unclosed quotes  \n", ft_strlen("unclosed quotes  \n"));
		return (1);
	}
	if (ft_create_list_cmd(str, cmd_line) || ft_create_tree(cmd_line)
		|| red_handle(cmd_line, str, 0))
		return (1);
	if (check_tree(cmd_line))
	{
		write(2, "bash: syntax error \n", ft_strlen("bash: syntax error '\n"));
		return (1);
	}
	if (red_update(cmd_line) || expand(cmd_line, export, 0) || re_shap(cmd_line)
		|| red_handle(cmd_line, str, 0))
		return (1);
	ft_handle_shap(cmd_line);
	if (fd_redirection(cmd_line, export))
		return (1);
	return (0);
}
