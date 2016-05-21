/*
** builtin_cd.c for builtin_cd in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan 14 11:10:03 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 13:35:49 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		find_key(char *data, char *data_ref)
{
  return ((my_strstr(data, data_ref) != NULL) ? 0 : 1);
}

char		*get_goto_dir(t_mysh *mysh, char **args)
{
  char		*home_val;

  if ((args[1] == NULL || args[1][0] == 0) &&
      !env_key_exist_v(mysh->my_env, "HOME"))
    return (NULL);
  if (!env_key_exist(mysh->my_env, "HOME"))
    return (my_strdup(args[1]));
  home_val = key_to_value(mysh->my_env, "HOME");
  if (args[1] != NULL && my_strstr(args[1], "~") != NULL)
    return (my_str_replace("~", home_val, args[1], -1));
  if (args[1] == NULL || args[1][0] == 0)
    return (home_val);
  return (my_strdup(args[1]));
}

void		builtin_cd_replacing_pwd(t_mysh *mysh, char *cwd)
{
  char		*pwd_value;
  t_list	*tmp;

  if (!env_key_exist(mysh->my_env, "PWD"))
    return;
  tmp = my_find_node_eq_in_list(mysh->my_env, "PWD", find_key);
  pwd_value = key_to_value(mysh->my_env, "PWD");
  if (cwd != NULL)
    tmp->data = my_str_replace(pwd_value, cwd, tmp->data, 1);
  free(pwd_value);
}

void		builtin_cd_replacing_oldpwd(t_mysh *mysh, char *cwd)
{
  char		*pwd_value;
  t_list	*tmp;

  if (!env_key_exist(mysh->my_env, "OLDPWD"))
    return;
  tmp = my_find_node_eq_in_list(mysh->my_env, "OLDPWD", find_key);
  pwd_value = key_to_value(mysh->my_env, "OLDPWD");
  if (cwd != NULL)
    tmp->data = my_str_replace(pwd_value, cwd, tmp->data, 1);
  free(pwd_value);
}

int		builtin_cd(t_mysh *mysh, char **args)
{
  char		*goto_dir;
  int		res;
  char		buf[PATH_MAX + 1];
  char		*cwd;

  if ((goto_dir = get_goto_dir(mysh, args)) == NULL)
    return (0);
  if (access(goto_dir, F_OK) != 0)
    return (my_printf("'%s': No such file or folder type.\n", goto_dir));
  if (access(goto_dir, R_OK) != 0)
    return (my_printf("%s: Unauthorized access\n", goto_dir));
  cwd = getcwd(buf, PATH_MAX + 1);
  builtin_cd_replacing_oldpwd(mysh, cwd);
  res = chdir(goto_dir);
  cwd = getcwd(buf, PATH_MAX + 1);
  if (res == -1 || cwd == NULL)
    return (my_printf("%s: Not a directory\n", goto_dir));
  if (!env_key_exist(mysh->my_env, "PWD"))
    return (0);
  builtin_cd_replacing_pwd(mysh, cwd);
  free(goto_dir);
  return (1);
}
