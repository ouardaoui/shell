/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 02:39:00 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/23 00:13:20 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

void handle_write(char *str, int fd, t_env *export)
{
  int i;
  int j;
  char *s;
  t_env *env;
  
  env  = export;
  i = 0;
  while(str[i])
  {
    if(str[i] == '$' && str[i + 1] == '?' )
    {
      s = ft_itoa(g_exit_status);
      write(fd, s, ft_strlen(s));
      free(s);
      i += 2;
    }
    else if(str[i] == '$' && str[i + 1]  >='0' && str[i + 1] <= '9' ) 
      i += 2;     
    else if(str[i] == '$')
    {
      i++;
      j = i;
      while((str[i] >= '0' && str[i] <= '9') || ft_isalpha(str[i]) )
        i++;
      if(str[j] == '_')
        i++; 
      s = ft_substr(str,j, i - j); 
      while(env)
      {
        if(!strcmp(env->var_name, s))
        {
          write(fd,env->content, ft_strlen(env->content) );
          break;
        }
        env = env->next;
      }
      free(s);
      i--;
    }
    else 
      write(fd,str + i ,1);
    i++;
  }   
}

char* generate() {
	int i = 0;
  int bytes;
  int x;

    char* name = (char *)malloc(sizeof(char) * (11));

    int fd = open("/dev/random", O_RDONLY);

    bytes = read(fd, name, 10);
	
    close(fd);

    while(i < 10)
	{
        x = name[i] % 26;
        if(x < 0)
          x = -x ;
        name[i] = 'a' + x;
		i++;
	}
    name[10] = '\0';

    return name;
}

int ft_handle_fd(t_w_token *node, t_cmd *cmd, t_env *export)
{
  char *str; 
  char *s;
  char *k;

  s = NULL;
  if(node->token == OUTPUT_FILE)
  {
    cmd->fd_out= open(node->string, O_CREAT | O_RDWR , 0644);
    if(cmd->fd_out == -1)
      return -1;
  }
  if(node->token == APPEND_FILE)
  {
    cmd->fd_out = open(node->string, O_CREAT | O_RDWR | O_APPEND , 0644);
    if(cmd->fd_out == -1)
      return -1;
  }
  if(node->token == INPUT_FILE)
  {
    cmd->fd = open(node->string, O_RDONLY);
    if(cmd->fd == -1)
      return -1;
  }
  if(node->token == DELIMITER)
  {
    k = generate();
    s = ft_strjoin("/tmp/", k);
    free(k);
    cmd->fd = open(s, O_CREAT | O_EXCL | O_RDWR , 0644);
    while(1)
    {
      str = readline(">"); 
      if(!str)
        return 1;
      if(!strcmp(node->string, str))
      {
        free(str);
        break;
      }
      handle_write(str, cmd->fd, export);
      write(cmd->fd,"\n", 1);
      free(str);
    }
    close(cmd->fd);
    cmd->fd  = open(s,O_RDONLY);
    if(s)
    {
      unlink(s);
      free(s);
      s = NULL;
    }
  }
  return 0;
}




int fd_redirection(t_cmd **cmd_line, t_env *export)
{
  t_cmd *cmd;
  t_w_token *node;

  cmd = *cmd_line;
  while(cmd)
  {
    node = cmd->word;
    while(node)
    {
      if(node->token > 9)
      {
          if(ft_handle_fd(node, cmd, export))
            return 1;
      }
      node = node->next;
    }
    cmd = cmd->next;    
  }
  return 0;
}