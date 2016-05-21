/*
** signal_util.c for signal_util in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Fri Jan 22 02:30:01 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 16:23:03 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

void		sig_handler(int code)
{
  if (code == SIGINT)
    {
      if (bonus)
	my_putchar('\n');
      my_printf("\n%s", prompt);
      signal(SIGINT, sig_handler);
    }
}
