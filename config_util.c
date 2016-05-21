/*
** config_util.c for config_util in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Sat Jan 16 14:00:01 2016 Berdrigue BONGOLO BETO
** Last update Fri Jan 22 01:51:31 2016 Berdrigue BONGOLO BETO
*/

#include "mysh.h"

int		write_default_config(int fd)
{
  char		*txt;

  txt = my_strdup("\n# this is a comment line\n");
  if (write(fd, txt, my_strlen(txt)) == -1)
    return (0);
  txt = my_strdup("\n### setenv\n");
  if (write(fd, txt, my_strlen(txt)) == -1)
    return (0);
  txt = my_strdup("setenv EDITOR vi\n");
  if (write(fd, txt, my_strlen(txt)) == -1)
    return (0);
  txt = my_strdup("setenv EDITOR nano\n");
  if (write(fd, txt, my_strlen(txt)) == -1)
    return (0);
  txt = my_strdup("\n### alias\n");
  if (write(fd, txt, my_strlen(txt)) == -1)
    return (0);
  txt = my_strdup("alias rm rm -i\n");
  if (write(fd, txt, my_strlen(txt)) == -1)
    return (0);
  free(txt);
  close(fd);
  return (1);
}

int		is_comment_line(char *line)
{
  int		i;

  i = 0;
  while (line && line[i])
    {
      if (line[i] == ' ' || line[i] == '\t')
	i++;
      if (line[i] == '#')
	return (1);
      else
	return (0);
      i++;
    }
  return (0);
}

int		is_empty_line(char *line)
{
  int		i;

  i = 0;
  if (line == NULL || line[0] == 0)
    return (1);
  while (line && (line[i] == ' ' || line[i] == '\t'))
    i++;
  return (my_strlen(line) == i);
}

int		is_correct_command_config(char *line, int line_nbr)
{
  int		i;

  i = 0;
  while (line && line[i])
    {
      if (line[i] == ' ' || line[i] == '\t')
	i++;
      if (my_strstr(&line[i], "setenv") != NULL ||
	  my_strstr(&line[i], "alias") != NULL)
	return (1);
      else
      {
	if (line_nbr != -1)
	  my_printf("%s: the line %d is not correct.\n", CONFIG_FILE_NAME,
		    line_nbr);
	return (1);
      }
      i++;
    }
  return (0);
}

int		count_line_config()
{
  int		fd;
  char		*line;
  int		cp;
  int		line_nbr;

  if ((fd = open(CONFIG_FILE_NAME, O_RDONLY)) == -1)
    {
      my_printf("Unalbe to open %s's file\n", CONFIG_FILE_NAME);
      return (-1);
    }
  cp = 0;
  line_nbr = 1;
  while ((line = get_next_line(fd)) != NULL)
    {
      if (!is_empty_line(line) && !is_comment_line(line))
	{
	  if (is_correct_command_config(line, line_nbr))
	    cp++;
	  else
	    return (-1);
	}
      free(line);
      line_nbr++;
    }
  return (cp);
}
