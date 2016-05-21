Simple UNIX command interpreter based on tcsh shell. The command lines are simple, no pipes, no redirects or other
advanced features.

<b>Builtins:</b> cd, env, setenv, unsetenv and alias (with --bonus flag)

### Usage :
```
./mysh [bh] [--bonus] [--help]
```

### Example :
```
$ ./mysh b
$> alias
rm	rm -i

$> alias l ls

$> alias
rm	rm -i
l	ls 

$> l
alias_handler.c  builtin_cd.c	 builtin_help.c     builtin_unsetenv.c	config_util3.c	env_util.c	     execute_cmd_util.c  init_builtins.c  Makefile	     README.md
bonus_util.c	 builtin_env.c	 builtin_history.c  config.c		config_util.c	execute_cmd.c	     file_util.c	 lib		  malloc_handlers.c  signal_util.c
builtin_alias.c  builtin_exit.c  builtin_setenv.c   config_util2.c	env_util2.c	execute_cmd_util2.c  include		 main.c		  mysh		     test.c

$> exit

```
