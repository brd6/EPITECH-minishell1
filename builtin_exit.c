/*
** builtin_exit.c for builtin_exit in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 11:14:53 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 21:58:46 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		builtin_exit(t_mysh *mysh, char **args)
{
  if (args[1] == NULL || args[1][0] == 0)
    {
      mysh->exit_code = 0;
      my_putstr("exit\n");
      return (EXIT_PROG);
    }
  if (!my_str_isnum(args[1]) || args[2] != NULL)
    {
      mysh->exit_code = 1;
      my_puterr("exit: Expression Syntax.\n");
      return (GO_ON);
    }
  mysh->exit_code = my_getnbr(args[1]) % 256;
  my_putstr("exit\n");
  return (EXIT_PROG);
}
