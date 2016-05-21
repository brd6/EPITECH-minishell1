/*
** alias_handler.c for alias_handler in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Fri Jan 22 01:59:55 2016 Berdrigue BONGOLO BETO
** Last update Sat Jan 23 23:03:54 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

char		*get_corr_alias(t_mysh *mysh, char *alias)
{
  t_list	*curr;
  char		*curr_key;
  char		*curr_value;
  char		*first_val_al;

  curr = mysh->alias;
  while (curr != NULL)
    {
      curr_key = get_env_key(curr->data);
      curr_value = get_env_value(curr->data);
      first_val_al = get_first_value_arg(alias);
      if (!my_strcmp(curr_key, first_val_al) &&
	  my_strstr(alias, curr_value) == NULL)
	{
	  alias = my_str_replace(first_val_al, curr_value, alias, -1);
	  return (get_corr_alias(mysh, alias));
	  free(first_val_al);
	}
      free(curr_key);
      free(curr_value);
      curr = curr->next;
    }
  return (alias);
}

char		*alias_reverse_cmd(t_mysh *mysh, char *alias)
{
  char		*first_val;
  char		*alias_val;
  char		*val;

  if (!mysh->bonus || alias == NULL || alias[0] == 0 ||
      mysh->alias == NULL || !env_key_exist(mysh->alias, alias))
    return (alias);
  alias_val = key_to_value(mysh->alias, alias);
  first_val = get_first_value_arg(alias_val);
  if (env_key_exist(mysh->alias, first_val))
    {
      val = get_corr_alias(mysh, alias_val);
    }
  else
    return (alias_val);
  return (val);
}
