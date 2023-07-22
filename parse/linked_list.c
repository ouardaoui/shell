/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aouardao <aouardao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/14 01:15:39 by aouardao          #+#    #+#             */
/*   Updated: 2023/07/15 08:03:59 by aouardao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../execution/minishell.h"

void ft_add_end(t_cmd **head,t_cmd *node)
{
  t_cmd *tmp;

  tmp = *head;
  if(!*head)
    *head = node;
  else
  {
    while(tmp->next)
      tmp = tmp->next;
    tmp->next = node; 
  }
}	

void add_tree_end(t_w_token **head,t_w_token *node)
{
  t_w_token *tmp; 
  
  tmp = *head;
  if(!*head)
    *head = node;
  else
  {
    while(tmp->next)
      tmp = tmp->next;
    tmp->next = node; 
  }
}

void ft_free_word(t_w_token **head)
{
  t_w_token *tmp;

  while(*head)
  {
    tmp = (*head)->next; 
    if((*head)->string)
    {
      free((*head)->string) ;
      (*head)->string =NULL;
    }
    free(*head);
    *head = tmp;
  }
}

void ft_free_all(t_cmd **head)
{
  t_cmd *tmp;

  while(*head)
  {
    tmp = (*head)->next;
    if((*head)->string)
    {
      free((*head)->string) ;
      (*head)->string =NULL;
    }
    if((*head)->word)
      ft_free_word(&(*head)->word);
    free(*head);
    *head = tmp;
  } 
}

void ft_free_env(t_env **env)
{
  t_env *node;

  while(*env)
  {
    node = (*env)->next;
    if((*env)->content)
      free((*env)->content);
    if((*env)->var_name)
      free((*env)->var_name);
    if((*env)->variable)
      free((*env)->variable);
    free(*env);
    *env = node;
  }
}

void ft_free_t_data(t_data *data)
{
  /*if(data->line)
    free(data->line);
  if(data->curr_pwd)
    free(data->curr_pwd);
  if(data->new_pwd)
    free(data->new_pwd);
  */
  if(data->home_dir)
    free(data->home_dir);
  //if(data)
    //free(data);
}