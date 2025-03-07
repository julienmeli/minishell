/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 17:04:39 by jmeli             #+#    #+#             */
/*   Updated: 2025/03/07 15:37:59 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	index_existing_var(char *arg)
{
	extern char	**environ;
	int		len;
	int		i;

	if (ft_strchr(arg, '='))
	{
		len = 0;
		while (arg[len] && (arg[len] != '='))
			len++;

	}
	else
		len = ft_strlen(arg);
	i = 0;
	while (environ[i])
	{
		if (ft_strncmp(environ[i], arg, len) == 0 && environ[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

int	update(char *arg, int index)
{
	extern char	**environ;

	if (environ[index])
	{
		free(environ[index]);
		environ[index] = ft_strdup(arg);
		if (!environ[index])
			return (1);
	}
	return (0);
}

int	add_var(char *arg, char **environ)
{
	//extern char	**environ;
	char		**new_environ;
	int		size_env;
	int		i;

	size_env = ft_size_env(environ);
	new_environ = malloc((size_env + 1) * sizeof(*new_environ));
	if (!new_environ)
	{
		perror("memory allocation failed.");
		return (1);
	}
	i = 0;
	while (i < size_env)
	{
		new_environ[i] = environ[i];
		if (!new_environ[i])
		{
			free_array(new_environ, i);
			return (1);
		}
		i++;
	}
	new_environ[size_env] = ft_strdup(arg);
	new_environ[size_env + 1] = NULL;
	//free(environ);
	puts("a");
	environ = new_environ;
	free(new_environ);
	return (0);
}	

int	jsh_export(t_commands **temp)
{
	(void)temp;
	/*
	int	i;
	int	index;
	int	fd;
	
	new_environ = ft_copy_env(envp);
	index = -1;
	if (!args[1])
		return (print_export());
	else
	{
		i = 1;
		while (args[i])
		{
			index = index_existing_var(args[i]);
			printf("index: %d\n", index);
			if (index >= 0)
				update(args[i], index);
			else
			{
				add_var(args[i], envp);
				fd = open("environ_log.txt", O_CREAT | O_WRONLY | O_TRUNC, 0664);
        			ft_putstr_fd(args[i], fd);

			}
			i++;
		}
	}
	*/
	return (0);
}
