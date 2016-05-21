/*
** execute_cmd_util.c for execute_cmd_util in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Wed Jan 13 21:46:40 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 12:44:36 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		is_builins_cmd(char *cmd, t_my_builtin *builtins)
{
  int		i;

  i = 0;
  while (builtins[i].name)
    {
      if (my_strcmp(builtins[i].name, cmd) == 0)
	return (i);
      i = i + 1;
    }
  return (-1);
}

int		is_relative_dir(char *bin)
{
  if (!my_strncmp(bin, "~/", 2) || !my_strncmp(bin, "/", 1)
      || !my_strncmp(bin, "./", 2) || access(bin, F_OK) == 0)
    return (1);
  return (0);
}

char		*get_bin_path_search(char **path, char *bin)
{
  char		*correct_bin;
  int		i;
  struct stat	file_stat;

  i = 0;
  while (path[i])
    {
      correct_bin = concat_two_str(path[i], bin, "/");
      file_stat = my_stat(correct_bin);
      if (!access(correct_bin, F_OK | X_OK) && S_ISREG(file_stat.st_mode))
	return (correct_bin);
      i++;
      free(correct_bin);
    }
  return (NULL);
}

char		*get_bin_path(char *bin, char *str_path)
{
  char		**path;
  char		*correct_bin;

  if (is_relative_dir(bin))
    return (my_strdup(bin));
  if (str_path == NULL)
    {
      my_puterr("There aren't PATH in the env variable\n");
      return (NULL);
    }
  path = my_str_split(str_path, ':');
  check_malloc(path);
  correct_bin = get_bin_path_search(path, bin);
  if (correct_bin == NULL)
    {
      my_puterr(bin);
      my_puterr(": command not found.\n");
    }
  free(path);
  return (correct_bin == NULL ? NULL : correct_bin);
}
