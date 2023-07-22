/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/13 22:16:01 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 00:16:38 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int is_quote(char *str)
{
	int state; 
	int s_state;

	state = 0;
	s_state = 0;
	while(*str) 
	{
		if(*str == '"' && !state && !s_state)  
			state = 1;
		else if(*str == '"' && state == 1)
			state =0; 
		if(*str == '\'' && !s_state  && !state)
			s_state = 1;
		else if(*str == '\'' && s_state)
			s_state = 0;
		str++;
	}
	return state  + s_state; 	
}

int is_pipe(char *str)
{
	int is_valid;
	int is_red;

	is_valid = 1;
	is_red = 0;
	while(*str && *str == ' ')
		str++;
	if(*str == '|')
		return (is_valid);
	while(*str)
	{
		if(*str == '|' && !is_red)
		{
			if(is_valid == -1)
				return -1;
			is_valid = -1;
		}
		else if(*str != ' ')
			is_valid = 0;
		if(*str == '>' || *str  == '<')
			is_red = 1;
		else if(*str != ' '  &&  *str!= '|')
			is_red = 0;
		str++;
	}
	return is_valid;
}
int ft_alloc_cmd(t_cmd **cmd)
{
	*cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if(!*cmd)
		return 1;
	(*cmd)->next = NULL;
	(*cmd)->word = NULL;
	return 0;
}

int  ft_create_list_cmd(char *str, t_cmd **cmd_line)
{
	int start;
	int end;
	int len;
	char *string;
	t_cmd *node;
	t_e_token quote;

	start = 0;
	end = 0;
	quote = ARG;
	while(str[end])
	{
		if(ft_alloc_cmd(&node))
			return 1;	
		while(str[end] != '\0' )
		{
			if(quote == ARG && str[end] == '|')
				break;
			if(str[end] == '"' && quote == ARG )
				quote =  IN_D_QUOTE ;
			else if(str[end] == '\'' && quote == ARG)
					quote = IN_QUOTE;
			else if(str[end] == '"' && quote == IN_D_QUOTE)
				quote = ARG;
			else if(str[end] == '\'' && quote == IN_QUOTE)
				quote = ARG;
			end++;
		}
		len = end - start;
		string = ft_substr(str,start, len);
		if(!string)
			return 1;
		node->string = string;
		node->fd = 0;
		node->fd_out = 1;
		if(str[end] == '|')
			end++;
		start = end;
		ft_add_end(cmd_line,node);
	}
	return 0;
}

int red_handle(t_cmd **cmd_line,char *str)
{
	t_cmd *node;
	t_w_token *word;
	t_e_token type;
	int handler;

	node = *cmd_line;
	handler = 0;
	while(node)
	{
		word = node->word;
		while(word)
		{
			
			if(!handler &&  is_red(word->token))
			{
				type = word->token;
				handler = 1;
			}
			else if(handler && is_red(word->token))
				return (print_error(word->token, 0));
			else if(handler  && word->string && word->string[0] != '\0')
			{
				word->token = update_token(type);	
				handler  = 0;
			}
			word = word->next;
		}
		if(handler && ft_strchr(str,'|'))
				return(print_error(0, 2));
		else if(handler && !node->next)
				return (print_error(0, 1));
		node = node->next;
	}
	return 0;	
}

int red_update(t_cmd **cmd)
{
	t_cmd *node;	

	node = *cmd;
	while(node)
	{
		if(!ft_strcmp(node->word->string,"<"))
		{
			write(2,"bash: No such file or directory\n",ft_strlen("bash: No such file or directory\n"))	;
			return 1;
		}
	node = node->next;
	}
	return 0;
}

int check_tree(t_cmd **cmd_line)
{
	t_cmd *cmd;
	t_w_token *node;

	cmd = *cmd_line;
	while(cmd)
	{
		node = cmd->word;
		while(node)
		{
			if(node->token == REDIRECTION)
				return 1;
		node = node->next;
		}
		cmd = cmd->next;
	}
	return 0;
}

int handle_single_quote(t_w_token *word,char c)
{
	char *str;
	int i;
	int len;

	len = ft_strlen(word->string);
	if(len < 2)
		return 1;
	str = (char *)malloc(sizeof(char ) *(len - 2 + 1));
	if(!str)
		return 1;
	i = 1;
	while( word->string[i] != c && word->string[i])
	{
		str[i - 1] = word->string[i];
		i++;
	}
	str[i - 1] = '\0'; 
	free(word->string);
	word->string = str;
	return 0;
}

int ft_expand(t_w_token *word, t_env *export)
{
	int k;

	k = 0;
	while(word)
	{
		if(word->token == DELIMITER)
		{
				if(word->string[0] == '\'')
					k = handle_single_quote(word, '\'');
				else if(word->string[0] == '"')
					k = handle_single_quote(word,'"');
				if(k)
					return 1;
		}
		else if(word->string[0] == '\'')
		{
			if(handle_single_quote(word,'\''))
				return 2;
		}
		else if(word->string[0] == '"')
		{
			if(handle_double_quote(word,export))
				return 3;
		}
		else if(word->token == ARG)
		{
			if(handle_arg(word, export))
			return 1;
		}
		word = word->next;
	}
	return 0;
}


int expand(t_cmd **cmd_line, t_env *export)
{
	t_cmd *node;
	int rslt;

	rslt = 0;
	node = *cmd_line;
	while(node)
	{
		rslt = ft_expand(node->word,export);
		if(rslt)
			return rslt;
		node = node->next;		
	}
	return rslt;
}

int parse(t_cmd **cmd_line,char *str,t_env *export)
{
	int rslt;
	//t_w_token *nodew;
	
	rslt = is_pipe(str);
	if( rslt)
	{
		rslt > 0 && write(2,"bash: syntax error near unexpected token `|'\n",ft_strlen("bash: syntax error near unexpected token `|'\n"));
		rslt < 0 && write(2,"bash: syntax error \n",ft_strlen("bash: syntax error '\n")); 
		g_exit_status = 1;
		return 1;
	}
	if(is_quote(str))
	{
		write(2,"unclosed quotes  \n",ft_strlen("unclosed quotes  \n"));
		return (1);
	}
	
	if(ft_create_list_cmd(str,cmd_line))
		return (1);
	(void )export;
	
	if(ft_create_tree(cmd_line))
		return (1);
	if(red_handle(cmd_line,str))
		return (1);
	
	if(check_tree(cmd_line))
	{
		write(2,"bash: syntax error \n",ft_strlen("bash: syntax error '\n")); 
		return (1);
	}
	if(red_update(cmd_line))
		return (1);
	
	if(expand(cmd_line, export))
		return (1);
	
	if(re_shap(cmd_line))
		return (1);

	ft_handle_shap(cmd_line);
	if(fd_redirection(cmd_line, export))
		return(1);	
		
	/*
	 while(*cmd_line)
	 {
	 	nodew = (*cmd_line)->word;
	
	 	while(nodew)
	 	{
	 		printf("%s\t%d\n", nodew->string, nodew->is_link);
	 		nodew = nodew->next;
	 	}
	 		(*cmd_line) = (*cmd_line)->next;
	 }
	*/
	return 0;
}
