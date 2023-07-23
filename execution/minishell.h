/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/10 12:46:10 by mlagrini          #+#    #+#             */
/*   Updated: 2023/07/23 23:51:03 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <dirent.h>
# include <string.h>
# include <termios.h>
# include <termcap.h>
# include "42_libft/libft.h"
# include <limits.h>
# include "../parse/parse.h"

// # define TRUE 1
// # define FALSE 0

typedef struct s_data
{
	char	*line;
	char	*curr_pwd;
	char	*new_pwd;
	char	*home_dir;
	int		index;
	int		return_value;
	int		exit_status;
}				t_data;

typedef struct s_env
{
	char			*variable;
	char			*var_name;
	char			*content;
	int				checker;
	struct s_env	*next;
}				t_env;

int	g_exit_status;

void	fill_envlist(t_env **env, t_env **export, t_data *data, char **environ);
void	add_env_element(t_env **node, char *var);
void	create_envnode(t_env **head, char *name, char *var, char *env_var);
// void	execute_env(t_env *env);
// void	execute_pwd(t_data *data);
void	free_nodes_content(t_env **node);
int		find_env_var(t_env **env, char *var_name);
int		update_env_var(t_env **env, char *name, char *content);
// int		execute_cd(t_env **env, t_env **export, t_data *data);
// void	execute_export(t_env **env, t_env **export, t_data *data);
void	free_split(char **split);
void	free_the_whole_node(t_env **node);
// void	execute_unset(t_env **env, t_env **export, t_data *data);
int		execve_example(t_env **env, char **args);
char	**equal_split(char *var);
// void	execute_echo(t_data *data);
// void	execute_exit(t_data *data);
char	*find_path(char **paths, char **args);
void	execute_commands(t_env **env, char **args);
void	int_handler(int num);
void	shell_signals(void);
char	**args_array(t_cmd **cmd);
void	free_list(t_env **list);
void	free_cmd(t_cmd **head);
int		commands_counter(t_cmd **cmd);
void	print_list(t_cmd *cmd);
// int		execute_pipes(t_env **env, t_cmd **cmd, int cmd_nbr, int **fd);
int		is_path_env(t_env **env, char ***paths, char *arg);
int		does_path_exist(char **path, char **paths_arr, char **args);
int		pipes_creation(t_env **env, t_cmd **cmd, int cmd_nbr);
// int		exec_pipes(t_env **env, t_cmd **cmd);
// int		execute_env(t_env *env, char **args);
// int		execute_pwd(char **args);
int		execute_cd(t_env **env, t_env **export, char **args);
// int		execute_export(t_env **env, t_env **export, char **args);
// int		execute_echo(char **args);
int		execute_exit(char **args);
int		execute_unset(t_env **env, t_env **export, char **args);
int		check_echo_flag(char *str);
int		execute_env(t_env *env, char **args, int fd);
int		execute_pwd(char **args, int fd);
int		execute_export(t_env **env, t_env **export, char **args, int fd);
int		execute_echo(char **args, int fd);
//
char	*ft_join_dollar(char *str, char *word, int len, t_env *export);
int		handle_double_quote(t_w_token *word, t_env *export);
int		handle_arg(t_w_token *word, t_env *export);
int		parse(t_cmd **cmd_line, char *str, t_env *export);
//
/*forking builtings*/
int		fork_pwd(char **args, int fd);
int		fork_echo(char **args, int fd);
int		fork_env(t_env *env, char **args, int fd);
int		exec_pipes(t_env **env, t_cmd **cmd, t_env **export);
void	execute_builtins(t_env **env, t_cmd **cmd, t_env **export);
/**/
void	swap_env(t_env **a, t_env **b);
void	sort_env(t_env **env);
char	*is_path_valid(char *path);

int fd_redirection(t_cmd **cmd_line, t_env *export);
int	expand(t_cmd **cmd_line, t_env *export, int rslt);
int ft_handle_fd(t_w_token *node, t_cmd *cmd, t_env *export);
char *ft_herdoc(t_w_token *node,t_cmd *cmd, t_env *export);
char *ft_loopfct(t_w_token *word, int *end , char *str, t_env *export);
char *ft_loopfct_double(t_w_token *word, int *end , char *str, t_env *export);

#endif