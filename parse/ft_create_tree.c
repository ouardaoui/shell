/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_create_tree.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/15 15:47:13 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 00:11:15 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

t_e_token ft_update_white_space(int *i,int *j,char *str)
{
	while(str[*i] == ' ' || str[*i] == '\t')
	{
		(*i)++;
		(*j)++;
	}
  return WHITE_SPACE;
}


t_e_token ft_update_quote(int *i, char *str, char c)
{
  (*i)++;
	while(str[*i] && str[*i] != c)		
		(*i)++;
  (*i)++;
		if(c == '"')
			return IN_D_QUOTE;
		return IN_QUOTE;
}

int is_builtin(char *str)
{
	if(!ft_strcmp("echo",str))
			return 1;
			if(!ft_strcmp("cd",str))
			return 1;
			if(!ft_strcmp("export",str))
			return 1;
			if(!ft_strcmp("pwd",str))
			return 1;
		if(!ft_strcmp("unset",str))
			return 1;
		if(!ft_strcmp("env",str))
			return 1;
		if(!ft_strcmp("exit",str))
			return 1;
		return 0;	
	}

int ft_create_node(t_cmd *cmd, int s,int e, int quote)
{
	t_w_token *node;
	
	node  = (t_w_token *)malloc(sizeof(t_w_token));
	if(!node)
		return 1;
	node->string = ft_substr(cmd->string,s,e-s);
	if(!node->string)
		return 1;
	node->token = quote;
	node->is_expand = 0;
	node->next = NULL;
	if(cmd->string[e] == ' ' || cmd->string[e] == '\0' || cmd->string[e] == '>' || cmd->string[e] == '<' || cmd->string[e -1] == '>' || cmd->string[e - 1] == '<' )
		node->is_link = 0;
	else 
		node->is_link = 1;
	add_tree_end(&(*cmd).word,node);
	return 0;
}

t_e_token ft_update_redir(int *i, char *str, char c)
{
	int len; 

	len = (*i)++;
	while(str[*i] && str[*i] == c)		
		(*i)++;
	len = *i - len;
	if(len == 1 && c == '>')
		return RED_OUTPUT;
	if(len == 2 && c == '>')
		return APPEND_OUTPUT;
	if(len == 1 && c == '<')
		return RED_INPUT;
	if(len == 2 && c == '<')
		return HER_DOC;	
	return  REDIRECTION;
}

t_e_token ft_update_arg(int *i, char *str)
{
	while(str[*i ] && str[*i] != ' ' && str[*i] != '\t' && str[*i] != '\'' && str[*i] != '"' &&  str[*i] != '<' &&  str[*i] != '>')		
		(*i)++;
	return  ARG;
}

int ft_split_word(t_cmd *node)
{
	char *str;
	int len;
	int end; 
	int start; 
	int quote;

	str =	 node->string;
	end = 0;
	start = 0;
	len = ft_strlen(str);
	while(end < len && str[end] )
	{
		quote = ARG;
		if(str[end] == ' ' )
    {
			quote = ft_update_white_space(&start, &end, str);
    } 
		else if(str[end] == '"' || str[end] == '\'')
    {
			quote = ft_update_quote(&end, str, str[end]);
    } 
    else if(str[end] == '<' || str[end] == '>')
    {
     quote = ft_update_redir(&end, str, str[end]);
    }
    else
      quote = ft_update_arg(&end,str);
		if(quote != WHITE_SPACE &&  ft_create_node(node,start,end, quote))
			return 1; 
		start = end;
	}
	return 0;
}

int ft_create_tree(t_cmd **cmd_line)
{
	t_cmd *node;

	node = *cmd_line;
	while(node)
	{
		if(ft_split_word(node))
			return 1;
		node = node->next;
	}	
	return 0;	
}