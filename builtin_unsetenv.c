/*
** builtin_unsetenv.c for builtin_unsetenv in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 11:19:21 2016 Berdrigue BONGOLO BETO
** Last update Tue Jan 19 18:03:35 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		builtin_unsetenv(t_mysh *mysh, char **args)
{
  if (args[1] != NULL && env_key_exist(mysh->my_env, args[1]))
    my_rm_all_eq_from_list(&mysh->my_env, args[1], find_key);
  return (1);
}
