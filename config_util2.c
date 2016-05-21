/*
** config_util2.c for config_util2 in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Sat Jan 16 15:43:25 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 20:17:21 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		syntax_config_key(char *key, char *type)
{
  if (!is_alpha(key[0]))
    {
      my_printf("%s: Variable name must begin with a letter.\n", type);
      return (0);
    }
  if (!my_str_isalphanum(key))
    {
      my_printf("%s: Variable name must contain alphanumeric ",type);
      my_printf("characters.\n");
      return (0);
    }
  return (1);
}

int		check_command_config(char *tmp)
{
  if (my_strcmp(tmp, "setenv") == 0 || my_strcmp(tmp, "alias") == 0)
    return (1);
  my_printf("%s: command %s is not correct.\n", CONFIG_FILE_NAME, tmp);
  return (0);
}

char		*get_correct_value_config(char *tmp)
{
  int		i;
  int		j;
  char		*value;

  i = 0;
  j = 0;
  if ((value = malloc(sizeof(*value) * (my_strlen(tmp)))) == NULL)
    return (NULL);
  while (tmp[i] != ' ' && tmp[i++] != '\t');
  i++;
  while (tmp[i] != ' ' && tmp[i++] != '\t');
  i++;
  if (tmp[i] == '#')
    return ((my_printf("command %s is not correct.\n", &tmp[i])) ? NULL : NULL);
  while (tmp[i])
    {
      if (tmp[i] == '#')
	break;
      if (tmp[i] != '"' && tmp[i] != '\'')
	value[j++] = tmp[i];
      i++;
    }
  value[j] = 0;
  return (value);
}

int		proceed_update_config(t_mysh *mysh, char **tmp, char *value)
{
  char		*arg;
  char		**args;
  int		res;

  if (my_strcmp(tmp[0], "setenv") == 0)
    {
      if ((args = malloc(sizeof(*args) * (4))) == NULL)
	return (0);
      args[0] = my_strdup(tmp[0]);
      args[1] = my_strdup(tmp[1]);
      args[2] = my_strdup(value);
      args[3] = 0;
      res = builtin_setenv(mysh, args);
      free(args);
    }
  if (my_strcmp(tmp[0], "alias") == 0)
    {
      arg = concat_two_str(tmp[1], value, "=");
      if (!(res = my_add_elem_in_list_begin(&mysh->alias, arg)))
	my_printf("alias: Unable to set alias\n");
      free(arg);
    }
  return (res);
}
