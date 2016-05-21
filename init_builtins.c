/*
** init_builtins.c for init_builtins in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Wed Jan 13 21:26:09 2016 Berdrigue BONGOLO BETO
** Last update Thu Jan 21 23:17:26 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

void		init_builtin_struct(t_my_builtin *builtin,
				    char *name,
				    int (*func)(t_mysh *mysh, char **args))
{
  builtin->name = name;
  builtin->func = func;
}

void		init_builtins(t_my_builtin *builtins)
{
  init_builtin_struct(&builtins[0], "exit", &builtin_exit);
  init_builtin_struct(&builtins[1], "cd", &builtin_cd);
  init_builtin_struct(&builtins[2], "env", &builtin_env);
  init_builtin_struct(&builtins[3], "history_", &builtin_exit);
  init_builtin_struct(&builtins[4], "setenv", &builtin_setenv);
  init_builtin_struct(&builtins[5], "unsetenv", &builtin_unsetenv);
  init_builtin_struct(&builtins[6], "exit", &builtin_exit);
  init_builtin_struct(&builtins[7], "help", &builtin_help);
  init_builtin_struct(&builtins[8], "alias", &builtin_alias);
  init_builtin_struct(&builtins[9], NULL, NULL);
}
