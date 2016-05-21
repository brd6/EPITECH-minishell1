/*
** execute_cmd_util2.c for execute_cmd_util2 in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 16:09:08 2016 Berdrigue BONGOLO BETO
** Last update Tue Jan 19 00:33:08 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

char		*concat_two_str(char *str1, char *str2, char *c)
{
  char		*tmp;

  if ((tmp = malloc(my_strlen(str1) + my_strlen(str2) + 2)) == NULL)
    return (0);
  tmp[0] = 0;
  if (str1[my_strlen(str1) - 1] != c[0])
    {
      my_strcat(tmp, str1);
      my_strcat(tmp, c);
      tmp[my_strlen(str1) + 1] = 0;
    }
  else
    {
      my_strcat(tmp, str1);
      tmp[my_strlen(str1)] = 0;
    }
  my_strcat(tmp, str2);
  tmp[my_strlen(str1) + my_strlen(str2) + 1] = 0;
  return (tmp);
}

void		args_replace_str(t_list *my_env, char **args)
{
  int		i;
  char		*env_home;

  i = 0;
  while (args[i])
    {
      if (my_strncmp(args[i], "~", 1) == 0)
	{
	  env_home = key_to_value(my_env, "HOME");
	  if (env_key_exist(my_env, args[1]))
	    args[i] = my_str_replace("~", env_home, args[i], 1);
	  else
	    return;
	}
      i++;
    }
}
