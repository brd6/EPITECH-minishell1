/*
** file_util.c for file_util in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Sat Jan 16 01:57:14 2016 Berdrigue BONGOLO BETO
** Last update Sat Jan 16 02:13:46 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

struct stat	my_stat(char *file)
{
  struct stat	file_stat;

  stat(file, &file_stat);
  return (file_stat);
}

int		file_exist(char *file)
{
  struct stat	file_stat;

  return (stat(file, &file_stat) == 0);
}
