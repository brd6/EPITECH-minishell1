/*
** builtin_setenv.c for builtin_setenv in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 11:16:39 2016 Berdrigue BONGOLO BETO
** Last update Thu Jan 21 16:01:34 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		syntax_env_key(char *key)
{
  if (!is_alpha(key[0]))
    {
      my_printf("setenv: Variable name must begin with a letter.\n");
      return (0);
    }
  if (!my_str_isalphanum(key))
    {
      my_printf("setenv: Variable name must contain alphanumeric characters.");
      my_printf("\n");
      return (0);
    }
  return (1);
}

int		builtin_setenv_cond(t_list *my_env, char **args)
{
  t_list	*tmp;
  char		*new_elem;

  new_elem = concat_two_str(args[1], args[2], "=");
  if (env_key_exist(my_env, args[1]))
    {
      tmp = my_find_node_eq_in_list(my_env, args[1], find_key);
      tmp->data = new_elem;
      return (1);
    }
  else
    {
      if (!my_add_elem_in_list_end(&my_env, new_elem))
	{
	  my_printf("setenv: Unable to set a new variable to the env\n");
	  return (0);
	}
      return (1);
    }
}

int		builtin_setenv(t_mysh *mysh, char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (builtin_env(mysh, args));
  if (!syntax_env_key(args[1]))
    return (0);
  return (builtin_setenv_cond(mysh->my_env, args));
}
