#ifndef MINISHELL_H
#define MINISHELL_H

#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <stdio.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "./libft/libft.h"
#include <stdio.h>

#define BUFFER_SIZE 1024

int     execute_command(char **args);
char    **ft_split2(char *str, char *charset);

//Builtins
//cd.c //echo.c //env.c //exit.c //export.c //pwd.c //unset.c
int     jsh_cd(char **args);
int     jsh_echo(char **args);
int     jsh_env(void);
int     jsh_exit(char **args);
int     jsh_export(char **args);
int     jsh_pwd(void);
int     jsh_unset(char **args);
int     clean_exit(char **args, int exit);
int     ft_size_env(char **env);

//export.c (utils)
int	print_export(void);
void    sort_env_alphabetically(char **array);
void    free_array(char **array, int index);
char    **copy_environ(char **environ);

//ft_split2.c
void    ft_free(char **array);

//ft_strcmp.c
int     ft_strcmp(const char *s1, const char *s2);

#endif
