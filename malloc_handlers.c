/*
** malloc_handlers.c for malloc_handlers in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Fri Jan  8 01:27:05 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 16:25:00 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		free_args(char **args)
{
  int		i;

  i = 0;
  while (args[i] != 0)
    {
      free(args[i]);
      i++;
    }
  free(args);
  return (1);
}

void		check_malloc(void *ptr)
{
  if (ptr == NULL)
    {
      my_puterr("Error : malloc error");
      exit(1);
    }
}

int		check_line(char *line)
{
  if (line == NULL)
    {
      my_putstr("exit\n");
      return (0);
    }
  return (1);
}

void		at_exit_mysh(t_mysh *mysh)
{
  free_env(&mysh->my_env);
  if (mysh->bonus)
    free_env(&mysh->alias);
  free(prompt);
}
