/*
** env_util2.c for env_util2 in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Fri Jan 15 18:02:00 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 13:29:10 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		env_key_exist(t_list *my_env, char *key)
{
  return (my_env != NULL && key != NULL && key_to_value(my_env, key) != NULL);
}

int		env_key_exist_v(t_list *my_env, char *key)
{
  if (key == NULL)
    return (0);
  if (key_to_value(my_env, key) == NULL)
    {
      my_puterr("Error: The ");
      my_puterr(key);
      my_puterr(" variable is not defined. Please define it before.\n");
      return (0);
    }
  return (1);
}
