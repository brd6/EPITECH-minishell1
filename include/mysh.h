/*
** mysh.h for mysh in /home/bongol_b/rendu/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Thu Jan  7 23:31:04 2016 Berdrigue BONGOLO BETO
** Last update Sun Jan 24 19:38:00 2016 Berdrigue BONGOLO BETO
*/

#ifndef MYSH_H_
# define MYSH_H_
# define GO_ON 1
# define EXIT_PROG 42
# define CONFIG_FILE_NAME ".myshrc"
# define CONFIG_RIGHT ((S_IWUSR + S_IRUSR) | (S_IRGRP) | (S_IROTH))
# define CREARE_CONFIG_MODE ((O_CREAT) | (O_WRONLY))
# define WHITE	"\033[0m"
# define RED	"\033[0;31m"
# define GREEN	"\033[0;32m"
# define YELLOW	"\033[1;33m"
# define BLUE	"\033[0;34m"
# define BBLUE2	"\033[0;36m"
# define GRAY	"\033[0;37m"
# define BOLD	"\033[1m"
# define BWHITE	"\033[1;0m"
# define BRED	"\033[1;31m"
# define BGREEN	"\033[1;32m"
# define BBLUE	"\033[1;34m"
# define BCYAN	"\033[1;36m"

# include <stdio.h>
# include <stdlib.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <sys/wait.h>
# include <signal.h>
# include <linux/limits.h>
# include "my.h"

typedef struct	s_mysh
{
  t_list	*my_env;
  t_list	*alias;
  int		exit_code;
  int		bonus;
}		t_mysh;

typedef struct	s_my_builtin
{
  char		*name;
  int		(*func)(t_mysh *mysh, char **args);
}		t_my_builtin;

char		*prompt;
int		bonus;

int		my_printf(char *format, ...);
int		key_value_cmp(char *data, char *data_ref);
char		*key_to_value(t_list *env, char *key);
char		**env_list_to_array(t_list *my_env);
void		sig_handler(int code);
int		execute_cmd(t_mysh *mysh, char **args, t_my_builtin *);
int		free_args(char **args);
void		check_malloc(void *ptr);
void		free_env(t_list **my_env);
int		builtin_exit(t_mysh *mysh, char **args);
int		builtin_cd(t_mysh *mysh, char **args);
int		builtin_env(t_mysh *mysh, char **args);
/* int		builtin_history(t_mysh *mysh, char **args); */
int		builtin_setenv(t_mysh *mysh, char **args);
int		builtin_unsetenv(t_mysh *mysh, char **args);
int		builtin_help(t_mysh *mysh, char **args);
int		builtin_alias(t_mysh *mysh, char **args);
void		init_builtins(t_my_builtin builtins[6]);
char		*get_bin_path(char *bin, char *str_path);
char		*concat_two_str(char *str1, char *str2, char *c);
void		args_replace_str(t_list *my_env, char **args);
char		*get_env_key(char *env_data);
char		*get_env_value(char *env_data);
int		find_key(char *data, char *data_ref);
int		env_key_exist(t_list *my_env, char *key);
struct stat	my_stat(char *file);
int		file_exist(char *file);
int		init_config(t_mysh *mysh);
int		env_key_exist_v(t_list *my_env, char *key);
int		write_default_config(int fd);
int		count_line_config();
int		check_command_config(char *tmp);
int		proceed_update_config();
char		*get_correct_value_config(char *tmp);
int		proceed_update_config(t_mysh *mysh, char **tmp, char *value);
int		update_alias_config(t_mysh *mysh);
int		is_builins_cmd(char *cmd, t_my_builtin *builtins);
void		print_env(void *data);
int		check_line(char *line);
void		promp_bonus(t_mysh *mysh);
char		*get_first_value_arg(char *value);
char		*line_alias_replacing(t_mysh *mysh, char *line);
int		backup_prompt(char *prompt);
void		restore_prompt();
void		delete_prompt();
void		prompt_bonus(t_mysh *mysh);
int		is_comment_line(char *line);
int		is_empty_line(char *line);
int		is_correct_command_config(char *line, int line_nbr);
int		syntax_config_key(char *key, char *type);
char		*shorten_pwd(t_mysh *mysh, char *env_pwd);
void		at_exit_mysh(t_mysh *mysh);
char		*alias_reverse_cmd(t_mysh *mysh, char *alias);
char		*get_corr_alias_cond(t_mysh *, char *, char *alias, char *);
#endif /* !MYSH_H_ */
