/*
** builtin_help.c for builtin_help in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 19:07:50 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 20:21:15 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		builtin_help(t_mysh *mysh, char **args)
{
  if (args == NULL || args !=NULL || mysh != NULL || mysh == NULL)
    {

    }
  my_printf("%s### %sProjet minishell1 - bongol_b %s###\n\n",
	    WHITE, BRED, WHITE);
  my_printf("%sUsage%s: ./mysh [bh] [--bonus] [--help]\n\n", BRED, WHITE);
  my_printf("%sBuiltins%s: help, cd, env, setenv, unsetenv\n\n", BRED, WHITE);
  return (1);
}
