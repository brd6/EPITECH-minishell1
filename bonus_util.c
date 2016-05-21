/*
** bonus_util.c for bonus_util in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Tue Jan 19 18:29:26 2016 Berdrigue BONGOLO BETO
** Last update Wed May  4 10:41:59 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

char		*shorten_pwd(t_mysh *mysh, char *env_pwd)
{
  char		*home;

  home = key_to_value(mysh->my_env, "HOME");
  if (home != NULL && my_strstr(env_pwd, home) != NULL)
    {
      return (my_str_replace(home, "~", env_pwd, -1));
    }
  return (my_strdup(env_pwd));
}

void		set_prompt_bonus(char *env_user, char *env_host, char *shortpwd)
{
  prompt = my_str_replace("%s1", env_user, "\033[1;34m# \033[0;36m%s1", 1);
  prompt = concat_two_str(prompt, "\033[0;37mat \033[0;32m%s2 \033[0;37m", " ");
  prompt = concat_two_str(prompt, "in \033[1;33m%s3 \n\033[1;31m$\033[0m ", "");
  prompt = my_str_replace("%s2", env_host, prompt, 1);
  prompt = my_str_replace("%s3", shortpwd, prompt, 1);
}

void		prompt_bonus(t_mysh *mysh)
{
  char		*env_user;
  char		*env_host;
  char		*env_pwd;
  char		*shortpwd;

  if (((env_key_exist(mysh->my_env, "USER") &&
       (env_user = key_to_value(mysh->my_env, "USER"))) &&
      (env_key_exist(mysh->my_env, "HOST") &&
       (env_host = key_to_value(mysh->my_env, "HOST"))) &&
      (env_key_exist(mysh->my_env, "PWD") &&
       (env_pwd = key_to_value(mysh->my_env, "PWD")))))
    {
      shortpwd = shorten_pwd(mysh, env_pwd);
      set_prompt_bonus(env_user, env_host, shortpwd);
      my_putstr(prompt);
      free(shortpwd);
      free(env_user);
      free(env_host);
      free(env_pwd);
    }
  else
    {
      prompt = my_strdup("$> ");
      my_putstr(prompt);
    }
}

char		*alias_var_replacing(t_mysh *mysh, char *alias)
{
  char		*var;
  char		*key;
  char		*first_value;
  char		*tmp;

  tmp = my_strdup(alias);
  if (tmp == NULL)
    return (alias);
  var = my_strstr(tmp, "$");
  if (var == NULL)
    return (alias);
  first_value = get_first_value_arg(var);
  key = key_to_value(mysh->my_env, first_value + 1);
  if (env_key_exist(mysh->my_env, first_value + 1))
    alias = my_str_replace(var, key, alias, -1);
  free(first_value);
  free(key);
  return (alias);
}

char		*line_alias_replacing(t_mysh *mysh, char *line)
{
  char		*first_value;
  char		*alias;

  if (!mysh->bonus || line[0] == 0)
    return (line);
  first_value = get_first_value_arg(line);
  if (env_key_exist(mysh->alias, first_value))
    {
      alias = alias_reverse_cmd(mysh, first_value);
      line = my_str_replace(first_value, alias, line, -1);
      free(alias);
    }
  free(first_value);
  line = alias_var_replacing(mysh, line);
  return (line);
}
