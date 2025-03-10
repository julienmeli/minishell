/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/03 15:30:22 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/10 12:33:46 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int     size_env(char **array)
{
        int     i;

        i = 0;
        while (array[i])
                i++;
        return (i);
}

char    **ft_copy_env(char **envp)
{
        char    **new_env;
        int     size;
        int     i;

        size = size_env(envp);
        new_env = malloc((size + 1) * sizeof(*new_env));
        if (!new_env)
                return (NULL);
        i = 0;
        while (i < size)
        {
                new_env[i] = ft_strdup(envp[i]);
                i++;
        }
        new_env[i] = NULL;
        return (new_env);
}

int	ft_delete_file(char **envp)
{
	char	**args;
	
	args = malloc(4 * sizeof(*args));
	if (!args)
	{
		perror("memory allocation");
		return (1);
	}
	args[0] = "/bin/rm";
	args[1] = "-f";
	args[2] = "example.txt";
       	args[3] = NULL; 
	printf("Deleting file using execve...\n");
	if (execve("/bin/rm", args, envp) == -1) 
	{
		perror("execve failed");
		return 1;
	}
	free(args);
	return (0);
}

void	ft_free(char **array)
{
	int	i;

	i = 0;
	if (array)
	{	
		while (array[i])
		{
			//array[i] = NULL;
			if (array[i])
			{	
				free(array[i]);
				array[i] = NULL;
			}
			i++;
		}
		printf("i:%d\n", i);
		//free(array[53]);
		free(array);
		array = NULL;
	}
}

int	ft_builtin(t_commands **temp, t_env **env)
{
	//static	int	change_env;
	//extern char	**environ;
	char	**args;

	args = (*temp)->command;
	if (!args || args[0] == NULL)
		return (1);
	else if (strcmp(args[0], "cd") == 0)
		return (jsh_cd(args));
	else if (strcmp(args[0], "exit") == 0)
	{
		exit(EXIT_SUCCESS);
		/*
		if (change_env != 0)
			ft_free(environ);
		*/
		return (0);
	}
	else if (ft_strcmp(args[0], "echo") == 0)
		return(jsh_echo(args));
	else if (ft_strcmp(args[0], "pwd") == 0)
		return (jsh_pwd());
	else if (ft_strcmp(args[0], "env") == 0)
        	return (jsh_env(temp, env));
	else if (ft_strcmp(args[0], "export") == 0)
        	return (jsh_export(temp, env));
	else if (ft_strcmp(args[0], "unset") == 0)
        	return (jsh_unset(temp, env));
	else
		return (1);
}
