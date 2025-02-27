/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 10:23:22 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/27 16:53:06 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	jsh_launch(char **args)
{
	pid_t	pid;
	pid_t	wpid;
	int	status;

	pid = fork();
	if (pid < 0)
	{
		perror("jsh");
		//return (1);
	}
	else if (pid == 0)
	{
		if (execvp(args[0], args) == -1)
			perror("jsh");
		exit(EXIT_FAILURE);
		//return (1);
	}
	else
	{
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (1);
}

int	jsh_execute(char **args)
{
	extern char	**environ;

	if (!args || args[0] == NULL)
	{
		return (1);
	}
	if (strcmp(args[0], "cd") == 0)
	{
		jsh_cd(args);
		return (1);
	}
	else if (strcmp(args[0], "exit") == 0)
	{
		//exit(EXIT_SUCCESS);
		//ft_free(args);
		ft_free(environ);
		return (0);
	}
	else if (ft_strcmp(args[0], "echo") == 0)
	{
		jsh_echo(args);
		return (1);
	}
	else if (ft_strcmp(args[0], "pwd") == 0)
	{
		jsh_pwd();
                return (1);
	}
	else if (ft_strcmp(args[0], "env") == 0)
        {
                jsh_env();
                return (1);
        }
	else if (ft_strcmp(args[0], "export") == 0)
        {
                jsh_export(args);
                return (1);
        }
	else if (ft_strcmp(args[0], "unset") == 0)
        {
                jsh_unset(args);
                return (1);
        }
	else
		return (jsh_launch(args));
}

void	jsh_loop(void)
{
	char	*line;
	char	**args;
	int	status;
	//seg fault resolution
	int	count;
	
	status = 1;
	count = 0;
	while (status)
	{
		//printf("%d\n", count++);
		line = readline("minishell>>> ");
		//puts("here");
		if (!line)
			break ;
		if (*line)
			add_history(line);
		args = ft_split2(line, " \a\b\t\n\v\f\r");
		status = jsh_execute(args);
		ft_free(args);
		//free(args);
		free(line);
	}
}

void	jsh_loop_test(char **argv)
{
        char    **args;
        int     status;

        status = 1;
        while (status)
        {
                args = ft_split2(argv[2], " \a\b\t\n\v\f\r");
                status = jsh_execute(args);
                ft_free(args);
        }
}

int	main(int argc, char **argv)
{
	if (argc == 3 && ft_strcmp(argv[1], "-c") == 0 && argv[2])
		jsh_loop_test(argv);
	else	
		jsh_loop();
	return (0);
}
