/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmeli <jmeli@student.42luxembourg.lu>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/24 12:01:27 by jmeli             #+#    #+#             */
/*   Updated: 2025/02/27 15:07:00 by jmeli            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_size_env(char **env)
{
	int	i;

	i = 0;
	while (env[i])
		i++;
	return (i);
}

/*
static char	**ft_populate_new_env(char **new_environ, char **environ, int size,
		int index)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < size)
	{
		if (i != index)
		{
			//new_environ[j] = ft_strdup(environ[i]);
			new_environ[j] = environ[i];
			
			if (!new_environ[j])
			{
				free_array(new_environ, j);
				return (NULL);
			}
			
			j++;
		}
		i++;
	}
	new_environ[j] = NULL;
	return (new_environ);
}
*/

char	**ft_remove_var(char **environ, int index)
{
	char	**new_environ;
	int		size;
	int		i;
	int		j;

	size = ft_size_env(environ);
	if (size <= 1)
	{
		free(environ[0]);
		free(environ);
		return (NULL);
	}
	if (index < 0 || index >= size)
		return (environ);
	new_environ = (char **)malloc((size) * sizeof(char *));
	if (new_environ == NULL)
	{
		perror("memory allocation failed.");
		return (NULL);
	}
	i = 0;
        j = 0;
        while (i < size)
        {
                //printf("size:%d i:%d j:%d index:%d\n", size, i, j, index);
		if (i != index)
                {
                        new_environ[j] = environ[i];
                        j++;
                }
		else
		{
			//puts("che");
			//free(environ[i]);
			environ[i] = NULL;
			//puts("val");
		}
                i++;
        }
	new_environ[j] = NULL;
	i = 0;
	/*
	while (i < size)
	{
		if (environ[i])
			printf("environ[i]:%s\n", environ[i]);
		if (new_environ[i])
			printf("new_environ[i]:%s", new_environ[i]);
		printf("\n");
		i++;
	}
	*/
	//new_environ = ft_populate_new_env(new_environ, environ, size, index);
	free(environ);
	return (new_environ);
}

int	jsh_unset(char **args)
{
	extern char	**environ;
	int			i;
	int			k;
	int			size;
	int			len;
	
	size = ft_size_env(environ);
	if (!args[1] || args[1] == NULL)
	{
		printf("unset: not enough arguments\n");
		return (1);
	}
	k = 1;
	while (args[k])
	{
		i = 0;
		len = ft_strlen(args[k]);
		while (i < size)
		{
			if ((ft_strncmp(environ[i], args[k], len) == 0)
				&& environ[i][len] == '=')
			{
				//puts("heremoving");
				environ = ft_remove_var(environ, i);
				//puts("hello");
				size = ft_size_env(environ);
				i = size;
				//puts("hola");	
			}
			//printf("%d %d\n", size, i);
			i++;
		}
		k++;
		//puts("3");
	}
	//puts("here mais oui");
	//ft_free(environ);
	return (0);
}
