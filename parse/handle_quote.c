/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/15 11:20:47 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 00:11:53 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

int ft_init_str(char **str)
{
	*str = (char *)malloc(sizeof(char) * 1);
	if(!*str)
		return 1;
	(*str)[0] = '\0';
	return 0;
}

int is_alph_num(char c)
{
	if(c >=  '0' && c <= '9')
		return 1;
	if(c >= 'A' && c <= 'Z')
		return 1;
	if(c >= 'a' && c <= 'z')
		return 1;
	if(c == '_')
		return 1;
	return 0;
}

int handle_double_quote(t_w_token *word, t_env *export)
{
 int start;
 int end;
 char *str;
 char *pt;

start = 1;
end = 1;
if(ft_init_str(&str))
	return 1;
if(ft_strlen(word->string) == 2)
{
	free(word->string);
	word->string = str;
	return 0;
}
while(word->string[end] && word->string[end] != '"') 
{
			while(word->string[end] && word->string[end ] != '$'   && word->string[end] !=  '"')
				end++; 
			if(end  != start)
			{
				str = ft_join(str, word->string, start, end);
				if(!str)
					return 1;
				start = end;
			}
			if(word->string[end] =='$')
			{
			word->is_expand = 1;
			end++;
			start++;
			if(word->string[end] == '?')
			{
				end++;
				pt = ft_itoa(g_exit_status);
				str = ft_join(str,pt, 0, ft_strlen(pt));
				free(pt);
			}
			else if(word->string[end] > '0' && word->string[end] < '9' )
			{
				end++;
				start++;
				str  = ft_join_dollar(str, word->string + start , end -start , export);
			}
			else
			{
			while(word->string[end]  && is_alph_num(word->string[end]) )
				end++;
			str = ft_join_dollar(str, word->string +start,end - start,  export);
			}
			start = end;
			}
}
free(word->string);
word->string = str;
return 0;
}

int handle_arg(t_w_token *word, t_env *export)
{
 int start;
 int end;
 char *str;
 char *pt;

start = 0;
end = 0;
if(ft_init_str(&str))
	return 1;
if(!ft_strlen(word->string))
{
	free(word->string);
	word->string = str;
	return 0;
}
while(word->string[end]) 
{
			while(word->string[end] && word->string[end ] != '$' )
				end++; 
			if(end  != start)
			{
				str = ft_join(str, word->string, start, end);
				if(!str)
					return 1;
				start = end;
			}
			if(word->string[end] =='$')
			{
			word->is_expand = 1;
			start++;
			end++;
			if(word->string[end] == '?')
			{
				end++;
				pt = ft_itoa(g_exit_status);
				str = ft_join(str,pt, 0, ft_strlen(pt));
				free(pt);
			}
			if(word->string[end] > '0' && word->string[end] < '9')
			{
				end++;
				str = ft_join_dollar(str, word->string +start, end -start, export);
			}
			else
			{
			while(word->string[end] &&  is_alph_num(word->string[end]) )
				end++;
			str = ft_join_dollar(str, word->string +start,end - start,  export);	
			}
			start = end;
			}
}
free(word->string);
word->string = str;
return 0;
}