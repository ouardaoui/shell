/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 21:17:40 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 00:12:37 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H
#include "../execution/minishell.h"

typedef enum s_enum_token {
  ARG,
  BUILTIN, 
  IN_QUOTE, // ' '
  IN_D_QUOTE, // " "
  REDIRECTION, // 0 >>>
  RED_OUTPUT, // > 
  APPEND_OUTPUT, //>>
  RED_INPUT,  //<
  HER_DOC,  // <<
  WHITE_SPACE, //0
  OUTPUT_FILE, 
  APPEND_FILE, 
  INPUT_FILE, 
  DELIMITER, 
} t_e_token;

typedef struct s_word_token 
{
  char *string;
  t_e_token token;
  int is_link;
  int is_expand;
  struct s_word_token *next; 
} t_w_token;

typedef struct s_cmd 
{
  char *string;
  t_w_token *word;
  struct s_cmd *next;
  int fd;
  int fd_out;
  char  *path;
} t_cmd;


void ft_add_end(t_cmd **head,t_cmd *node);
void add_tree_end(t_w_token **head,t_w_token *node);
int ft_create_tree(t_cmd **cmd_line);
int ft_split_word(t_cmd *node);
int is_red(t_e_token type);
t_e_token update_token(t_e_token type);
int print_error(t_e_token type, int key);
void ft_free_word(t_w_token **node);
void ft_free_all(t_cmd **head);
char *ft_join(char *str, char *word, int start, int end );
// char *ft_join_dollar(char *str, char *word,int len,  t_env *export);
// int handle_double_quote(t_w_token *word, t_env *export);
// int handle_arg(t_w_token *word, t_env *export);
int re_shap(t_cmd ** cmd);
int red_handle(t_cmd **cmd_line,char *str);
int is_builtin(char *str);
void ft_handle_shap(t_cmd **cmd);

#endif