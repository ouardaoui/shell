/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utiles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/18 02:12:21 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 20:39:42 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int	is_red(t_e_token type)
{
	if (type == RED_OUTPUT || type == APPEND_OUTPUT || type == RED_INPUT
		|| type == HER_DOC)
		return (1);
	return (0);
}

t_e_token	update_token(t_e_token type)
{
	if (type == RED_OUTPUT)
		return (OUTPUT_FILE);
	if (type == APPEND_OUTPUT)
		return (APPEND_FILE);
	if (type == RED_INPUT)
		return (INPUT_FILE);
	if (type == HER_DOC)
		return (DELIMITER);
	return (ARG);
}

int	print_error(t_e_token type, int key)
{
	write(2, "bash: syntax error near unexpected token ",
		ft_strlen("bash: syntax error near unexpected token "));
	if (type == RED_OUTPUT && !key)
		write(2, "\">\"\n", ft_strlen("\">\"\n"));
	if (type == APPEND_OUTPUT && !key)
		write(2, "\">>\"\n", ft_strlen("\">>\"\n"));
	if (type == RED_INPUT && !key)
		write(2, "\"<\"\n", ft_strlen("\"<\"\n"));
	if (type == HER_DOC && !key)
		write(2, "\"<<\"\n", ft_strlen("\"<<\"\n"));
	if (key == 1)
		write(2, "`newline'\n", ft_strlen("`newline'\n"));
	if (key == 2)
		write(2, "`|'\n", ft_strlen("`|'\n"));
	return (1);
}

t_e_token	ft_update_quote(int *i, char *str, char c)
{
	(*i)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
	(*i)++;
	if (c == '"')
		return (IN_D_QUOTE);
	return (IN_QUOTE);
}

int	is_builtin(char *str)
{
	if (!ft_strcmp("echo", str))
		return (1);
	if (!ft_strcmp("cd", str))
		return (1);
	if (!ft_strcmp("export", str))
		return (1);
	if (!ft_strcmp("pwd", str))
		return (1);
	if (!ft_strcmp("unset", str))
		return (1);
	if (!ft_strcmp("env", str))
		return (1);
	if (!ft_strcmp("exit", str))
		return (1);
	return (0);
}
