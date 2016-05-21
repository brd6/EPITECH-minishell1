/*
** builtin_alias.c for builtin_alias in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Tue Jan 19 15:44:39 2016 Berdrigue BONGOLO BETO
** Last update Sat Jan 23 23:32:45 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

void		show_alias(t_mysh *mysh)
{
  t_list	*curr;
  char		*key;
  char		*value;

  curr = mysh->alias;
  while (curr != NULL)
    {
      key = get_env_key(curr->data);
      value = get_env_value(curr->data);
      my_printf("%s\t%s\n", key, value);
      free(key);
      free(value);
      curr = curr->next;
    }
}

int		builtin_setalias(t_mysh *mysh, char *key, char *value)
{
  t_list	*tmp;
  char		*new_elem;

  new_elem = concat_two_str(key, value, "=");
  if (env_key_exist(mysh->alias, key))
    {
      tmp = my_find_node_eq_in_list(mysh->alias, key, find_key);
      tmp->data = new_elem;
      return (1);
    }
  else
    {
      if (!my_add_elem_in_list_end(&mysh->alias, new_elem))
	{
	  my_printf("alias: Unable to set a new alias\n");
	  return (0);
	}
      return (1);
    }
  return (0);
}

int		builtin_alias(t_mysh *mysh, char **args)
{
  char		*arg;
  int		res;

  if (!mysh->bonus)
    return (my_printf("%s: command not found.\n", "alias"));
  if (args[1] == NULL)
    {
      show_alias(mysh);
      return (1);
    }
  if (args[2] == NULL)
    return (1);
  arg = my_wordtab_to_str(&args[2], ' ');
  res = builtin_setalias(mysh, args[1], arg);
  free(arg);
  return (res);
}
