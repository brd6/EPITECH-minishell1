/*
** execute_cmd.c for execute_cmd in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Fri Jan  8 01:35:22 2016 Berdrigue BONGOLO BETO
** Last update Wed May  4 01:38:41 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		check_bin_permission(char *bin)
{
  struct stat	file_stat;

  file_stat = my_stat(bin);
  if (access(bin, F_OK) != 0 || !S_ISREG(file_stat.st_mode))
    {
      my_puterr(bin);
      my_puterr(": command not found.\n");
      return (0);
    }
  if (access(bin, X_OK) != 0)
    {
      my_puterr(bin);
      my_puterr(": Permission denied\n");
      return (0);
    }
  return (1);
}

void		son_process_action(char *bin, char **env, char **args)
{
  int		res;

  signal(SIGINT, SIG_IGN);
  if (!check_bin_permission(bin))
    exit(1);
  res = execve(bin, args, env);
  if (res == -1)
    {
      my_puterr("Execve: an error has occurred\n");
    }
}

int		father_process_action(int son_pid)
{
  int		son_status;

  while (wait(&son_status) != son_pid);
  if (WIFSIGNALED(son_status) == 1 && WTERMSIG(son_status) == SIGSEGV)
    my_puterr("Segmentation Fault\n");
  else if (WIFSIGNALED(son_status) == 1 && WTERMSIG(son_status) == SIGFPE)
    my_puterr("Floating point exception\n");
  return (son_status);
}

int		execute_cmd_system(t_mysh *mysh, char **args)
{
  pid_t		son_pid;
  char		**env;
  char		*bin;

  env = env_list_to_array(mysh->my_env);
  if ((bin = get_bin_path(args[0], key_to_value(mysh->my_env, "PATH"))) == NULL)
    {
      free(env);
      return (GO_ON);
    }
  if ((son_pid = fork()) == -1)
    {
      my_puterr("Error : unable to create a new process\n");
      free(env);
      free(bin);
      return (GO_ON);
    }
  if (son_pid == 0)
    son_process_action(bin, env, args);
  else
    father_process_action(son_pid);
  free(bin);
  free(env);
  return (GO_ON);
}

int		execute_cmd(t_mysh *mysh, char **args, t_my_builtin *builtins)
{
  int		builtin_index;

  if (args[0] == NULL || args[0][0] == 0)
    return (GO_ON);
  args_replace_str(mysh->my_env, args);
  if ((builtin_index = is_builins_cmd(args[0], builtins)) != -1)
    return (builtins[builtin_index].func(mysh, args));
  else
    return (execute_cmd_system(mysh, args));
  return (GO_ON);
}
