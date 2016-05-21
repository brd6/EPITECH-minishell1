/*
** config_util3.c for config_util3 in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Mon Jan 18 00:06:45 2016 Berdrigue BONGOLO BETO
** Last update Fri Jan 22 03:54:16 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

char		*get_first_value_arg(char *value)
{
  char		*arg1;
  int		i;

  if ((arg1 = malloc(sizeof(*arg1) * (my_strlen(value)) + 1)) == NULL)
    return (NULL);
  i = 0;
  while (value[i] && (value[i] != ' ' && value[i] != '\t'))
    {
      arg1[i] = value[i];
      i++;
    }
  arg1[i] = 0;
  return (arg1);
}

void		replace_alias_cond(char *value_arg1, char *curr_value,
				   t_list *curr_alias)
{
  char		*alias_key;
  char		*alias_value;
  char		*good_value;

  alias_value = get_env_value(curr_alias->data);
  alias_key = get_env_key(curr_alias->data);
  good_value = my_str_replace(value_arg1, curr_value, alias_value, -1);
  curr_alias->data = concat_two_str(alias_key, good_value, "=");
  free(alias_value);
  free(alias_key);
  free(good_value);
}

void		replace_alias(char *value_arg1, t_list *curr_alias)
{
  t_list	*curr;
  char		*curr_key;
  char		*curr_value;

  curr = curr_alias;
  while (curr != NULL)
    {
      curr_key = get_env_key(curr->data);
      curr_value = get_env_value(curr->data);
      if (!my_strcmp(get_env_key(curr->data), value_arg1) &&
	  my_strstr(get_env_value(curr_alias->data), curr_value) == NULL)
	{
	  replace_alias_cond(value_arg1, curr_value, curr_alias);
	}
      free(curr_key);
      free(curr_value);
      curr = curr->next;
    }
}

void		replace_alias_var(t_list *curr, t_mysh *mysh)
{
  char		*var;
  char		*key;
  char		*first_value;

  var = my_strstr(curr->data, "$");
  if (var != NULL)
    {
      first_value = get_first_value_arg(var);
      key = key_to_value(mysh->my_env, var + 1);
      if (env_key_exist(mysh->my_env, var + 1))
	curr->data = my_str_replace(var, key, curr->data, -1);
      free(first_value);
      free(key);
    }
}

int		update_alias_config(t_mysh *mysh)
{
  t_list	*curr;
  char		*value_arg1;
  char		*value;

    curr = mysh->alias;
    while (curr != NULL)
      {
    	value = get_env_value(curr->data);
    	if ((value_arg1 = get_first_value_arg(value)) == NULL)
    	  return (0);
	replace_alias_var(curr, mysh);
        replace_alias(value_arg1, curr);
    	free(value);
    	free(value_arg1);
    	curr = curr->next;
      }
    return (1);
}
