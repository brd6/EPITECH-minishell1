/*
** builtin_env.c for builtin_env in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 11:13:24 2016 Berdrigue BONGOLO BETO
** Last update Thu Jan 21 23:23:01 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

void		print_env(void *data)
{
  my_printf("%s\n", data);
}

int		builtin_env(t_mysh *mysh, char **args)
{
  if (args == NULL || args !=NULL)
    my_apply_on_list(mysh->my_env, print_env);
  return (1);
}
