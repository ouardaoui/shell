/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:17:40 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/26 16:10:59 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
# include "../execution/minishell.h"

typedef enum s_enum_token
{
	ARG,
	BUILTIN,
	IN_QUOTE,
	IN_D_QUOTE,
	REDIRECTION,
	RED_OUTPUT,
	APPEND_OUTPUT,
	RED_INPUT,
	HER_DOC,
	WHITE_SPACE,
	OUTPUT_FILE,
	APPEND_FILE,
	INPUT_FILE,
	DELIMITER,
}						t_e_token;

typedef struct s_word_token
{
	char				*string;
	t_e_token			token;
	int					is_link;
	int					is_expand;
	struct s_word_token	*next;
}						t_w_token;

typedef struct s_cmd
{
	char				*string;
	t_w_token			*word;
	struct s_cmd		*next;
	int					fd;
	int					fd_out;
	char				*path;
}						t_cmd;

void					ft_add_end(t_cmd **head, t_cmd *node);
void					add_tree_end(t_w_token **head, t_w_token *node);
int						ft_create_tree(t_cmd **cmd_line);
int						is_red(t_e_token type);
t_e_token				update_token(t_e_token type);
int						print_error(t_e_token type, int key);
void					ft_free_word(t_w_token **node);
void					ft_free_all(t_cmd **head);
char					*ft_join(char *str, char *word, int start, int end);
int						re_shap(t_cmd **cmd);
int						is_builtin(char *str);
void					ft_handle_shap(t_cmd **cmd);
int						is_pipe(char *str, int is_red);
int						check_pipe(int rslt);
int						ft_create_list_cmd(char *str, t_cmd **cmd_line);
t_e_token				ft_update_arg(int *i, char *str);
t_e_token				ft_update_redir(int *i, char *str, char c);
int						is_builtin(char *str);
t_e_token				ft_update_quote(int *i, char *str, char c);
int						red_handle(t_cmd **cmd_line, char *str, int handler);
int						ft_mini_expand(t_w_token *word, int *start, int *end,
							char *str);
char					*ft_chunk(t_w_token *word, int *start, int *end,
							char *str);
void					ft_chunk_two(t_w_token *word, int *start, int *end);
int						ft_check(t_w_token *word, char *str, int i);
int						is_alph_num(char c);
char					*ft_chunk_double(t_w_token *word, int *start, int *end,
							char *str);
char					*dunder(char *s);

#endif