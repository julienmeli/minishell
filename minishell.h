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

#define BUFFER_SIZE 1024

int     execute_command(char **args);
char    **ft_split2(char *str, char *charset);

//echo.c
int     jsh_echo(char **args);

//exit.c
int     clean_exit(char **args, int exit);

//ft_split2.c
void    ft_free(char **array);

//ft_strcmp.c
int     ft_strcmp(const char *s1, const char *s2);

#endif
