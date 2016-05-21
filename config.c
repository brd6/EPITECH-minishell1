/*
** config.c for config in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Sat Jan 16 02:13:25 2016 Berdrigue BONGOLO BETO
** Last update Thu Jan 21 23:38:35 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

char		**get_config_array(const int fd, int config_nbr)
{
  char		*line;
  char		line_nbr;
  char		**config;
  int		j;

  line_nbr = -1;
  j = 0;
  if ((config = malloc(sizeof(*config) * (config_nbr + 2))) == NULL)
    return (NULL);
  while ((line = get_next_line(fd)) != NULL)
    {
      if (!is_empty_line(line) && !is_comment_line(line))
	{
	  if (is_correct_command_config(line, line_nbr))
	    {
	      config[j] = my_strdup(line);
	      j++;
	    }
	  else
	    return (NULL);
	  free(line);
	}
    }
  config[j] = 0;
  return (config);
}

char		**parse_config()
{
  int		fd;
  int		config_nbr;

  if (!file_exist(CONFIG_FILE_NAME))
    {
      my_printf("%s: The config file doesn't exist, ", CONFIG_FILE_NAME);
      my_printf("run 'bonus' to create it.\n", CONFIG_FILE_NAME);
      return (NULL);
    }
  if ((fd = open(CONFIG_FILE_NAME, O_RDONLY)) == -1)
    {
      my_printf("Unalbe to open %s's file\n", CONFIG_FILE_NAME);
      return (NULL);
    }
  if ((config_nbr = count_line_config()) == -1)
    return (NULL);
  return (get_config_array(fd, config_nbr));
}

int		create_config_file()
{
  int		fd;

  fd = open(CONFIG_FILE_NAME, CREARE_CONFIG_MODE, CONFIG_RIGHT);
  if (fd == -1)
    {
      my_printf("Unalbe to create %s's file\n", CONFIG_FILE_NAME);
      return (0);
    }
  return (write_default_config(fd));
}

int		update_config(char **tmp_config, t_mysh *mysh)
{
  int		i;
  char		**tmp;
  char		*value;

  i = 0;
  value = NULL;
  while (tmp_config[i])
    {
      if ((tmp = my_str_split(tmp_config[i], ' ')) == NULL)
	return (0);
      if (!tmp[1] || !tmp[1][0])
	return (0);
      if (!check_command_config(tmp[0]))
	return (0);
      if (my_strcmp(tmp[0], "alias") != 0 && !syntax_config_key(tmp[1], tmp[0]))
	return (0);
      if ((value = get_correct_value_config(tmp_config[i])) == NULL)
	return (0);
      if (!proceed_update_config(mysh, tmp, value))
      	return (0);
      free(tmp);
      free(value);
      i++;
    }
  return (my_rev_list(&mysh->alias));
}

int		init_config(t_mysh *mysh)
{
  char		**tmp_config;

  if (!file_exist(CONFIG_FILE_NAME))
    {
      if (!create_config_file())
	return (0);
    }
  if ((tmp_config = parse_config()) == NULL)
    return (0);
  return (update_config(tmp_config, mysh));
}
