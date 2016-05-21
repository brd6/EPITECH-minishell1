/*
** main.c for minishell1 in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Tue Jan  5 16:33:42 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 20:52:46 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		option_handler(t_mysh *mysh, char **av)
{
  if (!my_strcmp(av[1], "--help") || !my_strcmp(av[1], "h"))
    {
      builtin_help(mysh, av);
      return (0);
    }
  if (!my_strcmp(av[1], "--bonus") || !my_strcmp(av[1], "b"))
    {
      if (init_config(mysh))
	mysh->bonus = 1;
      return (1);
    }
  return (1);
}

void		show_prompt(t_mysh *mysh)
{
  char		*env_pwd;

  if ( mysh->bonus == 1)
    prompt_bonus(mysh);
  else if (env_key_exist(mysh->my_env, "PWD") &&
       (env_pwd = key_to_value(mysh->my_env, "PWD")))
    {
      prompt = my_str_replace("%s", env_pwd, "%s> ", 1);
      my_putstr(prompt);
      free(env_pwd);
    }
  else
    {
      prompt = my_strdup("$> ");
      my_putstr(prompt);
    }
}

void		mysh_loop(t_mysh *mysh)
{
  char		*line;
  char		**args;
  int		status;
  t_my_builtin	builtins[10];

  init_builtins(builtins);
  while (1)
    {
      show_prompt(mysh);
      line = get_next_line(0);
      if (!check_line(line))
	break;
      else
      	{
	  line = line_alias_replacing(mysh, line);
      	  args = my_str_split(line, ' ');
      	  status = execute_cmd(mysh, args, builtins);
      	  free_args(args);
	  if (mysh->bonus && mysh->my_env != NULL)
	    my_putchar('\n');
	  if (status == EXIT_PROG)
	    break;
      	}
      free(line);
    }
}

int		main(int ac, char **av, char **envn)
{
  t_mysh	mysh;

  signal(SIGINT, sig_handler);
  mysh.bonus = 0;
  mysh.exit_code = 0;
  mysh.alias = NULL;
  if (envn == NULL || envn[0] == 0)
    mysh.my_env = NULL;
  else
    {
      mysh.my_env = my_params_in_list(my_wordtab_count(envn), envn);
      check_malloc(mysh.my_env);
      my_rev_list(&mysh.my_env);
    }
  if (ac == 2)
    {
      if (!option_handler(&mysh, av))
	return (0);
    }
  bonus = mysh.bonus;
  mysh_loop(&mysh);
  at_exit_mysh(&mysh);
  return (mysh.exit_code);
}
