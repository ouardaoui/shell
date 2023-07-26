/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mlagrini <mlagrini@1337.student.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:39:00 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/24 18:15:19 by mlagrini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

void	ft_if_dollar(char *str, int *i, int fd, t_env *env)
{
	char	*s;
	int		j;

	*i = *i + 1;
	j = *i;
	while ((str[*i] >= '0' && str[*i] <= '9') || ft_isalpha(str[*i]))
		*i = *i + 1;
	if (str[j] == '_')
		*i = *i + 1;
	s = ft_substr(str, j, *i - j);
	while (env)
	{
		if (!strcmp(env->var_name, s))
		{
			write(fd, env->content, ft_strlen(env->content));
			break ;
		}
		env = env->next;
	}
	free(s);
	*i = *i - 1;
}

void	handle_write(char *str, int fd, t_env *export)
{
	int		i;
	char	*s;
	t_env	*env;

	env = export;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] == '?')
		{
			s = ft_itoa(g_var.exit_status);
			write(fd, s, ft_strlen(s));
			free(s);
			i += 2;
		}
		else if (str[i] == '$' && str[i + 1] >= '0' && str[i + 1] <= '9')
			i += 2;
		else if (str[i] == '$')
			ft_if_dollar(str, &i, fd, env);
		else
			write(fd, str + i, 1);
		i++;
	}
}

char	*generate(void)
{
	int		i;
	int		bytes;
	int		x;
	char	*name;
	int		fd;

	i = 0;
	name = (char *)malloc(sizeof(char) * (11));
	fd = open("/dev/random", O_RDONLY);
	bytes = read(fd, name, 10);
	if (fd > 2)
		close(fd);
	while (i < 10)
	{
		x = name[i] % 26;
		if (x < 0)
			x = -x;
		name[i] = 'a' + x;
		i++;
	}
	name[10] = '\0';
	return (name);
}

char	*ft_herdoc(t_w_token *node, t_cmd *cmd, t_env *export)
{
	char	*str;
	char	*s;
	char	*k;

	s = NULL;
	k = generate();
	s = ft_strjoin("/tmp/", k);
	free(k);
	cmd->fd = open(s, O_CREAT | O_EXCL | O_RDWR, 0644);
	while (1)
	{
		str = readline(">");
		if (!str || !strcmp(node->string, str))
		{
			free(str);
			break ;
		}
		handle_write(str, cmd->fd, export);
		write(cmd->fd, "\n", 1);
		free(str);
	}
	if (g_var.her == 1)
		open("/dev/tty", O_RDONLY);
	return (s);
}

int	fd_redirection(t_cmd **cmd_line, t_env *export)
{
	t_cmd		*cmd;
	t_w_token	*node;

	cmd = *cmd_line;
	while (cmd)
	{
		node = cmd->word;
		while (node)
		{
			if (node->token > 9)
			{
				if (ft_handle_fd(node, cmd, export))
					return (1);
			}
			node = node->next;
		}
		cmd = cmd->next;
	}
	return (0);
}
